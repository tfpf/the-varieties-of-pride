#include <climits>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <ios>
#include <iostream>
#include <stdexcept>
#include <string>

#define THROW(exception, message)  \
{  \
    throw exception(std::string(__FILE__) + ':' + std::to_string(__LINE__)  \
                    + ", in function " + __func__ + ". " + message);  \
}

/******************************************************************************
 * Explain how to use this program.
 *****************************************************************************/
void show_help(void)
{
    std::cerr << "Usage:\n";
    std::cerr << "  ./tvop <source_file> [<output_file>]\n";
}

/******************************************************************************
 * Determine from the source code of a TVOP program what has to be done.
 *
 * @param source_file File containing TVOP source code.
 *
 * @return A number indicating which C++ program has to be executed.
 *****************************************************************************/
std::size_t read_source(std::string const& source_file)
{
    std::ifstream source_stream(source_file, std::ios::in | std::ios::binary);
    if(!source_stream.good())
    {
        THROW(std::invalid_argument, "Could not open the file " + source_file + " for reading.")
    }

    // Interpret the contents of the source file as a number.
    std::size_t proxy_index = 0;
    char byte;
    while(source_stream.read(&byte, 1))
    {
        proxy_index = (proxy_index << CHAR_BIT) | byte;
        if(proxy_index > 0xFFFFU)
        {
            THROW(std::runtime_error, "File " + source_file + " is too large.")
        }
    }
    return proxy_index;
}

/******************************************************************************
 * Check whether the specified file is readable.
 *
 * @param fname
 *
 * @return `true` if `fname` can be read, else `false`.
 *****************************************************************************/
bool file_readable(std::string const& fname)
{
    return std::ifstream(fname).good();
}

/******************************************************************************
 * Main function.
 *****************************************************************************/
int main(int const argc, char const* argv[])
{
    if(argc < 2)
    {
        show_help();
        return EXIT_FAILURE;
    }
    std::string source_file = argv[1];
    std::string output_file = (argc < 3) ? "a.out" : argv[2];

    // Is the program valid?
    std::size_t proxy_index = read_source(source_file);
    std::string proxy_source_file = "lib/" + std::to_string(proxy_index) + ".cc";
    if(!file_readable(proxy_source_file))
    {
        THROW(std::invalid_argument, source_file + " is not a valid TVOP source file.")
    }

    // Tell a C++ compiler to compile the proxy program.
    std::string command = "g++ -o " + output_file + ' ' + proxy_source_file + " 2> /dev/null";
    if(std::system(command.c_str()) != EXIT_SUCCESS)
    {
        THROW(std::runtime_error, "C++ compiler reported an error. Perhaps the output file couldn't be written?")
    }
    return EXIT_SUCCESS;
}
