/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:52:34 by sgabsi            #+#    #+#             */
/*   Updated: 2025/03/11 11:46:27 by sgabsi           ###   ########.fr       */
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

void init_ADC () {
	//Souce : https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf (page 217)
	ADMUX 	|= (1 << ADLAR) | (1 << REFS0);							// Permet d'activer le mode 8bit (par default il est en mode 10bit)
	ADCSRA 	|= (1 << ADEN) | (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2);	// Permet d'activer l'ADC et de mettre le prescaler sur 128 (pour avoir 150kHz)
	ADCSRA	|= (1 << ADIE);
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

volatile uint8_t level_POT = 0;

ISR(ADC_vect) {
	PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB4));

	level_POT = ADC_read(0);
	
	if (level_POT >= 64) {
		// Action for 25-50% range
		PORTB |= (1 << PB0);
	} 
	if (level_POT >= 128) {
		// Action for 50-75% range
		PORTB |= (1 << PB1);
	} 
	if (level_POT >= 192) {
		// Action for 75-100% range
		PORTB |= (1 << PB2);
	} 
	if (level_POT == 255) {
		// Action for 100% range
		PORTB |= (1 << PB4);
	}
	wheel(level_POT);
	_delay_ms(50);
}

int main(void) {
	init_rgb();
	init_ADC();

	DDRB |= (1 << DDB0) | (1 << DDB1) | (1 << DDB2) | (1 << DDB4);
	
	sei();
	ADC_read(0);
	
	while (1);
}