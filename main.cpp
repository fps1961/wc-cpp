#include <chrono>
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


uintmax_t getTotalBytesOfFile(const std::string& file_path)
{
    return std::filesystem::file_size(file_path);
}

long long getTotalLinesOfFile(const std::string& file_path)
{
    std::ifstream file_stream(file_path);

    std::string line{};
    long long total_lines{0};

    while (std::getline(file_stream, line))
    {
        ++total_lines;
    }

    return total_lines;
}

long long getTotalWordsOfFile(const std::string& file_path)
{
    std::ifstream file_stream(file_path);

    std::string word{};
    long long total_words{0};

    while (file_stream >> word)
    {
        ++total_words;
    }

    return total_words;
}

long long getTotalCharsOfFile(const std::string& file_path)
{
    std::wifstream file_stream(file_path);
    file_stream.imbue(std::locale(""));
    std::noskipws(file_stream);

    wchar_t c{};
    long long total_chars{0};

    while (file_stream >> c)
    {
        ++total_chars;
    }

    return total_chars;
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
        std::cout << std::format("{} {}\n", getTotalBytesOfFile(argv[2]), argv[2]);
    }
    else if (command == "-l")
    {
        checkIfFileProvided(argc);
        std::cout << std::format("{} {}\n", getTotalLinesOfFile(argv[2]), argv[2]);
    }
    else if (command == "-w")
    {
        checkIfFileProvided(argc);
        std::cout << std::format("{} {}\n", getTotalWordsOfFile(argv[2]), argv[2]);
    }
    else if (command == "-m")
    {
        checkIfFileProvided(argc);
        std::cout << std::format("{} {}\n", getTotalCharsOfFile(argv[2]), argv[2]);
    }
    else if (command == "-h")
    {
        std::string c_option = "-c [file_path] will return the number of bytes in the file.";
        std::string l_option = "-l [file_path] will return the number of lines in the file.";
        std::string w_option = "-w [file_path] will return the number of words in the file.";
        std::string m_option = "-m [file_path] will return the number of characters in the file.";

        std::cout << std::format("{}\n{}\n{}\n{}\n", c_option, l_option, w_option, m_option);
    }
    else if (argc == 2)
    {
        checkIfFilePathIsValid(argv[1]);
        std::string file_name = argv[1];
        std::cout << std::format("{} {} {} {}\n", getTotalLinesOfFile(file_name), getTotalWordsOfFile(file_name),
                                 getTotalBytesOfFile(file_name), file_name);
    }
    else
    {
        std::cerr << std::format("No Valid Arguments Provided. {}\n", valid_arguments_message);
        exit(1);
    }
    return 0;
}
