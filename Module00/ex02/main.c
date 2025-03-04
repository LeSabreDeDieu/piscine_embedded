/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:49:04 by sgabsi            #+#    #+#             */
/*   Updated: 2025/03/04 09:48:09 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <avr/io.h>

int main(void) {
    //Voir exercice 1 pour l'explication
    DDRB |= (1 << PB0);
    PORTB &= ~(1 << PB0);

    while (1) {
        // Le PINX est un registre un peu speciale, il est en READ only.
        // Le PINX nous permet de connaitre l'etat d'un composant.
        // Si le PINX est a 1, le composant est utilise. 0 sinon
        // SAUF pour le switch ou il est inverse a cause (ou grace) aux resistance utilise (voir schemas).
        
        // Ici, on selectionne le switch PIND2, et on regarde son etat.
        // Si le bouton est a 0, on allume la LED
        // Si non, on eteint la LED
        if (!(PIND & (1 << PIND2))) {
            PORTB |= (1 << PB0);
        } else {
            PORTB &= ~(1 << PB0);
        }
    }
}