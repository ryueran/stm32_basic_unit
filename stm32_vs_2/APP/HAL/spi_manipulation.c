#include "spi_manipulation.h"

void SPI_Transfer_Data(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size)
{
    HAL_SPI_Transmit_IT(hspi, pData, Size);
}

void SPI_Receive_Data(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size)
{
    HAL_SPI_Receive_IT(hspi, pData, Size);
}

void SPI_Init(SPI_HandleTypeDef *hspi)
{
    /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi->Instance = SPI1;
  hspi->Init.Mode = SPI_MODE_SLAVE;
  hspi->Init.Direction = SPI_DIRECTION_2LINES;
  hspi->Init.DataSize = SPI_DATASIZE_8BIT;
  hspi->Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi->Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi->Init.NSS = SPI_NSS_SOFT;
  hspi->Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi->Init.TIMode = SPI_TIMODE_DISABLE;
  hspi->Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi->Init.CRCPolynomial = 10;
  // hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  // hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(hspi) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */
}
