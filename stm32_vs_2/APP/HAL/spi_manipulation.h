#ifndef SPI_MANIPULATION_H_
#define SPI_MANIPULATION_H_

#include <stdint.h>
#include "stm32f0xx_hal_dma.h"
#include "stm32f0xx_hal_rcc.h"
#include "stm32f0xx_hal_spi.h"
#include "stm32f0xx_hal_spi_ex.h"

void SPI_Transfer_Data(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size);
void SPI_Receive_Data(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size);
void SPI_Init(SPI_HandleTypeDef *hspi1);

#endif