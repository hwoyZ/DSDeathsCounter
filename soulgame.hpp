#include <iostream>

#include <windows.h>

#include <psapi.h>

#include <vector>

#include <cstdint>

#include <string>

#include <utility>

#include <optional>

#include <wow64apiset.h>

#include "process.hpp"

#ifndef __SOULGAME_H__
#define __SOULGAME_H__

class CSoulGameProcess
{
protected:
    std::string name;
    DWORD pid;
    HANDLE hProcess;
    HMODULE baseaddress;
    std::vector<int> offset;

public:

    CSoulGameProcess(CSoulGameProcess &&g):
        name(g.name),pid(g.pid),hProcess(g.hProcess), baseaddress(g.baseaddress), offset(g.offset)
    {
        g.pid=0;
        g.hProcess=0;

    }

    CSoulGameProcess(const CSoulGameProcess &)=delete;
    CSoulGameProcess operator=(const CSoulGameProcess &)=delete;
    CSoulGameProcess &operator=(CSoulGameProcess &&)=delete;

    CSoulGameProcess(const std::string &name, DWORD pid,HANDLE hProcess,HMODULE baseaddress,
                     const std::vector<int> &offset):
        name(name),pid(pid),hProcess(hProcess), baseaddress(baseaddress), offset(offset) {}


    ~CSoulGameProcess()
    {
        if(pid && hProcess)
        {
            CloseHandle(hProcess);
        }
    }

    std::optional<int> getDeathCount() const
    {
        int value = 0;
        if(PeekMemory(hProcess, reinterpret_cast < uintptr_t > (GetBaseAddress(hProcess)), true, offset, value))
        {
            return value;
        }

        return {};
    }

    const std::string& getname() const
    {
        return name;
    }

};



struct CError
{
    unsigned   int id;
    std::string msg;
};

class CSoulGame
{
#define CSoulGameProcess_DUMMY() CSoulGameProcess("",0,0,0, {0,0})
protected:
    std::string name;
    std::vector<int> offset32;
    std::vector<int> offset64;

public:
    CSoulGame(const std::string &name,const std::vector<int> offset32,const std::vector<int> offset64):
        name(name),offset32(offset32),offset64(offset64)
    {}


    std::pair<CError,CSoulGameProcess> getCSoulGameProcess() const
    {
        const DWORD pid = ::FindProcessId(this->name.c_str());

        if(!pid)
        {
            return std::make_pair(CError{1,this->name+": PID not found."},CSoulGameProcess_DUMMY());
        }

        const HANDLE hProcess = ::OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, false, pid);
        if(!hProcess)
        {
            return std::make_pair(CError{2,this->name+": can be not open."},CSoulGameProcess_DUMMY());
        }

        const HMODULE baseaddress = ::GetBaseAddress(hProcess);
        if(!baseaddress)
        {
            return std::make_pair(CError{3,this->name+": can not access baseaddress."},CSoulGameProcess_DUMMY());
        }

        BOOL isWow64 = FALSE;
        if (!IsWow64Process(hProcess, &isWow64))
        {
            return std::make_pair(CError{4,this->name+": Wow64 error."},CSoulGameProcess_DUMMY());
        }

        return std::make_pair(CError{0,""},CSoulGameProcess(name,pid,hProcess,baseaddress,isWow64 ? offset32:offset64));
    }

};

#if !defined __GNUC__
#error gcc or clang only
#endif

#if !defined __x86_64__
#error X64 only
#endif


#endif
