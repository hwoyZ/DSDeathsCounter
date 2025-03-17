#include <iostream>

#include <fstream>

#include <filesystem>

#include <chrono>

#include <thread>

#include "soulgame.hpp"

#define DEFAULT_FILENAME "DSDeathsCount.txt"

#define DEFAULT_PLACEHOLDER "{}"

#define DEFAULT_FORMATTED_TEXT ("Deaths: " DEFAULT_PLACEHOLDER)

#define SEARCHING_SLEEP_TIME std::chrono::milliseconds(500)

#define GETDEATHCOUNT_SLEEP_TIME std::chrono::milliseconds(1000)



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

            std::this_thread::sleep_for(SEARCHING_SLEEP_TIME);
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

static void usage(const std::vector<CSoulGame> &games)
{
    std::cerr << "\n\n================== HELP ==================\n\n";

#ifdef __DCVERSION__
    std::cerr << "\tVERSION:" << __DCVERSION__ << "\n";
#endif

#ifdef __DCHASH__
    std::cerr << "\tHASH:" << __DCHASH__ << "\n";
#endif

    std::cerr << "\tCOMPILED DATE:" << __DATE__ << "\n";
    std::cerr << "\tCOMPILED TIME:" << __TIME__ << "\n\n";


    std::cerr << "\tUsage:\n";
    std::cerr << "\t\tprogram\n";
    std::cerr << "\t\tprogram format\n";
    std::cerr << "\t\tprogram format filename\n\n";

    std::cerr << "\tExample:\n";
    std::cerr << "\t\tprogram \"COUNT: " << DEFAULT_PLACEHOLDER << "\" OBS.txt\n\n";

    std::cerr << "\tDefault params:\n";
    std::cerr << "\t\tplaceholder = " << DEFAULT_PLACEHOLDER << std::endl;
    std::cerr << "\t\tformat = " << DEFAULT_FORMATTED_TEXT << std::endl;
    std::cerr << "\t\tfilename = " << DEFAULT_FILENAME << std::endl << std::endl;

    std::cerr << "\tSupported games:\n";
    for(const auto &g:games)
        std::cerr << "\t\t" << g.getname() << std::endl;

    std::cerr << "\n\n================== END ==================\n\n";
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

    const std::vector<CSoulGame> games =
    {
        CSoulGame("DarkSoulsIII.exe",{0,0},{0x47572B8,0x98}),
        CSoulGame("DarkSoulsRemastered.exe",{0,0},{0x1C8A530,0x98}),
        CSoulGame("eldenring.exe",{0,0},{0x3D5DF38, 0x94})

    };

    usage(games);

    switch(argc)
    {
    case 3:
        filename=argv[2];
    case 2:
        formatted_text=argv[1];
    case 1:
        break;
    default:
        return 1;
    }

    std::ofstream file(filename);


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

            std::this_thread::sleep_for(GETDEATHCOUNT_SLEEP_TIME);
        }
    }

    return 0;
}
