#include <iostream>

#include <fstream>

#include <filesystem>

#include <chrono>

#include <thread>

#include "soulgame.hpp"


static const char default_filename[] = "DSDeathsCount.txt";

static const char default_formatted_text[]="Deaths: {}";

static const char default_placeholder[]="{}";


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
    size_t start_pos = str.find(from);
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
    std::cerr << "format = " << default_formatted_text << std::endl;
    std::cerr << "filename = " << default_filename << std::endl;
}

int main(int argc,const char **argv)
{

    std::string filename=default_filename,formatted_text=default_formatted_text;

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

        while(error.id==0)
        {
            const auto op = gameproc.getDeathCount();

            if(op)
            {
                std::cout << "DeathCount: " << op.value() << std::endl;

                std::filesystem::resize_file(filename, 0);
                file.seekp(0);

                auto text = formatted_text;
                while(replace(text,default_placeholder,std::to_string(op.value()))) {}
                file << text;
                file.flush();

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
