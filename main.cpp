#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>


void printTotalBytesOfFile(const std::string& file_path)
{
    if (!std::filesystem::exists(file_path))
    {
        std::cout << std::format("No file found with path {}", file_path);
        return;
    }

    std::cout << std::format("{} {}\n", std::filesystem::file_size(file_path), file_path);
}


int main(const int argc, char* argv[])
{
    // ReSharper disable once CppVariableCanBeMadeConstexpr
    const auto valid_arguments_message = std::string("Use ./ccwc -h for list of valid arguments\n");

    if (argc <= 1)
    {
        std::cerr << std::format("No Arguments Provided. {}\n", valid_arguments_message);
        exit(1);
    }

    if (const auto command = std::string(argv[1]); command == "-c")
    {
        if (argc == 2)
        {
            std::cerr << "No file provided.\n";
            exit(1);
        }

        printTotalBytesOfFile(argv[2]);
    }
    else if (command == "-h")
    {
        std::string help_message_for_c_option = "-c [file] will return the number of bytes in the file.";

        std::cout << std::format("{}\n", help_message_for_c_option);
    }
    else
    {
        std::cerr << std::format("No Valid Arguments Provided. {}\n", valid_arguments_message);
        exit(1);
    }
    return 0;
}
