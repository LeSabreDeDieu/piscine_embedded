/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:03:42 by sgabsi            #+#    #+#             */
/*   Updated: 2025/03/06 12:00:28 by sgabsi           ###   ########.fr       */
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


int main(void) {
	
	DDRD |= (1 << DDD3) | (1 << DDD5) | (1 << DDD6);
	PORTD &= ~((1 << PD3) | (1 << PD5) | (1 << PD6));

	while (1) {
		B_off;
		R_on;
		_delay_ms(1000);

		R_off;
		G_on;
		_delay_ms(1000);

		G_off;
		B_on;
		_delay_ms(1000);
	};
}

