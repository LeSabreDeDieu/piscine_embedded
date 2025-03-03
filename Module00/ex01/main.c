/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:49:04 by sgabsi            #+#    #+#             */
/*   Updated: 2025/03/03 16:49:00 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <avr/io.h>

int main(void) {

    // source 1 : https://openclassrooms.com/forum/sujet/ddrx-portx-pinx
    // source 2 : https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf (page 72)
    
    // Le microprocesseur est divise en trois secteur B, C et D
    // chaque secteur est lui meme divise en trois registre DDRX, PORTX et PINX.
    
    // DDRX ou Data Direction Register X permet de choisir entre mode ecriture (1) ou lecture (0) d'un secteur donner (ici B).
    // ici, on selectionne la LED DDB0 (car c'est la premiere en commancant par 0) en mode ecriture.
    DDRB |= (1 << DDB0);
    
    // le PORTX permet de definir l'etat de la sortie (allume, eteint (1 ou 0)) d'un secteur (ici B).
    // ici, on selectionne la LED PB0 (car c'est aussi la premiere en commancant par 0) et on lui dis de s'allumer (1).
    PORTB |= (1 << PB0);
    return 0;
}
