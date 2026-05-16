#include <chrono>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>


bool isFileProvided(const int argc)
{
    if (argc <= 2)
    {
        return false;
    }

    return true;
};

void checkIfFilePathIsValid(const std::string& file_path)
{
    if (!std::filesystem::exists(file_path))
    {
        std::cerr << std::format("No file found with path {}", file_path);
        exit(1);
    }
}


uintmax_t getTotalBytesOfFile(std::istream& file_stream)
{
    const std::istreambuf_iterator<char> it{file_stream}, end;

    return std::distance(it, end);
}

long long getTotalLinesOfFile(std::istream& file_stream)
{
    std::string line{};
    long long total_lines{0};

    while (std::getline(file_stream, line))
    {
        ++total_lines;
    }

    return total_lines;
}

long long getTotalWordsOfFile(std::istream& file_stream)
{
    std::string word{};
    long long total_words{0};

    while (file_stream >> word)
    {
        ++total_words;
    }

    return total_words;
}

long long getTotalCharsOfFile(std::wistream& file_stream)
{
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
        if (isFileProvided(argc))
        {
            checkIfFilePathIsValid(argv[2]);
            std::ifstream file_stream(argv[2]);
            std::cout << std::format("{} {}\n", getTotalBytesOfFile(file_stream), argv[2]);
        }
        else
        {
            std::cout << std::format("{}\n", getTotalBytesOfFile(std::cin));
        }
    }
    else if (command == "-l")
    {
        if (isFileProvided(argc))
        {
            checkIfFilePathIsValid(argv[2]);
            std::ifstream file_stream(argv[2]);
            std::cout << std::format("{} {}\n", getTotalLinesOfFile(file_stream), argv[2]);
        }
        else
        {
            std::cout << std::format("{}\n", getTotalLinesOfFile(std::cin));
        }
    }
    else if (command == "-w")
    {
        if (isFileProvided(argc))
        {
            checkIfFilePathIsValid(argv[2]);
            std::ifstream file_stream(argv[2]);
            std::cout << std::format("{} {}\n", getTotalWordsOfFile(file_stream), argv[2]);
        }
        else
        {
            std::cout << std::format("{}\n", getTotalWordsOfFile(std::cin));
        }
    }
    else if (command == "-m")
    {
        if (isFileProvided(argc))
        {
            checkIfFilePathIsValid(argv[2]);
            std::wifstream file_stream(argv[2]);
            std::cout << std::format("{} {}\n", getTotalCharsOfFile(file_stream), argv[2]);
        }
        else
        {
            std::cout << std::format("{}\n", getTotalCharsOfFile(std::wcin));
        }
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
        std::ifstream file_stream(file_name);

        auto total_lines = getTotalLinesOfFile(file_stream);

        file_stream.clear();
        file_stream.seekg(0, std::ios::beg);
        auto total_words = getTotalWordsOfFile(file_stream);

        file_stream.clear();
        file_stream.seekg(0, std::ios::beg);
        auto total_bytes = getTotalBytesOfFile(file_stream);

        std::cout << std::format("{} {} {} {}\n", total_lines, total_words, total_bytes, file_name);
    }
    else
    {
        std::cerr << std::format("No Valid Arguments Provided. {}\n", valid_arguments_message);
        exit(1);
    }
    return 0;
}
