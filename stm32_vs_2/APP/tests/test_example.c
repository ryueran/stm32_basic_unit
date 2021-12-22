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

void setUp(void)
{
  /* This is run before EACH TEST */
  RESET_FAKE(HAL_FLASHEx_Erase);
  RESET_FAKE(HAL_FLASH_Unlock);
  RESET_FAKE(HAL_FLASH_GetError);
  RESET_FAKE(HAL_FLASH_Lock);
  RESET_FAKE(HAL_FLASH_Program);
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
    uint32_t data_write[4] = {0, 1, 2, 3};
    uint32_t StartPageAddress = 0x08000000;
    Flash_Write_Data(StartPageAddress, data_write, sizeof(data_write));
    int round = 4;
    int word = 4;
    TEST_ASSERT_EQUAL(HAL_FLASH_Lock_fake.call_count, 1);
    TEST_ASSERT_EQUAL(HAL_FLASH_Unlock_fake.call_count, 1);
    TEST_ASSERT_EQUAL(HAL_FLASHEx_Erase_fake.call_count, 1);
    TEST_ASSERT_EQUAL(HAL_FLASHEx_Erase_fake.arg0_val->TypeErase, FLASH_TYPEERASE_PAGES);
    TEST_ASSERT_EQUAL(HAL_FLASHEx_Erase_fake.arg0_val->PageAddress, StartPageAddress);    
    TEST_ASSERT_EQUAL(HAL_FLASHEx_Erase_fake.arg0_val->NbPages, 1);
    TEST_ASSERT_EQUAL(HAL_FLASH_Program_fake.call_count, round);
    for (int i = 0; i < round; i++)
    {
        TEST_ASSERT_EQUAL(HAL_FLASH_Program_fake.arg0_history[i], 0x02U);
        TEST_ASSERT_EQUAL(HAL_FLASH_Program_fake.arg1_history[i], StartPageAddress + word*i);
        TEST_ASSERT_EQUAL(HAL_FLASH_Program_fake.arg2_history[i], data_write[i]);
    }
}

void test_case5(void)
{
    uint32_t StartPageAddress = 0x08000000;
    uint32_t numberofpages = 3;
    Flash_init(StartPageAddress, numberofpages);
    TEST_ASSERT_EQUAL(HAL_FLASH_Lock_fake.call_count, 1);
    TEST_ASSERT_EQUAL(HAL_FLASH_Unlock_fake.call_count, 1);
    TEST_ASSERT_EQUAL(HAL_FLASHEx_Erase_fake.call_count, 1);
    TEST_ASSERT_EQUAL(HAL_FLASHEx_Erase_fake.arg0_val->TypeErase, FLASH_TYPEERASE_PAGES);
    TEST_ASSERT_EQUAL(HAL_FLASHEx_Erase_fake.arg0_val->PageAddress, StartPageAddress);    
    TEST_ASSERT_EQUAL(HAL_FLASHEx_Erase_fake.arg0_val->NbPages, numberofpages);
}

int main(int argc, const char * argv[])
{
    RUN_TEST(test_case1);
    RUN_TEST(test_case2);
    RUN_TEST(test_case3);
    RUN_TEST(test_case4);
    RUN_TEST(test_case5);
    return 1;
}