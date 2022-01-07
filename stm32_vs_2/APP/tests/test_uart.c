#include "stdlib.h"
#include "unity.h"
#include "fff.h"
#include "stm32f0xx_hal_rcc.h"
#include "stm32f0xx_hal_dma.h"
#include "stm32f0xx_hal_uart.h"
#include "uart_munipulation.h"

DEFINE_FFF_GLOBALS

UART_HandleTypeDef huart;
FAKE_VALUE_FUNC4(HAL_StatusTypeDef, HAL_UART_Transmit, UART_HandleTypeDef *, uint8_t *, uint16_t, uint32_t)
FAKE_VALUE_FUNC1(HAL_StatusTypeDef, HAL_UART_Init, UART_HandleTypeDef *)
FAKE_VOID_FUNC(HAL_NVIC_SetPriority, IRQn_Type, uint32_t, uint32_t)
FAKE_VOID_FUNC(HAL_NVIC_EnableIRQ, IRQn_Type)
FAKE_VOID_FUNC(Error_Handler)

void setUp(void)
{
  /* This is run before EACH TEST */
  RESET_FAKE(HAL_UART_Transmit);
  RESET_FAKE(HAL_UART_Init);
  RESET_FAKE(HAL_NVIC_SetPriority);
  RESET_FAKE(HAL_NVIC_EnableIRQ);
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
    huart.Instance = USART2;
    huart.Init.BaudRate = 9600;
    huart.Init.WordLength = UART_WORDLENGTH_9B;
    huart.Init.StopBits = UART_STOPBITS_1;
    huart.Init.Parity = UART_PARITY_EVEN;
    huart.Init.Mode = UART_MODE_TX_RX;
    huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart.Init.OverSampling = UART_OVERSAMPLING_16;
    huart.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    huart.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
    UART_Write_Data(&huart, write_buf, size_data);
    TEST_ASSERT_EQUAL(HAL_UART_Transmit_fake.call_count, 1);
    TEST_ASSERT_EQUAL(HAL_UART_Transmit_fake.arg0_val->Instance, USART2);
    TEST_ASSERT_EQUAL(HAL_UART_Transmit_fake.arg0_val->Init.BaudRate, 9600);    
    TEST_ASSERT_EQUAL(HAL_UART_Transmit_fake.arg0_val->Init.WordLength, UART_WORDLENGTH_9B);
    TEST_ASSERT_EQUAL(HAL_UART_Transmit_fake.arg0_val->Init.StopBits, UART_STOPBITS_1);
    TEST_ASSERT_EQUAL(HAL_UART_Transmit_fake.arg0_val->Init.Parity, UART_PARITY_EVEN);
    TEST_ASSERT_EQUAL(HAL_UART_Transmit_fake.arg0_val->Init.Mode, UART_MODE_TX_RX);
    TEST_ASSERT_EQUAL(HAL_UART_Transmit_fake.arg0_val->Init.HwFlowCtl, UART_HWCONTROL_NONE);
    TEST_ASSERT_EQUAL(HAL_UART_Transmit_fake.arg0_val->Init.OverSampling, UART_OVERSAMPLING_16);
    TEST_ASSERT_EQUAL(HAL_UART_Transmit_fake.arg0_val->Init.OneBitSampling, UART_ONE_BIT_SAMPLE_DISABLE);
    TEST_ASSERT_EQUAL(HAL_UART_Transmit_fake.arg0_val->AdvancedInit.AdvFeatureInit, UART_ADVFEATURE_NO_INIT);
}

void test_case2(void)
{
    UART_Init(&huart);
    TEST_ASSERT_EQUAL(HAL_UART_Init_fake.call_count, 1);
    TEST_ASSERT_EQUAL(HAL_UART_Init_fake.arg0_val->Instance, USART2);
    TEST_ASSERT_EQUAL(HAL_UART_Init_fake.arg0_val->Init.BaudRate, 9600);    
    TEST_ASSERT_EQUAL(HAL_UART_Init_fake.arg0_val->Init.WordLength, UART_WORDLENGTH_9B);
    TEST_ASSERT_EQUAL(HAL_UART_Init_fake.arg0_val->Init.StopBits, UART_STOPBITS_1);
    TEST_ASSERT_EQUAL(HAL_UART_Init_fake.arg0_val->Init.Parity, UART_PARITY_EVEN);
    TEST_ASSERT_EQUAL(HAL_UART_Init_fake.arg0_val->Init.Mode, UART_MODE_TX_RX);
    TEST_ASSERT_EQUAL(HAL_UART_Init_fake.arg0_val->Init.HwFlowCtl, UART_HWCONTROL_NONE);
    TEST_ASSERT_EQUAL(HAL_UART_Init_fake.arg0_val->Init.OverSampling, UART_OVERSAMPLING_16);
    TEST_ASSERT_EQUAL(HAL_UART_Init_fake.arg0_val->Init.OneBitSampling, UART_ONE_BIT_SAMPLE_DISABLE);
    TEST_ASSERT_EQUAL(HAL_UART_Init_fake.arg0_val->AdvancedInit.AdvFeatureInit, UART_ADVFEATURE_NO_INIT);
}

void test_case3(void)
{
    UART_DMA_Init(); // not testable
    TEST_ASSERT_EQUAL(HAL_NVIC_SetPriority_fake.call_count, 1);
    TEST_ASSERT_EQUAL(HAL_NVIC_EnableIRQ_fake.call_count, 1);
    TEST_ASSERT_EQUAL(HAL_NVIC_SetPriority_fake.arg0_val, DMA1_Channel4_5_IRQn);
    TEST_ASSERT_EQUAL(HAL_NVIC_SetPriority_fake.arg1_val, 0);
    TEST_ASSERT_EQUAL(HAL_NVIC_SetPriority_fake.arg2_val, 0);
    TEST_ASSERT_EQUAL(HAL_NVIC_EnableIRQ_fake.arg0_val, DMA1_Channel4_5_IRQn);
}

int main(int argc, const char * argv[])
{
    RUN_TEST(test_case1);
    RUN_TEST(test_case2);
    //RUN_TEST(test_case3);
    return 1;
}

