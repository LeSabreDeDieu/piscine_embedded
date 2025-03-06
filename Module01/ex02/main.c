/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:03:42 by sgabsi            #+#    #+#             */
/*   Updated: 2025/03/05 12:44:48 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <avr/io.h>

void timer1_init() {
	// Source : https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf (page 108)

	DDRB |= (1 << DDB1);					// Activation mode ecriture de la LED

	// Activation du fast PWM Mode
	TCCR1A |= (1 << WGM11); 
	TCCR1B |= (1 << WGM12) | (1 << WGM13);

	TCCR1A |= (1 << COM1A1);				// Permet d'eteindre la LED quand la valeur voulu est atteinte (ici 10% de 1s)
	TCCR1B |= (1 << CS10) | (1 << CS12);	// Prescaler 1024 (F_CPU / 1024)
	
	ICR1 	= (F_CPU / 1024); 				// Sert a delimiter le top du compteur
	OCR1A 	= 0.1 * ICR1;					// Sert a definir le duty cycle
}

int main( void ) {
	timer1_init();
	while (1);
}