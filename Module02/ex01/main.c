/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:03:42 by sgabsi            #+#    #+#             */
/*   Updated: 2025/03/05 13:38:21 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BAUD 115200UL
#define MYUBBR ((float)(F_CPU) / (16UL * BAUD)) - 1

void uart_init ( unsigned int ubrr ) {
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	UCSR0B |= (1<<TXEN0);
	UCSR0C |= (1<<UCSZ00) | (1<<UCSZ01);
}

void uart_tx ( char data ) {
	while ( !(UCSR0A & (1<<UDRE0)) );
	UDR0 = data;
	while ( !(UCSR0A & (1<<TXC0)) );
}

unsigned int round_ubbr() {
    if (MYUBBR >= 0)
        return (unsigned int)(MYUBBR + 0.5f);
    else
        return (unsigned int)(MYUBBR - 0.5f);
}

void uart_printstr(const char* str) {
	const char *tmp = str;
	while (*tmp) {
		uart_tx(*tmp);
		tmp++;
	}
}

void timer1_init() {
    TCCR1B |= (1 << WGM12);  				// Mode CTC (Clear Timer on Compare Match)
    TCCR1B |= (1 << CS12) | (1 << CS10);	// Prescaler 1024
    OCR1A = 31249;           				// 2 secondes
    TIMSK1 |= (1 << OCIE1A); 				// Activer l'interruption sur OCR1A
    sei();                   				// Activer les interruptions globales
}

ISR(TIMER1_COMPA_vect) {
	uart_printstr("Hello World!\n\r");
}

int main( void ) {
	uart_init(round_ubbr());
	timer1_init();

	while (1);
}