// output_utils.h
#ifndef OUTPUT_UTILS_H
#define OUTPUT_UTILS_H

#include <cstdarg>
#include <cstdio>

/**
 * @brief Prints formatted output to a file, similar to printf but writing to a file
 * 
 * @param filepath Path to the file where output will be written
 * @param format Format string, same as printf
 * @param ... Variable arguments to be formatted
 * @return int Number of characters written, or negative value if an error occurred
 */
int file_printf(const char* filepath, const char* format, ...);

/**
 * @brief Appends formatted output to a file, similar to printf but appending to a file
 * 
 * @param filepath Path to the file where output will be appended
 * @param format Format string, same as printf
 * @param ... Variable arguments to be formatted
 * @return int Number of characters written, or negative value if an error occurred
 */
int file_printf_append(const char* filepath, const char* format, ...);

#endif // OUTPUT_UTILS_H