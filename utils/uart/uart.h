/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uart.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:52:06 by sgabsi            #+#    #+#             */
/*   Updated: 2025/03/13 10:26:22 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UART_H
#define UART_H

#include <avr/io.h>

#define BAUD 115200UL
#define MYUBBR (((float)(F_CPU) / (16UL * BAUD)) - 0.5)

/**
* @brief Initializes the UART (Universal Asynchronous Receiver-Transmitter) interface in read mode.
*
* This function sets up the UART hardware for communication in read mode. It configures the
* necessary registers and settings to enable UART functionality for receiving data. This function
* should be called before any UART read operations are performed.
*/
void uart_init_r ( void );

/**
 * @brief Initializes the UART (Universal Asynchronous Receiver-Transmitter) interface in write mode.
 *
 * This function sets up the UART hardware for communication in write mode. It configures the
 * necessary registers and settings to enable UART functionality for transmitting data. This function
 * should be called before any UART write operations are performed.
 */
 void uart_init_w ( void );
 
/**
 * @brief Initializes the UART (Universal Asynchronous Receiver-Transmitter) interface in read/write mode.
 *
 * This function sets up the UART hardware for communication in both read and write modes. It configures the
 * necessary registers and settings to enable UART functionality for both receiving and transmitting data. This function
 * should be called before any UART read or write operations are performed.
 */
void uart_init_rw ( void );

/**
 * @brief Reads a character from the UART interface.
 *
 * This function reads a single character from the UART interface. It waits until a character is received
 * and then returns it. This function should be called after the UART has been initialized in read mode.
 *
 * @return The character read from the UART interface.
 */
char read_char ( void );

/**
 * @brief Transmits a character via the UART interface.
 *
 * This function sends a single character through the UART interface. It waits until the UART is ready
 * to transmit and then sends the character. This function should be called after the UART has been initialized
 * in write mode.
 *
 * @param c The character to be transmitted.
 */
void uart_printchar ( const char c );

/**
 * @brief Transmits a null-terminated string via the UART interface.
 *
 * This function sends a null-terminated string through the UART interface. It transmits each character
 * of the string one by one until the null terminator is encountered. This function should be called after
 * the UART has been initialized in write mode.
 *
 * @param str The null-terminated string to be transmitted.
 */
void uart_printstr( const char* str );

/**
 * @brief Prints a newline character to the UART interface.
 *
 * This function sends a newline character ('\n') followed by a carriage return ('\r') to the UART interface,
 * which is typically used to move the cursor to the beginning of the next line.
 * It can be useful for formatting output in a terminal or serial console.
 */
void uart_println ( void );

/**
 * @brief Prints an unsigned integer via the UART interface.
 *
 * This function converts an unsigned integer to its string representation and sends it through the UART interface.
 * This function should be called after the UART has been initialized in write mode.
 *
 * @param value The unsigned integer to be printed.
 */
void print_uint ( const uint32_t value );

/**
 * @brief Prints a signed integer via the UART interface.
 *
 * This function converts a signed integer to its string representation and sends it through the UART interface.
 * This function should be called after the UART has been initialized in write mode.
 *
 * @param value The signed integer to be printed.
 */
void print_int ( const int value );

/**
 * @brief Prints a floating-point number via the UART interface.
 *
 * This function converts a floating-point number to its string representation and sends it through the UART interface.
 * This function should be called after the UART has been initialized in write mode.
 *
 * @param value The floating-point number to be printed.
 */
void print_float ( const float value );

/**
 * @brief Prints a hexadecimal number via the UART interface.
 *
 * This function converts a hexadecimal number to its string representation and sends it through the UART interface.
 * The output can be in uppercase or lowercase depending on the parameter.
 * This function should be called after the UART has been initialized in write mode.
 *
 * @param value The hexadecimal number to be printed.
 * @param uppercase If non-zero, the hexadecimal digits will be printed in uppercase; otherwise, they will be printed in lowercase.
 */
void print_hexa ( const unsigned int value, uint8_t uppercase );

/**
 * @brief Prints an unsigned integer followed by a newline via the UART interface.
 *
 * This function converts an unsigned integer to its string representation, sends it through the UART interface,
 * and then sends a newline character. This function should be called after the UART has been initialized in write mode.
 *
 * @param value The unsigned integer to be printed.
 */
void println_uint ( const uint32_t value );

/**
 * @brief Prints a signed integer followed by a newline via the UART interface.
 *
 * This function converts a signed integer to its string representation, sends it through the UART interface,
 * and then sends a newline character. This function should be called after the UART has been initialized in write mode.
 *
 * @param value The signed integer to be printed.
 */
void println_int ( const int value );

/**
 * @brief Prints a floating-point number followed by a newline via the UART interface.
 *
 * This function converts a floating-point number to its string representation, sends it through the UART interface,
 * and then sends a newline character. This function should be called after the UART has been initialized in write mode.
 *
 * @param value The floating-point number to be printed.
 */
void println_float ( const float value );

/**
 * @brief Prints a hexadecimal number followed by a newline via the UART interface.
 *
 * This function converts a hexadecimal number to its string representation, sends it through the UART interface,
 * and then sends a newline character. The output can be in uppercase or lowercase depending on the parameter.
 * This function should be called after the UART has been initialized in write mode.
 *
 * @param value The hexadecimal number to be printed.
 * @param uppercase If non-zero, the hexadecimal digits will be printed in uppercase; otherwise, they will be printed in lowercase.
 */
void println_hexa ( const unsigned int value, uint8_t uppercase );

#endif // !UART_H