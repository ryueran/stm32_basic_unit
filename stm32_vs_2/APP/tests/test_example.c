#include "stdlib.h"
#include "unity.h"
#include "fff.h"
#include "stm32f0xx_hal_flash.h"
#include "stm32f0xx_hal_flash_ex.h"
#include "flash_sector_f0.h"

DEFINE_FFF_GLOBALS

FAKE_VALUE_FUNC2(HAL_StatusTypeDef, HAL_FLASHEx_Erase, FLASH_EraseInitTypeDef *, uint32_t *);
FAKE_VALUE_FUNC0(HAL_StatusTypeDef, HAL_FLASH_Unlock);
FAKE_VALUE_FUNC0(uint32_t, HAL_FLASH_GetError);
FAKE_VALUE_FUNC0(HAL_StatusTypeDef, HAL_FLASH_Lock);
FAKE_VALUE_FUNC3(HAL_StatusTypeDef, HAL_FLASH_Program, uint32_t, uint32_t, uint64_t);

uint32_t *PAGEError = 0;
static FLASH_EraseInitTypeDef EraseInitStruct;

void setUp(void)
{
  /* This is run before EACH TEST */
  FFF_RESET_HISTORY();

}

void tearDown(void)
{
}

void test_case1(void)
{
    TEST_ASSERT_EQUAL(GetPage(0x08000001), 0);
    TEST_ASSERT_EQUAL(GetPage(0x080003FF), 0);
}

void test_case3(void)
{
    TEST_ASSERT_EQUAL(GetPage(0x08000400), 1);
    TEST_ASSERT_EQUAL(GetPage(0x080007FF), 1);
}

void test_case4(void)
{
    TEST_ASSERT_EQUAL(GetPage(0x08000800), 2);
    TEST_ASSERT_EQUAL(GetPage(0x08000BFF), 2);
}

void test_case2(void)
{
    uint32_t data_write[] = {};
    EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
    EraseInitStruct.PageAddress = 0x08000000;
    EraseInitStruct.NbPages = 1;
    Flash_Write_Data(0x08000000, data_write, 4);
    TEST_ASSERT_EQUAL(HAL_FLASH_Lock_fake.call_count, 1);
    TEST_ASSERT_EQUAL(HAL_FLASH_Unlock_fake.call_count, 1);
    TEST_ASSERT_EQUAL(HAL_FLASHEx_Erase_fake.call_count, 1);
    TEST_ASSERT_EQUAL(HAL_FLASHEx_Erase_fake.arg0_val->TypeErase, FLASH_TYPEERASE_PAGES);
    TEST_ASSERT_EQUAL(HAL_FLASHEx_Erase_fake.arg0_val->PageAddress, 0x08000000);    
    TEST_ASSERT_EQUAL(HAL_FLASHEx_Erase_fake.arg0_val->NbPages, 1);
}

int main(int argc, const char * argv[])
{
    RUN_TEST(test_case1);
    RUN_TEST(test_case2);
    RUN_TEST(test_case3);
    RUN_TEST(test_case4);
    return 1;
}