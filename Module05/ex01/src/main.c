/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:09:31 by sayfallahga       #+#    #+#             */
/*   Updated: 2025/03/10 13:57:21 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void init_ADC () {
	//Souce : https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf (page 217)
	ADMUX 	|= (1 << ADLAR) | (1 << REFS0);							// Permet d'activer le mode 8bit (par default il est en mode 10bit)
	ADCSRA 	|= (1 << ADEN) | (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2);	// Permet d'activer l'ADC et de mettre le prescaler sur 128 (pour avoir 150kHz)
}

uint8_t ADC_read(uint8_t channel) {
	// Sélectionne le canal (0 à 7 sur ATmega328P en DIP)
    ADMUX = (ADMUX & 0xF8) | (channel & 0x07);

    // Démarrer la conversion
    ADCSRA |= (1 << ADSC);

    // Attendre la fin de la conversion
    while (ADCSRA & (1 << ADSC));

    // Lire la valeur convertie
    return ADCH;
}

int main( void ) {
	uart_init(round_ubbr());
	init_ADC();

	while (1) {
		print_hex(ADC_read(0));
		uart_printstr(", ");
		print_hex(ADC_read(1));
		uart_printstr(", ");
		print_hex(ADC_read(2));
		uart_printstr("\n\r");
		_delay_ms(20);
	}
}