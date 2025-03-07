/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayfallahgabsi <sayfallahgabsi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:03:42 by sgabsi            #+#    #+#             */
/*   Updated: 2025/03/07 13:04:52 by sayfallahga      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

#define LOOP while (1);

void ready( void ) {
	DDRB |= ((1<<PB0) | (1<<PB1) | (1<<PB2) | (1<<PB4));
	PORTB ^= ((1<<PB0) | (1<<PB1) | (1<<PB2) | (1<<PB4));
	_delay_ms(1000);
	PORTB ^= ((1<<PB0) | (1<<PB1) | (1<<PB2) | (1<<PB4));
}

int main(void) {
	pwm_init();
	uart_init(round_ubbr());
	ready();
	sei();
	
	LOOP;
}
