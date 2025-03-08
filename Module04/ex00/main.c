/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayfallahgabsi <sayfallahgabsi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:20:03 by sayfallahga       #+#    #+#             */
/*   Updated: 2025/03/07 15:04:06 by sayfallahga      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

ISR(INT0_vect) {
    PORTB ^= (1 << PB0);
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

    while (1);
}