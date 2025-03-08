/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayfallahgabsi <sayfallahgabsi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:20:03 by sayfallahga       #+#    #+#             */
/*   Updated: 2025/03/07 15:08:32 by sayfallahga      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile uint8_t val = 0;

ISR(INT0_vect) {
	_delay_ms(20);
	if (!(PIND & (1 << PIND2))) {
		val++;
		PORTB = (PORTB & ~((1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB4))) |
					((val & 1 << 0)) |
					((val & 1 << 1)) |
					((val & 1 << 2)) |
					((val & 1 << 3)) << 1;
	}
}

ISR(PCINT2_vect) {
	_delay_ms(20);
	if (!(PIND & (1 << PIND4))) {
		val--;
		PORTB = (PORTB & ~((1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB4))) |
					((val & 1 << 0)) |
					((val & 1 << 1)) |
					((val & 1 << 2)) |
					((val & 1 << 3)) << 1;
	}
}

int main() {
    DDRB |= ((1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB4));
	PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB4));

	// External Interrupt Control Register A
    // Init the register EICRA to switch 1
    EICRA |= (1 << ISC01);
	// External Interrupt Mask Register
    // init the register mask EIMSK to INT0 (it's the pin that communicate with the switch 1)
    EIMSK |= (1 << INT0);

	// Pin Change Interrupt Control Register
	// Init the register EICRA to switch 2
	PCICR |= (1 << PCIE2);
	// Pin Change Mask Register 2
	// init the register mask PCMSK2 to PCINT20 (it's the pin that communicate with the switch 2)
	PCMSK2 |= (1 << PCINT20);

    sei();

    while (1);
}
