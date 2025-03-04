/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:03:42 by sgabsi            #+#    #+#             */
/*   Updated: 2025/03/04 17:38:40 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <avr/io.h>
#include <util/delay.h>

int is_pressed( int switch_num ) {
    if (!(PIND & (1 << switch_num))) {
        _delay_ms(20);
		if (!(PIND & (1 << switch_num))) {
			return 1;
		}
    }
    return 0;
}

int main( void ) {
	volatile float dc = 0.1f;
	// Source : https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf (page 108)

	DDRB |= (1 << DDB1);					// Activation mode ecriture de la LED

	// Activation du fast Mode
	TCCR1A |= (1 << WGM11); 
	TCCR1B |= (1 << WGM12) | (1 << WGM13);

	TCCR1A |= (1 << COM1A1);				// Permet d'eteindre la LED quand la valeur voulu est atteinte (ici 10% de 1s)
	TCCR1B |= (1 << CS10) | (1 << CS12);	// Prescaler 1024 (F_CPU / 1024)
	
	ICR1 	= (F_CPU / 1024); 				// Sert a delimiter le top du compteur
	
	while (1) {
		if (is_pressed(PIND2)) { 
			dc += 0.1;
			if (dc > 1) { dc = 1; }
		}
		while (!(PIND & (1 << PIND2)));
		if (is_pressed(PIND4)) { 
			dc -= 0.1f;
			if (dc < 0.1) { dc = 0.1; }
		}
		while (!(PIND & (1 << PIND4)));
		OCR1A = dc * ICR1;					// Sert a definir le duty cycle
	}
}