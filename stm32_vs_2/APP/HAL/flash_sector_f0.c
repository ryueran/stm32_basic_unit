#include "stdio.h"
#include "string.h"
#include "unistd.h"
#include "stm32f0xx_hal.h"
#include "flash_sector_f0.h"
#include "stm32f0xx_hal_flash.h"
#include "stm32f0xx_hal_flash_ex.h"

uint32_t GetPage(uint32_t Address)
{
    uint32_t base_address = 0x08000000;
    uint32_t page_size = 1024;
    uint32_t num_of_page = 0;
    uint32_t nth_page = 0;
    if((Address - base_address)%page_size)
    {
        nth_page = ((Address - base_address) / page_size) + 1;
    } else {
        nth_page = ((Address - base_address) / page_size);
    }

    return num_of_page + nth_page;
}

uint32_t Flash_Write_Data(uint32_t StartPageAddress, uint32_t *data, uint16_t size_of_data)
{
    static FLASH_EraseInitTypeDef EraseInitStruct;
    uint32_t PAGEError = 0;
    int sofar = 0;
    uint32_t EndAddress = StartPageAddress + size_of_data;
    int page_start = GetPage(StartPageAddress);
    int page_end = GetPage(EndAddress);

    /* Unlock the Flash to enable the flash control register access *************/
    HAL_FLASH_Unlock();

    /* Fill EraseInit structure*/
    EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
    EraseInitStruct.PageAddress = StartPageAddress;
    EraseInitStruct.NbPages = page_end - page_start + 1;

    if (HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError) != HAL_OK)
    {
        return HAL_FLASH_GetError();
    }

    /* Program the user Flash area 8 WORDS at a time
	   * (area defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR) ***********/
    uint32_t Address = StartPageAddress;
    while (Address < EndAddress)
    {

        if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address, data[sofar]) == HAL_OK)
        {
            Address = Address + 4;
            sofar++;
        }   else    {
            return HAL_FLASH_GetError();
        }
    }

  /* Lock the Flash to disable the flash control register access (recommended
     to protect the FLASH memory against possible unwanted operation) *********/
    HAL_FLASH_Lock();
    return 0;
}

void Flash_Read_Data(uint32_t StartPageAddress, uint32_t *data, uint16_t numberofwords)
{
    while(1)
    {
        *data = *(__IO uint16_t*)StartPageAddress;
        StartPageAddress += 4;
        data++;
        if(!(numberofwords--))
            break;
    }
}

uint32_t Flash_init(uint32_t StartPageAddress, uint32_t numberofpages)
{
    static FLASH_EraseInitTypeDef EraseInitStruct;
    uint32_t PAGEError = 0;
    /* Unlock the Flash to enable the flash control register access *************/
    HAL_FLASH_Unlock();

    /* Fill EraseInit structure*/
    EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
    EraseInitStruct.PageAddress = StartPageAddress;
    EraseInitStruct.NbPages = numberofpages;

    if (HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError) != HAL_OK)
    {
        return HAL_FLASH_GetError();
    }

    HAL_FLASH_Lock();
    return 0;
}
