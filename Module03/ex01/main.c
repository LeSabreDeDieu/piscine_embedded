/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:03:42 by sgabsi            #+#    #+#             */
/*   Updated: 2025/03/06 12:09:04 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define R_on 	(PORTD |= (1 << PD5))
#define R_off 	(PORTD &= ~(1 << PD5))

#define G_on 	(PORTD |= (1 << PD6))
#define G_off	(PORTD &= ~(1 << PD6))

#define B_on 	(PORTD |= (1 << PD3))
#define B_off 	(PORTD &= ~(1 << PD3))

void setColorLED( uint8_t R, uint8_t G, uint8_t B ) {
	if ( R > 0 ) R_on; else R_off;
	if ( G > 0 ) G_on; else G_off;
	if ( B > 0 ) B_on; else B_off;
}

int main(void) {
	
	DDRD |= (1 << DDD3) | (1 << DDD5) | (1 << DDD6);
	PORTD &= ~((1 << PD3) | (1 << PD5) | (1 << PD6));

	while (1) {
		setColorLED(1, 0, 0);
		_delay_ms(1000);

		setColorLED(0, 1, 0);
		_delay_ms(1000);

		setColorLED(0, 0, 1);
		_delay_ms(1000);

		setColorLED(1, 1, 0);
		_delay_ms(1000);

		setColorLED(0, 1, 1);
		_delay_ms(1000);

		setColorLED(1, 0, 1);
		_delay_ms(1000);

		setColorLED(1, 1, 1);
		_delay_ms(1000);
	};
}

