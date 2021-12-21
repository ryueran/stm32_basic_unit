#ifndef UART_MANIPULATION_H_
#define UART_MANIPULATION_H_

#include <unistd.h>
#include <stdint.h>
#include "stm32f0xx_hal_rcc.h"
#include "stm32f0xx_hal_dma.h"
#include "stm32f0xx_hal_uart.h"

//extern UART_HandleTypeDef huart2;
//extern DMA_HandleTypeDef hdma_usart2_rx;
void UART_Write_Data(uint8_t *buf, int size);
void UART_Init();
void UART_DMA_Init();

#endif