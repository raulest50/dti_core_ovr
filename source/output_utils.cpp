// output_utils.cpp
#include "output_utils.h"
#include <cstdarg>
#include <cstdio>
#include <fstream>

/**
 * @brief Prints formatted output to a file, similar to printf but writing to a file
 * 
 * @param filepath Path to the file where output will be written
 * @param format Format string, same as printf
 * @param ... Variable arguments to be formatted
 * @return int Number of characters written, or negative value if an error occurred
 */
int file_printf(const char* filepath, const char* format, ...) {
    // Open the file for writing (will overwrite existing content)
    FILE* file = std::fopen(filepath, "w");
    if (!file) {
        std::fprintf(stderr, "Error: cannot open file %s for writing\n", filepath);
        return -1;
    }

    // Format and write the string
    va_list args;
    va_start(args, format);
    int result = std::vfprintf(file, format, args);
    va_end(args);

    // Close the file
    std::fclose(file);
    
    return result;
}

/**
 * @brief Appends formatted output to a file, similar to printf but appending to a file
 * 
 * @param filepath Path to the file where output will be appended
 * @param format Format string, same as printf
 * @param ... Variable arguments to be formatted
 * @return int Number of characters written, or negative value if an error occurred
 */
int file_printf_append(const char* filepath, const char* format, ...) {
    // Open the file for appending
    FILE* file = std::fopen(filepath, "a");
    if (!file) {
        std::fprintf(stderr, "Error: cannot open file %s for appending\n", filepath);
        return -1;
    }

    // Format and write the string
    va_list args;
    va_start(args, format);
    int result = std::vfprintf(file, format, args);
    va_end(args);

    // Close the file
    std::fclose(file);
    
    return result;
}