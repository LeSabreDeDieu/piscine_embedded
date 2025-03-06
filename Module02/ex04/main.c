/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:03:42 by sgabsi            #+#    #+#             */
/*   Updated: 2025/03/06 11:10:37 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BAUD 115200UL
#define MYUBBR ((float)(F_CPU) / (16UL * BAUD)) - 1
#define USERNAME "sgabsi"
#define PASSWORD "PaSsWoRd"

void uart_init ( unsigned int ubrr ) {
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	UCSR0B |= (1<<RXEN0) | (1<<TXEN0);
	UCSR0C |= (1<<UCSZ00) | (1<<UCSZ01);
}

void uart_tx ( char data ) {
	while ( !(UCSR0A & (1<<UDRE0)) );
	UDR0 = data;
	while ( !(UCSR0A & (1<<TXC0)) );
}

char uart_rx(void) {
	while ( !(UCSR0A & (1<<RXC0)) );
	return UDR0;
}

unsigned int round_ubbr() {
    if (MYUBBR >= 0)
        return (unsigned int)(MYUBBR + 0.5f);
    else
        return (unsigned int)(MYUBBR - 0.5f);
}

int strcmp(const char *s1, const char *s2) {
	int i = 0;
	while (s1[i] && s1[i] == s2[i]) { i++; }
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void uart_printstr(const char* str) {
	const char *tmp = str;
	while (*tmp) {
		uart_tx(*tmp);
		tmp++;
	}
}

int main(void) {
	int i;
	char c;
	char username[16];
	char password[16];

	uart_init(round_ubbr());

	DDRB |= (1 << DDB0) | (1 << DDB1) | (1 << DDB2) | (1 << DDB4);

	do {
		uart_printstr("Enter your login:\n\r\t");

		// USERNAME LOOP
		i = 0;
		c = 0;
		uart_printstr("username: ");
		while (c != '\n' && i < 15) {
			c = uart_rx();
			if (c == '\r') break;
			else if ((c == '\b' || c == 127) && i > 0) { 
				uart_printstr("\b \b");
				i--;
				continue;
			}
			else if ((c == '\b' || c == 127)) {
				continue;
			}
			else if (c == 27) { break; }
			uart_tx(c);
			username[i++] = c;
		}
		username[i] = '\0';

		if (c == 27) { break; }

		// PASSWORD LOOP
		i = 0;
		c = 0;
		uart_printstr("\n\r\tpassword: ");
		while (c != '\n' && i < 15) {
			c = uart_rx();
			if (c == '\r') break;
			else if ((c == '\b' || c == 127) && i > 0) { 
				uart_printstr("\b \b");
				i--;
				continue;
			}
			else if ((c == '\b' || c == 127)) {
				continue;
			}
			else if (c == 27) { break; }
			uart_tx('*');
			password[i++] = c;
		}

		if (c == 27) { break; }

		password[i] = '\0';

		uart_printstr("\n\r");
		
		// Vérification des identifiants
		if (strcmp(username, USERNAME) != 0 || strcmp(password, PASSWORD) != 0) {
			uart_printstr("Bad combination username/password\n\r");
			for (int j = 0; j < 30; j++) {
				PORTB |= (1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB4);
				_delay_ms(50);
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB4));
				_delay_ms(50);
			}
		}

	} while (strcmp(username, USERNAME) != 0 || strcmp(password, PASSWORD) != 0);
	
	if (c != 27){
		uart_printstr("Hello ");
		uart_printstr(USERNAME);
		uart_printstr("!\n\rShall we play a game?\n\r");
	}

	while (1) {
		PORTB |= (1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB4);
		_delay_ms(1000);
		PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB4));
		_delay_ms(1000);
	};
}

