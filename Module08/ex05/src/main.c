/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:15:51 by sgabsi            #+#    #+#             */
/*   Updated: 2025/03/14 21:01:31 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

#define R 0
#define G 1
#define B 2

uint8_t select_led = 0;
uint8_t select_rgb = 0;

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
    uint8_t RGB[3] = {0};
	level_POT = ADC_read(0);
	
    switch (select_rgb) {
        case R:
            RGB[0] = level_POT; 
            RGB[1] = LED_STATE[select_led].green;
            RGB[2] = LED_STATE[select_led].blue;
            break;
        case G:
            RGB[0] = LED_STATE[select_led].red; 
            RGB[1] = level_POT;
            RGB[2] = LED_STATE[select_led].blue;
            break;
        case B:
            RGB[0] = LED_STATE[select_led].red;
            RGB[1] = LED_STATE[select_led].green;
            RGB[2] = level_POT;
            break;
    }
    set_LED_state(select_led, 31, RGB[0], RGB[1], RGB[2]);
    on_LED();
	_delay_ms(50);
}

ISR(INT0_vect) {
	_delay_ms(20);
	if (!(PIND & (1 << PIND2))) {
        select_rgb++;
        if (select_rgb == 3) select_rgb = 0;
	}
}

ISR(PCINT2_vect) {
	_delay_ms(20);
	if (!(PIND & (1 << PIND4))) {
        select_led++;
        if (select_led == 3) select_led = 0;
	}
}

void init_switch ( void ) {
    // External Interrupt Control Register A
    // Init the register EICRA to switch 1
    EICRA |= (1 << ISC01);
	// External Interrupt Mask Register
    // init the register mask EIMSK to INT0 (it's the pin that communicate with the switch 1)
    EIMSK |= (1 << INT0);

	// Pin Change Interrupt Control Register
	// Init the register EICRA to switch 2
	PCICR |= (1 << PCIE2);
	// Pin Change Mask Register 2
	// init the register mask PCMSK2 to PCINT20 (it's the pin that communicate with the switch 2)
	PCMSK2 |= (1 << PCINT20);
}

int main( void )
{
    init_ADC();
	SPI_MasterInit();
    init_switch();

	sei();

	ADC_read(0);
	while (1);
}
