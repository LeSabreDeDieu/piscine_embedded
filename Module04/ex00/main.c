/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:20:03 by sayfallahga       #+#    #+#             */
/*   Updated: 2025/03/10 13:00:25 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile uint8_t switch_flag = 0; 

ISR(INT0_vect) {
    switch_flag = 1;
}

int main() {
    DDRB |= (1 << PB0);

    // External Interrupt Control Register A
    // Init the register EICRA to switch 1
    EICRA |= (1 << ISC01);

    // External Interrupt Mask Register
    // init the register mask EIMSK to INT0 (it's the pin that communicate with the switch)
    EIMSK |= (1 << INT0);

    sei();

    while (1) {
        if (switch_flag) {
            PORTB ^= (1 << PB0);
            _delay_ms(150);
            switch_flag = 0;
        }
    };
}