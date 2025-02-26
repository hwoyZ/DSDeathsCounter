#include <windows.h>

#include <tlhelp32.h>

#include <psapi.h>

#include <vector>

#include <cstdint>

#ifndef __PROCESS_H__
#define __PROCESS_H__

static DWORD FindProcessId(const char * processname)
{
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;
    DWORD result = 0;

    // Take a snapshot of all processes in the system.
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (INVALID_HANDLE_VALUE == hProcessSnap) return 0;

    pe32.dwSize = sizeof(PROCESSENTRY32); // <----- IMPORTANT

    // Retrieve information about the first process,
    // and exit if unsuccessful
    if (!Process32First(hProcessSnap, & pe32))
    {
        CloseHandle(hProcessSnap); // clean the snapshot object
        return 0;
    }

    do
    {
        //std::cout << "Checking process " << pe32.szExeFile << std::endl;
        if (0 == strcmp(processname, pe32.szExeFile))
        {
            result = pe32.th32ProcessID;
            break;
        }
    }
    while (Process32Next(hProcessSnap, & pe32));

    CloseHandle(hProcessSnap);

    return result;
}

static HMODULE GetBaseAddress(const HANDLE hProcess)
{
    if (!hProcess)
        return 0; // No access to the process

    HMODULE lphModule[1024]; // Array that receives the list of module handles
    DWORD lpcbNeeded(0); // Output of EnumProcessModules, giving the number of bytes requires to store all modules handles in the lphModule array

    if (!EnumProcessModulesEx(hProcess, lphModule, sizeof(lphModule), & lpcbNeeded, LIST_MODULES_32BIT | LIST_MODULES_64BIT))
        return 0; // Impossible to read modules

    TCHAR szModName[MAX_PATH];
    if (!GetModuleFileNameEx(hProcess, lphModule[0], szModName, sizeof(szModName) / sizeof(TCHAR)))
        return 0; // Impossible to get module info

    return lphModule[0]; // Module 0 is apparently always the EXE itself, returning its address
}

#endif