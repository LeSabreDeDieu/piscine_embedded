/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:37:16 by sgabsi            #+#    #+#             */
/*   Updated: 2025/03/14 15:56:07 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spi.h"

void SPI_MasterInit ( void ) {
	/* Set MOSI and SCK output, all others input */
	DDRB = (1 << DD3) | (1 << DD5) | (1 << PB2);
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
}
void SPI_MasterTransmit ( char cData ) {
	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)));
}