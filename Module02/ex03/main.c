/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayfallahgabsi <sayfallahgabsi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:03:42 by sgabsi            #+#    #+#             */
/*   Updated: 2025/03/07 11:37:30 by sayfallahga      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BAUD 115200UL
#define MYUBBR ((F_CPU / (16UL * BAUD)) + 0.5)

void uart_init(unsigned int ubrr) {
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void uart_tx(char data) {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

char uart_rx(void) {
    while (!(UCSR0A & (1 << RXC0)))
        ;
    return UDR0;
}

int is_alpha(char c) {
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

int is_uppercase(char c) {
    return (c >= 'A' && c <= 'Z');
}

int is_lowercase(char c) {
    return (c >= 'a' && c <= 'z');
}

ISR(USART_RX_vect) {
    char c = uart_rx();
    if (is_alpha(c)) {
        if (is_lowercase(c)) {
            c -= 32;
        } else {
            c += 32;
        }
    }
    uart_tx(c);
}

int main(void) {
    uart_init(MYUBBR);
    sei();
    while (1);
}
