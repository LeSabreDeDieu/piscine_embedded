/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:49:04 by sgabsi            #+#    #+#             */
/*   Updated: 2025/03/15 14:01:57 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <avr/io.h>
#include <util/delay.h>

// Voir exercice 3 pour l'explication
int is_released( int switch_num ) {
    volatile uint8_t i = 0;

    i = 0;
    if (!(PIND & (1 << switch_num))) {
        _delay_ms(20);
        i++;
    }
    if ((PIND & (1 << switch_num))) {
        i++;
    }
    if (i == 2) {
        return 1;
    }
    return 0;
}

int main(void) {
    //Voir exercice 1 pour l'explication
    DDRB |= ((1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB4));
    PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB4));

    uint8_t val = 0;

    while (1) {
        if (is_released(PIND2)) { val++; } 
        else if (is_released(PIND4)) { val--; }

        PORTB = (PORTB & ~((1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB4))) |
                ((val & 1 << 0)) |
                ((val & 1 << 1)) |
                ((val & 1 << 2)) |
                ((val & 1 << 3)) << 1;
    }
}