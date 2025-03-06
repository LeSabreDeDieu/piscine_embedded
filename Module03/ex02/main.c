/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:03:42 by sgabsi            #+#    #+#             */
/*   Updated: 2025/03/06 16:52:23 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define R 	(1 << PD5)
#define G 	(1 << PD6)
#define B	(1 << PD3)
#define SET_RGB_LED (DDRD |= R | G | B)

void init_rgb() {
	SET_RGB_LED;
	
	TCCR0A = (1 << WGM00) | (1 << WGM01) | (1 << COM0A1) | (1 << COM0B1);
    TCCR0B = (1 << CS00);

	TCCR2A = (1 << WGM20) | (1 << WGM21) | (1 << COM2B1);
    TCCR2B = (1 << CS20);
}

void set_rgb(uint8_t r, uint8_t g, uint8_t b) {
    OCR0B = r;
	OCR0A = g;
    OCR2B = b;
}

void wheel(uint8_t pos) {
	pos = 255 - pos;

	if (pos < 85) {
		set_rgb(255 - pos * 3, 0, pos * 3);
	} 
	else if (pos < 170) {
		pos = pos - 85;
		set_rgb(0, pos * 3, 255 - pos * 3);
	} 
	else {
		pos = pos - 170;
		set_rgb(pos * 3, 255 - pos * 3, 0);
	}
}

int main(void) {
	init_rgb();

	uint8_t i = 0;
	
	while (1) {
		wheel(i++);
		_delay_ms(50);
	};
}
