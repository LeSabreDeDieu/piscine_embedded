/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayfallahgabsi <sayfallahgabsi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:09:31 by sayfallahga       #+#    #+#             */
/*   Updated: 2025/03/07 15:40:08 by sayfallahga      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void init_ADC () {
	//Souce : https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf (page 217)
	ADMUX 	|= (1 << ADLAR) | (1 << REFS0); // Permet d'activer le mode 8bit (par default il est en mode 10bit)
	ADCSRA 	|= (1 << ADEN); // Permet d'activer l'ADC
}

uint8_t ADC_read() {
	ADCSRA	|= (1 << ADSC);
	while (ADCSRA & (1 << ADSC));
	return ADCH;
}

int main( void ) {
	uart_init(round_ubbr());
	init_ADC();

	while (1) {
		uint8_t acd_read = ADC_read();
		print_hex(acd_read);
		_delay_ms(20);
	}
}