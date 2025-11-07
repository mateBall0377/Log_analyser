#include "console_mode.h"


void console_mode(LogHandler& handler, int argc, char** argv) 
{
    std::string output_file;
    bool has_output = false;

    for (int i = 2; i < argc; ++i) 
    {
        std::string arg = argv[i];

        if (arg == "--stat") 
        {
            handler.get_stat();
            has_output = true;
        }
        else if (arg == "--find-time") 
        {   
            std::string start_str = argv[++i], end_str=argv[++i];
            std::tm start_time = {}, end_time = {};
            if (parse_time(start_str, start_time) && parse_time(end_str, end_time)) 
            {
                handler.findbytime(start_time, end_time);
            }
            else 
            {
                std::cout << "Error in time format\n";
            }
            has_output = true;
        }
        else if (arg == "--find-str") 
        {
            if (i + 1 >= argc) {
                throw std::invalid_argument("--find-str requires a text argument");
            }
            handler.findbystr(argv[++i]);
            has_output = true;
        }
        else if (arg == "--find-module") 
        {
            if (i + 1 >= argc) {
                throw std::invalid_argument("--find-module requires a module name");
            }
            handler.findbymodule(argv[++i]);
            has_output = true;
        }
        else if (arg == "--find-type") 
        {
            if (i + 1 >= argc) {
                throw std::invalid_argument("--find-type requires a message type");
            }
            codes_messages code = static_cast<codes_messages>(std::stoi(std::string(argv[++i])));
            handler.findbytype(code);
            has_output = true;
        }
        else if (arg == "--output") 
        {
            if (i + 1 >= argc) {
                throw std::invalid_argument("--output requires a filename");
            }
            output_file = argv[++i];
        }
        else 
        {
            throw std::invalid_argument("Unknown option: " + arg);
        }
    }

        
    if (!output_file.empty() && has_output) 
    {
        handler.write_last_result(output_file);
        std::cout << "Results saved to: " << output_file << std::endl;
    }
    else if (!output_file.empty() && !has_output) 
    {
        std::cout << "Nothing to output\n";
    }
}    