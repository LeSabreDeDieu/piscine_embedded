/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:49:04 by sgabsi            #+#    #+#             */
/*   Updated: 2025/03/04 09:52:56 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    //Voir exercice 1 pour l'explication
    DDRB |= (1 << PB0);
    PORTB &= ~(1 << PB0);
    volatile uint8_t i = 0;

    // Pareil que l'exercice precedent, sauf que cette fois on doit faire en sorte qu'a chaque relachement
    // la LED inverse son etat (d'eteint vers allumer et inversement).
    while (1) {
        i = 0;
        // Les 2 prochains if, permet de tester si le switch a ete presse puis relache.
        // De plus, il permet aussi de regler le probleme de bounce.
        if (!(PIND & (1 << PIND2))) {
            _delay_ms(20);
            i++;
        }
        if ((PIND & (1 << PIND2))) { 
            i++;
        }

        // Si le switch passe dans les 2 etats dans la meme boucle, c'est qu'il vient d'etre appuye puis relache
        // et donc il peut inverse sont etat.
        if (i == 2) {
            PORTB ^= (1 << PB0);
        }
    }
}