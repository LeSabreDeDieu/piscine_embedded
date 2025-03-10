/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:51:37 by sgabsi            #+#    #+#             */
/*   Updated: 2025/03/10 15:11:15 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void init_ADC() {
    // Sélectionne la référence de tension interne à 1.1V
    ADMUX = (1 << REFS1) | (1 << REFS0);

    // Active l'ADC et définit un prescaler de 128 (16 MHz / 128 = 125 kHz)
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint16_t ADC_read(uint8_t channel) {
    // Sélection du canal ADC
    if (channel == 8) { 
        ADMUX = (1 << REFS1) | (1 << REFS0) | (1 << MUX3); // Sélection du capteur interne
    } else {
        ADMUX = (1 << REFS0) | (channel & 0x07); // Sélection du canal externe
    }

    // Attendre que le capteur de température se stabilise
    _delay_ms(10);

    // Démarrer la conversion
    ADCSRA |= (1 << ADSC);

    // Attendre la fin de la conversion
    while (ADCSRA & (1 << ADSC));

    // Lire et retourner la valeur ADC (résolution 10 bits)
    return ADC;
}

int main(void) {
    uart_init(round_ubbr());
    init_ADC();

    while (1) {
        uint16_t TEMP_INT = ADC_read(8);

        uart_printstr(uint32toa((TEMP_INT - 324) / 1.22));
        uart_printstr("\n\r");

        _delay_ms(20); // Pause de 2 ms
    }
}
