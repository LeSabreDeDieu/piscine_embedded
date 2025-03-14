/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:15:51 by sgabsi            #+#    #+#             */
/*   Updated: 2025/03/14 17:16:15 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

typedef struct RGB_LED
{
    uint8_t brightness;
    uint8_t red;
    uint8_t green;
    uint8_t blue;
}   RGB_LED;


RGB_LED LED_STATE[3] = {0};

void APA102_sendPixel(uint8_t brightness, uint8_t red, uint8_t green, uint8_t blue) {
    SPI_MasterTransmit(0b11100000 | (brightness & 0b00011111)); // 3 bits "1" + luminosité (5 bits)
    SPI_MasterTransmit(blue);  // Couleur Bleu
    SPI_MasterTransmit(green); // Couleur Vert
    SPI_MasterTransmit(red);   // Couleur Rouge
}

void on_LED ( void ) {
	for (int i = 0; i < 4; i++) {
        SPI_MasterTransmit(0x00);
    }

    // Envoyer la couleur à chaque LED
    for (uint8_t i = 0; i < 3; i++) {
        APA102_sendPixel( LED_STATE[i].brightness,
                          LED_STATE[i].red,
                          LED_STATE[i].green,
                          LED_STATE[i].blue );
    }

    // End Frame (au moins numLEDs/2 bits à 1)
    SPI_MasterTransmit(0xFF);
    SPI_MasterTransmit(0xFF);
}

void set_LED_state(uint8_t led_index, uint8_t brightness, uint8_t red, uint8_t green, uint8_t blue) {
    if (led_index < 3) {
        LED_STATE[led_index].brightness = brightness;
        LED_STATE[led_index].red = red;
        LED_STATE[led_index].green = green;
        LED_STATE[led_index].blue = blue;
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

volatile uint16_t level_POT = 0;

ISR(ADC_vect) {
	set_LED_state(0, 0, 255, 0, 0);
	set_LED_state(1, 0, 255, 0, 0);
	set_LED_state(2, 0, 255, 0, 0);

	level_POT = ADC_read(0);
	
	if (level_POT >= 85) {
		// Action for 33-66% range
		set_LED_state(0, 3, 255, 0, 0);
	} 
	if (level_POT >= 170) {
		// Action for 66-99% range
        set_LED_state(1, 3, 255, 0, 0);
	} 
	if (level_POT >= 255) {
		// Action for 100% range
        set_LED_state(2, 3, 255, 0, 0);
	}
    on_LED();
	_delay_ms(50);
}

int main( void )
{
    init_ADC();
	SPI_MasterInit();

	sei();

	ADC_read(0);
	while (1);
}
