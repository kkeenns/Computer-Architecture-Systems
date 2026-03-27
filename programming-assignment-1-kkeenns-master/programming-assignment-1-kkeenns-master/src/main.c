/*
 * Programming Assignment 1
 * CS 211 Spring 2026 (Sections 5-8)
 */
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <inttypes.h>

#include "pa1.h"

/* ANSI color codes used for printing out colored text to the Linux terminal */
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

/*
 * This program simulates N-bit arithmetic operations (0 < N <= 64) with operands 
 * provided as ASCII strings.
 * 
 * Input: 
 *     - bit_width: the number of bits to use for the operation
 *     - operation: the operation to perform
 *     - operand_0: the first operand given as an ASCII string
 *     - operand_1: the second operand given as an ASCII string
 * 
 * Step 1: parse_operand()
 *     - parse each operand into a raw bit representation stored as a uint64_t.
 *     - if the string is invalid, return 0 and an error.
 *     - if the string contains too many bits (e.g., 8 bits for a 5-bit bit_width), keep only the least significant bit_width bits (ignore the MSBs).
 *     - if the string is too short, pad the most significant bits with 0s.
 * 
 * Step 2: perform_operation()
 *     - perform an ADD or SUB operation on the two operands using two's complement bit_width arithmetic
 *     - if the result causes an overflow, clamp the result to the maximum/minimum representable two's complement value.
 *     
 * Examples:
 *    -  bit_width=5, ADD
 *        - operand_0: "0x10" -> Parsed: (uint64_t)0x0000_0000_0000_0010 // decimal 2
 *        - operand_1: "0xff" -> Parsed: (uint64_t)0x0000_0000_0000_001f // decimal -1
 *        - result: (uint64_t)0x0000_0000_0000_0001 // decimal 1
 *    -  bit_width=32, ADD
 *        - operand_0: "0x10" -> Parsed: (uint64_t)0x0000_0000_0000_0010 // decimal 2
 *        - operand_1: "0xff" -> Parsed: (uint64_t)0x0000_0000_0000_00ff // decimal 255
 *        - result: (uint64_t)0x0000_0000_0000_0101 // decimal 257
 *
 * Operands are to be given in base 2, 4, 8, or 16, prefixed by "0[bqoxBQOX]" followed by digits valid for the given base.
 *     - binary (e.g., 0b1101, 0B1101)
 *     - quaternary (e.g., 0q12, 0Q12)
 *     - octal (e.g., 0o37, 0O37)
 *     - hexadecimal (e.g., 0x1a, 0X1A)
 * Any operand not in this format is considered malformed.
 */

/* Possible error cases for parse_operand() */
enum test_error_code 
{
    ERROR_NONE           = 0, 
    ERROR_OP_0_MALFORMED = 1,
    ERROR_OP_1_MALFORMED = 2
};

/* Definition of test cases for you to work with*/
struct pa1_test_case
{
    // inputs
    uint32_t bit_width;
    enum operation_code operation;
    const char *operand_0;
    const char *operand_1;

    // results
    uint64_t expected_operand_0;
    uint64_t expected_operand_1;
    uint64_t expected_result;
    enum test_error_code expected_error;
};

struct pa1_test_case test_cases[] = 
{
    // ADD tests
    {1,  OP_ADD, "0b1", "0B0", 0x1, 0x0, 0x1, ERROR_NONE}, // (-1) + 0 = -1
    {64, OP_ADD, "0b1111111111111111111111111111111111111111111111111111111111111111", "0x1", 0xffffffffffffffff, 0x1, 0x0, ERROR_NONE}, // (-1) + 1 = 0
    /* TODO: check other bit widths and supported operand formats... */

    // SUB tests
    {64, OP_SUB, "0xffffffffffffffff", "0xffffffffffffffff", 0xffffffffffffffff, 0xffffffffffffffff, 0x0, ERROR_NONE}, // (-1) - (-1) = 0
    /* TODO: check other SUB cases... */

    // input string too long 
    {1,  OP_ADD, "0b01001010",    "0b110101", 0x0,  0x1,  0x1,  ERROR_NONE},  // 0 + 1 = 1
    /* TODO: check other cases */
    
    // problem cases
    {12, OP_SUB, "",    "0b1",  0, 1, 0, ERROR_OP_0_MALFORMED},
    /* TODO: check other problem cases */
    
    /*
     * TODO: Add your own test cases here! The test cases above are just examples. They will not be graded.
     *
     * Hint: make sure to test all possible scenarios, including arithmetic overflows, malformed strings, bit widths, etc.
     */
};

/* 
 * Runs a single test case. Returns true if the test case passed, 
 * false otherwise. 
 */
bool run_pa1_test_case(struct pa1_test_case tc) 
{
    // sanity-check the test case
    assert(tc.bit_width > 0 && tc.bit_width <= 64);
    assert(tc.operation == OP_ADD || tc.operation == OP_SUB);
    
    // parse both operands
    struct parse_result operand_0 = parse_operand(tc.bit_width, tc.operand_0, strlen(tc.operand_0));
    if(operand_0.is_malformed) 
    {
        if(tc.expected_error != ERROR_OP_0_MALFORMED) {
            printf("    Operand 0 reported malformed: (%s @ %"PRIu32" bits) but expected no error\n", tc.operand_0, tc.bit_width);
            return false;
        }
        return true;
    }
    if(operand_0.value != tc.expected_operand_0) 
    {
        printf("    Operand 0 parsed value: 0x%"PRIx64" but expected 0x%"PRIx64"\n", operand_0.value, tc.expected_operand_0);
        return false;
    }

    struct parse_result operand_1 = parse_operand(tc.bit_width, tc.operand_1, strlen(tc.operand_1));
    if(operand_1.is_malformed) 
    {
        if(tc.expected_error != ERROR_OP_1_MALFORMED) {
            printf("    Operand 1 reported malformed: (%s @ %"PRIu32" bits) but expected no error\n", tc.operand_1, tc.bit_width);
            return false;
        }
        return true;
    }
    if(operand_1.value != tc.expected_operand_1) 
    {
        printf("    Operand 1 parsed value: 0x%"PRIx64" but expected 0x%"PRIx64"\n", operand_1.value, tc.expected_operand_1);
        return false;
    }
    
    // perform the requested operation
    uint64_t result = perform_operation(tc.bit_width, tc.operation, operand_0.value, operand_1.value);
    if(result != tc.expected_result) {
        printf("    Computed: 0x%"PRIx64" %c 0x%"PRIx64" = 0x%"PRIx64" but expected 0x%"PRIx64"\n",
            operand_0.value, tc.operation, operand_1.value, result, tc.expected_result);
        return false;
    }

    // success!
    return true;
}

/*
 * Runs all test cases and reports the results
 */
int main(int argc, char **argv)
{
    // run each test case and report any failed test cases
    uint32_t passed_tests = 0;
    size_t num_test_cases = sizeof(test_cases) / sizeof(test_cases[0]);
    for(uint32_t test_case_idx = 0; test_case_idx < num_test_cases; test_case_idx++)
    {
        printf("> Running test_cases[%2u / %2zu]: \"%s %c %s = 0x%"PRIx64"\" @ %u bits\n",
            test_case_idx, num_test_cases, 
            test_cases[test_case_idx].operand_0,
            test_cases[test_case_idx].operation,
            test_cases[test_case_idx].operand_1,
            test_cases[test_case_idx].expected_result,
            test_cases[test_case_idx].bit_width);
        
        if(run_pa1_test_case(test_cases[test_case_idx]))
            passed_tests++;
        else
            printf("%stest_cases[%2u] failed!%s\n", ANSI_COLOR_RED, test_case_idx, ANSI_COLOR_RESET);
    }

    puts("Testing complete!");
    if(passed_tests == num_test_cases)
        printf("%sAll %u test cases passed!%s\n", ANSI_COLOR_GREEN, passed_tests, ANSI_COLOR_RESET);
    else
        printf("%sPassed %u of %zu test cases!%s\n", ANSI_COLOR_RED, passed_tests, num_test_cases, ANSI_COLOR_RESET);
    return EXIT_SUCCESS;
}