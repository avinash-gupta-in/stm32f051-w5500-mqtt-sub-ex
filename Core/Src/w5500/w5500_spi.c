#include "stm32f0xx_hal.h"
#include "wizchip_conf.h"
#include "stdio.h"

extern SPI_HandleTypeDef hspi1;

uint8_t SPIReadWrite(uint8_t data)
{
	//wait till FIFO has a free slot
	while((hspi1.Instance->SR & SPI_FLAG_TXE) != SPI_FLAG_TXE);

	*(__IO uint8_t*)&hspi1.Instance->DR=data;

	//Now wait till data arrives
	while((hspi1.Instance->SR & SPI_FLAG_RXNE)!=SPI_FLAG_RXNE);

	return (*(__IO uint8_t*)&hspi1.Instance->DR);
}

void  wizchip_select(void)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
}

void  wizchip_deselect(void)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
}

uint8_t wizchip_read()
{
	uint8_t rb;
	rb=SPIReadWrite(0x00);
	return rb;
}

void  wizchip_write(uint8_t wb)
{
	SPIReadWrite(wb);
}

void wizchip_readburst(uint8_t* pBuf, uint16_t len)
{
	for(uint16_t i=0;i<len;i++)
	{
		*pBuf=SPIReadWrite(0x00);
		pBuf++;
	}
}

void  wizchip_writeburst(uint8_t* pBuf, uint16_t len)
{
	for(uint16_t i=0;i<len;i++)
	{
		SPIReadWrite(*pBuf);
		pBuf++;
	}
}

void W5500IOInit()
{
	/*
	 * Initialize the two GPIO pins
	 * RESET->PA10
	 * and
	 * CS->PA11
	 */
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	__HAL_RCC_GPIOA_CLK_ENABLE();

	GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void w5500_enter_critical(void)
{
	__disable_irq();
}

void w5500_exit_critical(void)
{
	__enable_irq();
}

void W5500Init()
{
	uint8_t tmp;
	uint8_t memsize[2][8] = { { 2, 2, 2, 2, 2, 2, 2, 2 }, { 2, 2, 2, 2, 2, 2, 2, 2 } };

	W5500IOInit();

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);//CS high by default

	//Send a pulse on reset pin
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
	tmp = 0xFF;
	while(tmp--);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);

	reg_wizchip_cs_cbfunc(wizchip_select, wizchip_deselect);
	reg_wizchip_spi_cbfunc(wizchip_read, wizchip_write);
	reg_wizchip_spiburst_cbfunc(wizchip_readburst, wizchip_writeburst);
	reg_wizchip_cris_cbfunc(w5500_enter_critical, w5500_exit_critical);

	/* WIZChip Initialize*/
	if (ctlwizchip(CW_INIT_WIZCHIP, (void*) memsize) == -1) {
		printf("WIZCHIP Initialized Failed.\r\n");
		while (1);
	}
	printf("WIZCHIP Initialization Success.\r\n");

	//Check if SPI is working
	printf("Auto-detecting Ethernet Chip on SPI Port...");
	if(WIZCHIP_READ(VERSIONR)==0x04)
	{
		printf("W5500 Found on SPI\r\n");
	}
	else
	{
		printf("W5500 NOT Found on SPI\r\n");
		printf("Double Check SPI Cables\r\n");
		while(1);
	}
}

