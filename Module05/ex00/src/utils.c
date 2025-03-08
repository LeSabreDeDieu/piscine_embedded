/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayfallahgabsi <sayfallahgabsi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:34:17 by sayfallahga       #+#    #+#             */
/*   Updated: 2025/03/07 15:42:05 by sayfallahga      ###   ########.fr       */
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
    uart_printstr("\n\r");  // Nouvelle ligne
}

unsigned int round_ubbr() {
    if (MYUBBR >= 0)
        return (unsigned int)(MYUBBR + 0.5f);
    else
        return (unsigned int)(MYUBBR - 0.5f);
}
