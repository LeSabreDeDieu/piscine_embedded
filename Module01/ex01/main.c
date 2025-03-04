/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:03:42 by sgabsi            #+#    #+#             */
/*   Updated: 2025/03/04 17:04:17 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <avr/io.h>

void timer1_init() {
	// Source : https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf (page 108)
	
	DDRB |= (1 << DDB1);					// Activation mode ecriture de la LED
	TCCR1B |= (1 << WGM12);  				// Mode CTC (Clear Timer on Compare Match)
	TCCR1B |= (1 << CS12) | (1 << CS10); 	// Prescaler 1024 (F_CPU / 1024)
	OCR1A 	= (F_CPU / 1024) / 2; 			// (F_CPU / 1024) nous permet d'avoir un clignement par seconde et /2 permet d'avoir 0.5
	TCCR1A |= (1 << COM1A0); 				// Toggle OC1A (PB1) à chaque match avec OCR1A
}

int main( void ) {
	timer1_init();
	while (1);
}