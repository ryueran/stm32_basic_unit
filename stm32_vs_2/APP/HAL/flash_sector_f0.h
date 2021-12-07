#ifndef FLASH_SECTOR_F0_H_
#define FLASH_SECTOR_F0_H_

#include <unistd.h>
#include <stdint.h>
#include "stm32f0xx_hal_flash.h"

static uint32_t GetPage(uint32_t Address);

uint32_t Flash_Write_Data(uint32_t StartPageAddress, uint32_t *data, uint16_t numberofwords);

void Flash_Read_Data(uint32_t StartPageAddress, uint32_t *data, uint16_t numberofwords);

uint32_t Flash_init();

#endif