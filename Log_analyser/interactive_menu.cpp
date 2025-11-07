#include "interactive_menu.h"

void print_menu()
{
    std::cout << "\n     Log Analyzer\n"
        << "1. Statistics\n"
        << "2. Search by time\n"
        << "3. Search by string\n"
        << "4. Search by module\n"
        << "5. Search by message type\n"
        << "6. Save result\n"
        << "0. Exit\n"
;
}

void interactive_mode(LogHandler& handler)
{
    int choice;
    std::string input;

    while (true) 
    {
        print_menu();
        std::getline(std::cin, input);
        choice = std::stoi(input);
        

        switch (choice) {
        case 1:

            handler.get_stat();
            break;

        case 2: {
            std::string start_str, end_str;
            std::tm start_time = {}, end_time = {};

            std::cout << "Enter start time (HH:MM:SS): ";
            std::getline(std::cin, start_str);
            std::cout << "Enter end time (HH:MM:SS): ";
            std::getline(std::cin, end_str);

            if (parse_time(start_str, start_time) && parse_time(end_str, end_time)) {
                handler.findbytime(start_time, end_time);
            }
            else {
                std::cout << "Invalid time format!\n";
            }
            break;
        }

        case 3: {
            std::string search_str;
            std::cout << "Enter search string: ";
            std::getline(std::cin, search_str);
            handler.findbystr(search_str);
            break;


        }

        case 4: {
            std::string module_name;
            std::cout << "Enter module name: ";
            std::getline(std::cin, module_name);
            handler.findbymodule(module_name);

            break;
        }

        case 5: {
            std::string code_str;
            std::cout << "INFO - 0, DEBUG - 1, WARNING - 2, ERROR -3 , FATAL - 4" << std::endl;
            std::cout << "Enter message type code: ";
            std::getline(std::cin, code_str);
            try {
                codes_messages code = static_cast<codes_messages>(std::stoi(code_str));
                handler.findbytype(code);
            }
            catch (...) {
                std::cout << "Invalid code!\n";
            }

            break;
        }

        case 6: {
            std::string filename;
            std::cout << "Enter filename to save: ";
            std::getline(std::cin, filename);
            handler.write_last_result(filename);
            std::cout << "Result saved!\n";
            break;
        }

        case 0:
            std::cout << "Exiting...\n";
            return;

        default:
            std::cout << "Invalid choice!\n";
        }
    }

}


