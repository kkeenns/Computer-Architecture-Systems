/*
 * Programming Assignment 1
 * CS 211 Spring 2025 (Sections 5-8)
 */
#ifndef PA1_H
#define PA1_H

#include <stdint.h>
#include <stdbool.h>

/*
 * Supported operations (currently just ADD and SUB)
 */
enum operation_code
{
    OP_ADD = '+', // ascii codepoint for '+'
    OP_SUB = '-', // ascii codepoint for '-'
};

/**
 * Enables us to return two values from parsing:
 *    value: the numeric value from parsing the string
 *    is_malformed: whether the string was malformed
 *
 * Note: value is ignored if is_malformed is true
 */
struct parse_result
{
    uint64_t value;
    bool is_malformed;
};

/******************************************************************************
 * Provided Functions: 
 *     Consult these as examples for how to work with the data
 *     See pa1.c for function descriptions and examples
 ******************************************************************************/
bool is_hexdigit(char c);

/******************************************************************************
 * Your Assignment:
 *     Implement the following functions in pa1.c
 *     See pa1.c for function descriptions and examples
 ******************************************************************************/
bool is_valid_digit(char c, uint32_t base);
uint64_t digit_to_int(char c);
uint32_t get_num_bits_per_digit(uint32_t base);
uint64_t get_max_representable_2C_value(uint32_t bit_width);
uint64_t get_min_representable_2C_value(uint32_t bit_width);
struct parse_result parse_operand(uint32_t bit_width, const char operand[], int operand_len);
uint64_t perform_operation(uint32_t bit_width, enum operation_code operation, uint64_t operand_0, uint64_t operand_1);

#endif /* PA1_H */