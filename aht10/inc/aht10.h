/**
 *******************************************************************************
 * @file      : aht10.h
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __aht10_H_
#define __aht10_H_
#ifndef _AHT10_H_
#define _AHT10_H_

#include "i2c.h"
#include "cmsis_os.h"
// 定义AHT10地址
#define AHT10_ADDRESS 0x70
#define AHT10_Write_ADDRESS 0x70
#define AHT10_Read_ADDRESS 0x71

// 定义AHT10命令
#define AHT10_Init_com 0xE1      // 1110 0001
#define AHT10_SoftReset_com 0xBA // 1011 1010
#define AHT10_TrigeMea_com 0xAC  // 1010 1100

#endif

#ifdef __cplusplus

/* Includes ------------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
class AHT10{
 public:
  float humidity,temperature;
  void Init(I2C_HandleTypeDef *_i2c);
  uint8_t ReadData();
 private:
  I2C_HandleTypeDef *i2c_;
  void SoftReset(void);
  void TrigeMea(void);
};
/* Exported variables --------------------------------------------------------*/
/* Exported function prototypes ----------------------------------------------*/

#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported function prototypes ----------------------------------------------*/

#ifdef  __cplusplus
}
#endif

#endif /* __aht10_H_ */