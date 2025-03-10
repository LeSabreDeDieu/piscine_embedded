/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:34:17 by sayfallahga       #+#    #+#             */
/*   Updated: 2025/03/10 14:49:59 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char* uint16toa(uint16_t value) {
    static char str[6];  // Maximum length for uint16_t (65535) + null terminator
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
