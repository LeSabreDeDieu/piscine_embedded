/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:34:17 by sayfallahga       #+#    #+#             */
/*   Updated: 2025/03/10 14:46:44 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void print_hex(uint8_t value) {
    char hex_str[5];  // Format "0xff\0"
    hex_str[0] = '0';
    hex_str[1] = 'x';
    hex_str[2] = "0123456789abcdef"[value >> 4];  // Partie haute
    hex_str[3] = "0123456789abcdef"[value & 0x0F];  // Partie basse
    hex_str[4] = '\0';  // Fin de chaîne
    uart_printstr(hex_str);
}

char* uint32toa(uint32_t value) {
    static char str[11];  // Maximum length for uint32_t (4294967295) + null terminator
    char *ptr = str + sizeof(str) - 1;
    *ptr = '\0';

    // Convert integer to string
    do {
        *--ptr = (value % 10) + '0';
        value /= 10;
    } while (value);

    return ptr;
}

unsigned int round_ubbr() {
    if (MYUBBR >= 0)
        return (unsigned int)(MYUBBR + 0.5f);
    else
        return (unsigned int)(MYUBBR - 0.5f);
}

uint16_t convert_to_celsius(uint16_t adc_value) {

    // Conversion en tension (V)
    // uint16_t voltage = adc_value * (1.1 / 1024.0); 
    uint16_t voltage = (adc_value - 324) / 1.22;

    // Conversion en température (°C)
    uint16_t temperature = (voltage - 0.5) * 100.0; 

    return temperature;
}