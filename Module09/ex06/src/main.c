/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 16:47:30 by sgabsi            #+#    #+#             */
/*   Updated: 2025/03/15 17:06:58 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

#define ZERO    0b00111111
#define ONE     0b00000110
#define TWO     0b01011011
#define THREE   0b01001111    
#define FOUR    0b01100110
#define FIVE    0b01101101
#define SIX     0b01111101
#define SEVEN   0b00000111
#define EIGHT   0b01111111
#define NINE    0b01101111

// Définition des valeurs des chiffres pour l'afficheur 7 segments (anode commune)
const uint8_t digits[10] = {
    ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE
};

// Sélection des digits (assume que D0-D3 sont les sélecteurs des digits)
const uint8_t digit_select[4] = {
    0x7F, // Activer digit 1 (Unité)
    0xBF, // Activer digit 2 (Dizaine)
    0xDF, // Activer digit 3 (Centaine)
    0xEF  // Activer digit 4 (Millier)
};

volatile int counter = 0;

void pca9555_init() {
    i2c_start((SLAVE_ADDR << 1) | 0);
    i2c_write(0x06);  // Configuration des directions des ports
    i2c_write(0x00);  // Port 0 en sortie
    i2c_write(0x00);  // Port 1 en sortie
    i2c_stop();
}

void pca9555_write(uint8_t port0, uint8_t port1) {
    i2c_start((SLAVE_ADDR << 1) | 0);
    i2c_write(0x02);  // Sélection du registre Output Port 0
    i2c_write(port0);
    i2c_write(port1);
    i2c_stop();
}

void display_number(uint16_t number) {
    uint8_t digit[4] = {
        number % 10,         // Unités
        (number / 10) % 10,  // Dizaine
        (number / 100) % 10, // Centaine
        (number / 1000) % 10 // Millier
    };

    // Afficher chaque chiffre séparément pendant 1 seconde
    for (int i = 0; i < 4; i++) {
        pca9555_write(digit_select[i], digits[digit[i]]);
		_delay_ms(2);
        pca9555_write(digit_select[i], 0x00);
    }
}

void init_ADC () {
	//Souce : https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf (page 217)
	ADMUX 	|= (1 << REFS0);										// Permet d'activer le mode 10bit
	ADCSRA 	|= (1 << ADEN) | (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2);	// Permet d'activer l'ADC et de mettre le prescaler sur 128 (pour avoir 150kHz)
}

uint16_t ADC_read(uint8_t channel) {
	// Sélectionne le canal (0 à 5 sur ATmega328P en DIP)
    ADMUX = (ADMUX & 0xF8) | (channel & 0x07);

    // Démarrer la conversion
    ADCSRA |= (1 << ADSC);

    // Attendre la fin de la conversion
    while (ADCSRA & (1 << ADSC));

    // Lire la valeur convertie
    return ADC;
}

int main() {
    i2c_init();
    pca9555_init();
    init_ADC();

    while (1) {
		display_number(ADC_read(0)); // Afficher le numéro actuel
    }
}
