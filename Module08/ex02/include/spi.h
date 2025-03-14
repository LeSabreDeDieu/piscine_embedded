/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spi.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:19:51 by sgabsi            #+#    #+#             */
/*   Updated: 2025/03/14 15:40:19 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPI_H
#define SPI_H

#include <avr/io.h>

void SPI_MasterInit(void);
void SPI_MasterTransmit(char cData);

#endif // !SPI_H
