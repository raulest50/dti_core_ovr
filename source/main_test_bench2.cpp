// main_test_bench2.cpp
#include "step_propagators.h"
#include "output_utils.h"
#include <cstdio>

int main() {
    printf("Hello World from console!\n");

    // Test file_printf function (creates a new file)
    file_printf("output_test_result.txt", "Hello World from file_printf!\n");

    // Test file_printf_append function (appends to the existing file)
    file_printf_append("output_test_result.txt", "This line was appended using file_printf_append.\n");

    // Test formatting capabilities
    file_printf_append("output_test.txt", 
                      "Formatted output: %d, %f, %s\n", 
                      42, 3.14159, "string example");

    printf("Output has been written to output_test_result.txt\n");

    return 0;
}
