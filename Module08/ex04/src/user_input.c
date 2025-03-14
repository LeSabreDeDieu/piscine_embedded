/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:48:27 by sgabsi            #+#    #+#             */
/*   Updated: 2025/03/14 17:28:19 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

uint8_t	is_printable_spe( char c ) {
	return ((c >= 32 && c <= 126) || c == 27 || c == '\r' || c == '\b' || c == 127 );
}

void get_input (char *buffer, uint8_t size) {
	int i = 0;
	char c = 0;

	while (1) {
		c = read_char();
		if (is_printable_spe(c) && i <= size - 1) {
			if (c == '\r') {
				uart_println();
				break;
			} 
			else if ((c == '\b' || c == 127)) {
				if (i > 0) {
					uart_printstr("\b \b");
					i--;
				}
				continue;
			}
			else if (c == 27) { break; }
			uart_printchar(c);
			buffer[i++] = c;
		}
	}
	buffer[i] = 0;
}
