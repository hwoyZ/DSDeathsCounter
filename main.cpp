#include <iostream>

#include <fstream>

#include <filesystem>

#include <chrono>

#include <thread>

#include "soulgame.hpp"

#define DEFAULT_FILENAME "DSDeathsCount.txt"

#define DEFAULT_PLACEHOLDER "{}"

#define DEFAULT_FORMATTED_TEXT ("Deaths: " DEFAULT_PLACEHOLDER)



static std::size_t searching(const std::vector<CSoulGame> &games)
{
    while(true)
    {
        for(std::size_t i=0; i<games.size(); ++i)
        {
            auto const error = std::get<0>(games[i].getCSoulGameProcess());
            if(error.id)
            {
                std::cerr << "ERROR ID: " << error.id << " -> " <<  error.msg << std::endl;
            }
            else
            {
                return i;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }
}


static bool replace(std::string& str, const std::string& from, const std::string& to)
{
    std::size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

static void usage()
{
    std::cerr << "\n\n==== USAGE ====\n\n";
    std::cerr << "program\n";
    std::cerr << "program format filename\n";

    std::cerr << "\nExample:\n";
    std::cerr << "format = \"COUNT: {}\"\n";

    std::cerr << "\nDefault param:\n";
    std::cerr << "format = " << DEFAULT_FORMATTED_TEXT << std::endl;
    std::cerr << "filename = " << DEFAULT_FILENAME << std::endl;
}

static void write_to_file(const std::string &filename,std::ofstream &file,std::string text,int value)
{
    std::filesystem::resize_file(filename, 0);
    file.seekp(0);

    while(replace(text,DEFAULT_PLACEHOLDER,std::to_string(value))) {}
    file << text;
    file.flush();
}

int main(int argc,const char **argv)
{

    std::string filename=DEFAULT_FILENAME,formatted_text=DEFAULT_FORMATTED_TEXT;

    switch(argc)
    {
    case 3:
        filename=argv[2];
    case 2:
        formatted_text=argv[1];
    case 1:
        break;
    default:
        usage();
        return 1;
    }

    std::ofstream file(filename);

    const std::vector<CSoulGame> games =
    {
        CSoulGame("DarkSoulsRemastered.exe",{0,0},{0x1C8A530,0x98}),
        CSoulGame("eldenring.exe",{0,0},{0x3D5DF38, 0x94})

    };

    while(true)
    {
        const auto [error,gameproc] = games[searching(games)].getCSoulGameProcess();

        std::cout << gameproc.getname() << std::endl;

        int old_value=0;
        write_to_file(filename,file,formatted_text,old_value);

        while(error.id==0)
        {
            const auto op = gameproc.getDeathCount();

            if(op)
            {
                std::cout << "DeathCount: " << op.value() << std::endl;

                if(op.value() != old_value)
                {
                    old_value = op.value();
                    write_to_file(filename,file,formatted_text,old_value);
                }
            }
            else
            {
                std::cerr << gameproc.getname() << " is over." << std::endl;
                break;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }

    return 0;
}
