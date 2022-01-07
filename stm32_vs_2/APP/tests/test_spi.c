#include "stdlib.h"
#include "unity.h"
#include "fff.h"
#include "stm32f0xx_hal_rcc.h"
#include "stm32f0xx_hal_dma.h"
#include "stm32f0xx_hal_spi.h"
#include "spi_manipulation.h"

DEFINE_FFF_GLOBALS

SPI_HandleTypeDef hspi;
FAKE_VALUE_FUNC3(HAL_StatusTypeDef, HAL_SPI_Transmit_IT, SPI_HandleTypeDef *, uint8_t *, uint16_t)
FAKE_VALUE_FUNC3(HAL_StatusTypeDef, HAL_SPI_Receive_IT, SPI_HandleTypeDef *, uint8_t *, uint16_t)
FAKE_VALUE_FUNC1(HAL_StatusTypeDef, HAL_SPI_Init, SPI_HandleTypeDef *)
FAKE_VOID_FUNC(Error_Handler)

void setUp(void)
{
  /* This is run before EACH TEST */
  RESET_FAKE(HAL_SPI_Receive_IT);
  RESET_FAKE(HAL_SPI_Receive_IT);
  RESET_FAKE(HAL_SPI_Init);
  RESET_FAKE(Error_Handler);
  FFF_RESET_HISTORY();
}

void tearDown(void)
{
}

void test_case1(void)
{
    uint8_t write_buf[13] = "Hello \r\n";
    int size_data = sizeof(write_buf)/sizeof(write_buf[0]);
    hspi.Instance = SPI1;
    hspi.Init.Mode = SPI_MODE_SLAVE;
    hspi.Init.Direction = SPI_DIRECTION_2LINES;
    hspi.Init.DataSize = SPI_DATASIZE_8BIT;
    hspi.Init.CLKPolarity = SPI_POLARITY_LOW;
    hspi.Init.CLKPhase = SPI_PHASE_1EDGE;
    hspi.Init.NSS = SPI_NSS_SOFT;
    hspi.Init.FirstBit = SPI_FIRSTBIT_MSB;
    hspi.Init.TIMode = SPI_TIMODE_DISABLE;
    hspi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    hspi.Init.CRCPolynomial = 10;
    SPI_Transfer_Data(&hspi, write_buf, size_data);
    TEST_ASSERT_EQUAL(HAL_SPI_Transmit_IT_fake.call_count, 1);
    TEST_ASSERT_EQUAL(HAL_SPI_Transmit_IT_fake.arg0_val->Instance, SPI1);
    TEST_ASSERT_EQUAL(HAL_SPI_Transmit_IT_fake.arg0_val->Init.Mode, SPI_MODE_SLAVE);    
    TEST_ASSERT_EQUAL(HAL_SPI_Transmit_IT_fake.arg0_val->Init.Direction, SPI_DIRECTION_2LINES);
    TEST_ASSERT_EQUAL(HAL_SPI_Transmit_IT_fake.arg0_val->Init.DataSize, SPI_DATASIZE_8BIT);
    TEST_ASSERT_EQUAL(HAL_SPI_Transmit_IT_fake.arg0_val->Init.CLKPolarity, SPI_POLARITY_LOW);
    TEST_ASSERT_EQUAL(HAL_SPI_Transmit_IT_fake.arg0_val->Init.CLKPhase, SPI_PHASE_1EDGE);
    TEST_ASSERT_EQUAL(HAL_SPI_Transmit_IT_fake.arg0_val->Init.NSS, SPI_NSS_SOFT);
    TEST_ASSERT_EQUAL(HAL_SPI_Transmit_IT_fake.arg0_val->Init.FirstBit, SPI_FIRSTBIT_MSB);
    TEST_ASSERT_EQUAL(HAL_SPI_Transmit_IT_fake.arg0_val->Init.TIMode, SPI_TIMODE_DISABLE);
    TEST_ASSERT_EQUAL(HAL_SPI_Transmit_IT_fake.arg0_val->Init.CRCCalculation, SPI_CRCCALCULATION_DISABLE);
    TEST_ASSERT_EQUAL(HAL_SPI_Transmit_IT_fake.arg0_val->Init.CRCPolynomial, 10);
    TEST_ASSERT_EQUAL(HAL_SPI_Transmit_IT_fake.arg1_val, write_buf);
    TEST_ASSERT_EQUAL(HAL_SPI_Transmit_IT_fake.arg2_val, size_data);
}

void test_case2(void)
{
    uint8_t read_buf[13] = {};
    int size_data = sizeof(read_buf)/sizeof(read_buf[0]);
    hspi.Instance = SPI1;
    hspi.Init.Mode = SPI_MODE_SLAVE;
    hspi.Init.Direction = SPI_DIRECTION_2LINES;
    hspi.Init.DataSize = SPI_DATASIZE_8BIT;
    hspi.Init.CLKPolarity = SPI_POLARITY_LOW;
    hspi.Init.CLKPhase = SPI_PHASE_1EDGE;
    hspi.Init.NSS = SPI_NSS_SOFT;
    hspi.Init.FirstBit = SPI_FIRSTBIT_MSB;
    hspi.Init.TIMode = SPI_TIMODE_DISABLE;
    hspi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    hspi.Init.CRCPolynomial = 10;
    SPI_Receive_Data(&hspi, read_buf, size_data);
    TEST_ASSERT_EQUAL(HAL_SPI_Receive_IT_fake.call_count, 1);
    TEST_ASSERT_EQUAL(HAL_SPI_Receive_IT_fake.arg0_val->Instance, SPI1);
    TEST_ASSERT_EQUAL(HAL_SPI_Receive_IT_fake.arg0_val->Init.Mode, SPI_MODE_SLAVE);    
    TEST_ASSERT_EQUAL(HAL_SPI_Receive_IT_fake.arg0_val->Init.Direction, SPI_DIRECTION_2LINES);
    TEST_ASSERT_EQUAL(HAL_SPI_Receive_IT_fake.arg0_val->Init.DataSize, SPI_DATASIZE_8BIT);
    TEST_ASSERT_EQUAL(HAL_SPI_Receive_IT_fake.arg0_val->Init.CLKPolarity, SPI_POLARITY_LOW);
    TEST_ASSERT_EQUAL(HAL_SPI_Receive_IT_fake.arg0_val->Init.CLKPhase, SPI_PHASE_1EDGE);
    TEST_ASSERT_EQUAL(HAL_SPI_Receive_IT_fake.arg0_val->Init.NSS, SPI_NSS_SOFT);
    TEST_ASSERT_EQUAL(HAL_SPI_Receive_IT_fake.arg0_val->Init.FirstBit, SPI_FIRSTBIT_MSB);
    TEST_ASSERT_EQUAL(HAL_SPI_Receive_IT_fake.arg0_val->Init.TIMode, SPI_TIMODE_DISABLE);
    TEST_ASSERT_EQUAL(HAL_SPI_Receive_IT_fake.arg0_val->Init.CRCCalculation, SPI_CRCCALCULATION_DISABLE);
    TEST_ASSERT_EQUAL(HAL_SPI_Receive_IT_fake.arg0_val->Init.CRCPolynomial, 10);
    TEST_ASSERT_EQUAL(HAL_SPI_Receive_IT_fake.arg1_val, read_buf);
    TEST_ASSERT_EQUAL(HAL_SPI_Receive_IT_fake.arg2_val, size_data);
}

void test_case3(void)
{
    SPI_Init(&hspi);
    TEST_ASSERT_EQUAL(HAL_SPI_Init_fake.call_count, 1);
    TEST_ASSERT_EQUAL(HAL_SPI_Init_fake.arg0_val, &hspi);
}

int main(int argc, const char * argv[])
{
    RUN_TEST(test_case1);
    RUN_TEST(test_case2);
    RUN_TEST(test_case3);
    return 1;
}