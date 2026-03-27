/*
 * Programming Assignment 1
 * CS 211 Spring 2026 (Sections 5-8)
 */
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>

#include "pa1.h"

/******************************************************************************
 * Provided functions: consult these as examples for how to work with the data
 ******************************************************************************/
/**
 * Input: a single ASCII codepoint, which potentially encodes a hexadecimal digit
 *
 * Output: whether or not that character encodes a valid hexdigit (0-9, a-f, A-F)
 */
bool is_hexdigit(char c)
{
	/* chars represent their codepoints, and the codepoints can be compared just
	like any other number. refer to the ASCII table for more info */
    return 
		(c >= '0' && c <= '9') ||
		(c >= 'a' && c <= 'f') ||
		(c >= 'A' && c <= 'F');
}

/******************************************************************************
 * Your Assignment:
 *     Implement the assigned functions declared in pa1.h. 
 *     You may NOT:
 *      - Use any compiler-supported 128-bit data types (e.g., __int128_t)
 *      - Use macros or functions from any standard library (e.g., <string.h>, <stdio.h>)
 *      - Use dynamic memory allocation (malloc/free)
 *      - Use static or global variables
 *     
 *     Make sure to follow the detailed function specifications.
 *     
 *     Consult the assignment handout for further information
 ******************************************************************************/ 
/**
 * Input: 
 *     c: a single ASCII codepoint, which potentially encodes a valid digit in the given base
 *     base: the base of the number we are working in
 *
 * Output: whether or not that character encodes a valid digit in the given base
 * 
 * Assumptions: 
 *     - base is guaranteed to be one of 2, 4, 8, 16
 */
bool is_valid_digit(char c, uint32_t base)
{
    // TODO: implement me
    return false;
}

/**
 * Input: 
 *     c: a single ASCII codepoint, which encodes a valid digit in the base we are working in
 *
 * Output: the integer value of the given digit
 *
 * Assumptions: 
 *     - c is guaranteed to be a valid digit in the base we are working in
 *
 * Hint: consider why base is not an argument
 */
uint64_t digit_to_int(char c)
{
    // TODO: implement me
    return 0;
}

/**
 * Input: 
 *     base: the base of the number we are working in
 *
 * Output: the number of bits per digit in the given base
 * 
 * Assumptions: 
 *     - base is guaranteed to be one of 2, 4, 8, 16
 */
uint32_t get_num_bits_per_digit(uint32_t base)
{
    // TODO: implement me
    return 0;
}

/**
 * Input: 
 *     bit_width: the number of bits in the 2's complement representation
 *
 * Output: the maximum value that can be represented in the given bit width
 * 
 * Assumptions: 
 *     - bit_width is guaranteed to be in range [1, 64] inclusive
 */
uint64_t get_max_representable_2C_value(uint32_t bit_width)
{
    // TODO: implement me
    return 0;
}

/**
 * Input: 
 *     bit_width: the number of bits in the 2's complement representation
 *
 * Output: the minimum value that can be represented in the given bit width
 * 
 * Assumptions: 
 *     - bit_width is guaranteed to be in range [1, 64] inclusive
 */
uint64_t get_min_representable_2C_value(uint32_t bit_width)
{
    // TODO: implement me
    return 0;
}



/**
 * Input: 
 *     bit_width: the number of bits in the 2's complement representation
 *     operand: the operand string (e.g. "0b101", "0q123", "0o777", "0xabc")
 *     operand_len: the number of characters in the operand string (not including the null terminator)
 *
 * Output: the parsed value and whether it is malformed
 *     - if the operand is malformed, return {.value = 0, .is_malformed = true}
 *     - if the operand is valid, return {.value = <value>, .is_malformed = false}
 *     - if the operand is valid, but has more digits than can be represented in the given bit width, ignore the extra most significant bits
 *         - all extra bits beyond bit_width must be set to zero (i.e., do not sign extend the representation)
 *     - valid inputs include prefixes of {0b, 0B, 0q, 0Q, 0o, 0O, 0x, 0X} followed by at least one valid digit in the corresponding base
 * 
 * Assumptions: 
 *     - bit_width is guaranteed to be in range [1, 64] inclusive
 *     - operand is guaranteed to be a null-terminated C string
 *     - operand_len is guaranteed to match the length of the operand string (not including the null terminator)
 *
 * Examples of operand strings:
 *     - Valid: {"0b101", "0B101", "0q123", "0Q123", "0o777", "0O777", "0xabc", "0Xabc"}
 *     - Invalid: {"", "0b", "gg", "OX0"}
 */
struct parse_result parse_operand(uint32_t bit_width, const char operand[], int operand_len)
{
    // TODO: check for a malformed input string
    int num_digits = 0;

    // TODO: extract the digits from the string
    for(int digit_idx = 0; digit_idx < num_digits; digit_idx++)
    {
        // TODO: check and parse the digit
    }

    return (struct parse_result){.value = 0, .is_malformed = true};
}



/**
 * Input: 
 *     bit_width: the number of bits in the 2's complement representation
 *     operation: the operation to perform
 *     operand_0: the first operand
 *     operand_1: the second operand
 *
 * Output: the result of the operation
 *     - if the operation results in an overflow or underflow, clamp the result to the min/max representable 2s complement value
 *     - all extra bits beyond bit_width must be set to zero (i.e., do not sign extend the representation)
 *
 * Assumptions: 
 *     - bit_width is guaranteed to be in range [1, 64] inclusive
 *     - operand_0 and operand_1 are guaranteed to be in the format returned by parse_operand
 */
uint64_t perform_operation(uint32_t bit_width, enum operation_code operation, uint64_t operand_0, uint64_t operand_1)
{
    // TODO: perform the relevant operation
    uint64_t result = 0;
    
    // TODO: return the result clamped to the representable bit_width values
    return result;
}