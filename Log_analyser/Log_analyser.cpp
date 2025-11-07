#include "Log_analyser.h"

bool parse_datetime(const std::string& datetime_str, std::tm& time_struct) {
    std::istringstream ss(datetime_str);
    ss >> std::get_time(&time_struct, "%H:%M:%S");
    return !ss.fail();
}

void print_menu() {
    std::cout << "\n=== Log Analyzer ===\n"
        << "1. Statistics\n"
        << "2. Search by time\n"
        << "3. Search by string\n"
        << "4. Search by module\n"
        << "5. Search by message type\n"
        << "6. Save result\n"
        << "0. Exit\n"
        << "Choose option: ";
}

void interactive_mode(LogHandler& handler) {
    int choice;
    std::string input;

    while (true) {
        print_menu();
        std::getline(std::cin, input);

        try {
            choice = std::stoi(input);
        }
        catch (...) {
            std::cout << "Invalid input!\n";
            continue;
        }

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

            if (parse_datetime(start_str, start_time) && parse_datetime(end_str, end_time)) {
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

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Need dir path";
        return 1;
    }
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::string dirname = argv[1];

    try {
        LogHandler handler(dirname);
        interactive_mode(handler);
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}