/*
 * w5500_spi.h
 *
 *  Created on: Sep 29, 2021
 *      Author: Avinash
 */

#ifndef SRC_W5500_W5500_SPI_H_
#define SRC_W5500_W5500_SPI_H_

#include "stm32f0xx_hal.h"

void W5500Init();

void  wizchip_select(void);
void  wizchip_deselect(void);

uint8_t wizchip_read();
void  wizchip_write(uint8_t wb);

void wizchip_readburst(uint8_t* pBuf, uint16_t len);
void  wizchip_writeburst(uint8_t* pBuf, uint16_t len);

#endif /* SRC_W5500_W5500_SPI_H_ */
