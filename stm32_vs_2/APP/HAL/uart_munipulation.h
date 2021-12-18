#ifndef UART_MANIPULATION_H_
#define UART_MANIPULATION_H_

#include <unistd.h>
#include <stdint.h>
#include "stm32f0xx_hal_uart.h"
#include "stm32f0xx_hal_dma.h"

UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_usart2_rx;
void UART_Read_Data(uint32_t *buf);
void UART_Init();
void UART_DMA_Init();

#endif