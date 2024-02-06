/**
 *******************************************************************************
 * @file      : aht10.cpp
 * @brief     :
 * @history   :
 *  Version     Date               Author             Note
 *  V0.9.0      2024/2/6         Huang Huichuan     1. <note>
 *******************************************************************************
 * @attention :
 *******************************************************************************
 *  Copyright (c) 2024 Reborn Team, University of Science and Technology Beijing.
 *  All Rights Reserved.
 *******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "aht10.h"
/* Private macro -------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void AHT10::Init(I2C_HandleTypeDef *_i2c)
{
  i2c_ = _i2c;

  uint8_t data;
  data = AHT10_Init_com;
  HAL_I2C_Master_Transmit(i2c_,AHT10_ADDRESS,&data,1,10);
}

void AHT10::SoftReset(void)
{
  uint8_t data;
  data = AHT10_SoftReset_com;
  HAL_I2C_Master_Transmit(i2c_, AHT10_Write_ADDRESS, &data, 1, 10);
  osDelay(20);
}

void AHT10::TrigeMea(void)
{
  uint8_t senddata[3];
  senddata[0] = AHT10_TrigeMea_com;
  senddata[1] = 0x33; // DATA0
  senddata[2] = 0x00; // DATA1
  HAL_I2C_Master_Transmit(i2c_, AHT10_Write_ADDRESS, senddata, 3, 10);
  osDelay(80);
}
uint8_t AHT10::ReadData()
{
  TrigeMea();
  osDelay(75);
  static uint32_t humi, temp;
  uint8_t readdata[6];
  uint8_t BusyIndication, CalEnable;
  HAL_I2C_Master_Receive(i2c_, AHT10_Read_ADDRESS, readdata, 6, 10);
  BusyIndication = (readdata[0] >> 7) & 0x01; // 状态标志位
  CalEnable = (readdata[0] >> 3) & 0x01;      // 校准标志位
  if (CalEnable == 0)
  {
    SoftReset();
  }
  if (BusyIndication == 0)
  {
    humi = (readdata[1] << 12) | (readdata[2] << 4) | (readdata[3] >> 4);
    temp = ((readdata[3] & 0x0F) << 16) | (readdata[4] << 8) | (readdata[5]);
    humidity = (((float)humi * 100.0f) / 1048576);
    temperature = ((float)temp / 1048576) * 200 - 50;
    return 0;
  }
  return 1;
}
