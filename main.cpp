#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>


void checkIfFileProvided(const int argc)
{
    if (argc <= 2)
    {
        std::cerr << "No file provided.\n";
        exit(1);
    }
};

void checkIfFilePathIsValid(const std::string& file_path)
{
    if (!std::filesystem::exists(file_path))
    {
        std::cerr << std::format("No file found with path {}", file_path);
        exit(1);
    }
}


void printTotalBytesOfFile(const std::string& file_path)
{
    std::cout << std::format("{} {}\n", std::filesystem::file_size(file_path), file_path);
}

void printTotalLinesOfFile(const std::string& file_path)
{
    std::ifstream file_stream(file_path);

    std::string line{};
    long long total_lines{0};

    while (std::getline(file_stream, line))
    {
        ++total_lines;
    }

    std::cout << std::format("{} {}\n", total_lines, file_path);
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
        checkIfFileProvided(argc);
        printTotalBytesOfFile(argv[2]);
    }
    else if (command == "-l")
    {
        checkIfFileProvided(argc);
        printTotalLinesOfFile(argv[2]);
    }
    else if (command == "-h")
    {
        std::string c_option = "-c [file_path] will return the number of bytes in the file.";
        std::string l_option = "-l [file_path] will return the number of lines in the file.";

        std::cout << std::format("{}\n{}\n", c_option, l_option);
    }
    else
    {
        std::cerr << std::format("No Valid Arguments Provided. {}\n", valid_arguments_message);
        exit(1);
    }
    return 0;
}
