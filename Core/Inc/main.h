/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "stm32f769i_discovery_audio.h"
#include "stm32f769i_discovery.h"
#include "fatfs.h"
#include "usbh_core.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
/* Audio Demo State Structure */
#define BUFF_SIZE 8192
#define AUDIO_OUT_BUFFER_SIZE                      8192

#define FILEMGR_LIST_DEPDTH                        24
#define FILEMGR_FILE_NAME_SIZE                     40
#define FILEMGR_FULL_PATH_SIZE                     256
#define FILEMGR_MAX_LEVEL                          4
#define FILETYPE_DIR                               0
#define FILETYPE_FILE                              1

typedef enum {
  AUDIO_DEMO_IDLE = 0,
  AUDIO_DEMO_WAIT,
  AUDIO_DEMO_EXPLORE,
  AUDIO_DEMO_PLAYBACK,
  AUDIO_DEMO_IN,
}AUDIO_Demo_State;

/* Audio Demo State Machine Structure */
typedef struct _DemoStateMachine {
  __IO AUDIO_Demo_State state;
  __IO uint8_t select;
}AUDIO_DEMO_StateMachine;

typedef enum {
  AUDIO_STATE_IDLE = 0,
  AUDIO_STATE_WAIT,
  AUDIO_STATE_INIT,
  AUDIO_STATE_PLAY,
  AUDIO_STATE_PRERECORD,
  AUDIO_STATE_RECORD,
  AUDIO_STATE_NEXT,
  AUDIO_STATE_PREVIOUS,
  AUDIO_STATE_FORWARD,
  AUDIO_STATE_BACKWARD,
  AUDIO_STATE_STOP,
  AUDIO_STATE_PAUSE,
  AUDIO_STATE_RESUME,
  AUDIO_STATE_VOLUME_UP,
  AUDIO_STATE_VOLUME_DOWN,
  AUDIO_STATE_ERROR,
}AUDIO_PLAYBACK_StateTypeDef;

typedef enum {
  AUDIO_SELECT_MENU = 0,
  AUDIO_PLAYBACK_CONTROL,
}AUDIO_DEMO_SelectMode;

typedef enum {
  BUFFER_OFFSET_NONE = 0,
  BUFFER_OFFSET_HALF,
  BUFFER_OFFSET_FULL,
}BUFFER_StateTypeDef;

/* Audio buffer control struct */
typedef struct {
  uint8_t buff[AUDIO_OUT_BUFFER_SIZE];
  BUFFER_StateTypeDef state;
  uint32_t fptr;
}AUDIO_OUT_BufferTypeDef;

typedef enum {
  BUFFER_EMPTY = 0,
  BUFFER_FULL,
}WR_BUFFER_StateTypeDef;

typedef struct {
  uint32_t ChunkID;       /* 0 */
  uint32_t FileSize;      /* 4 */
  uint32_t FileFormat;    /* 8 */
  uint32_t SubChunk1ID;   /* 12 */
  uint32_t SubChunk1Size; /* 16*/
  uint16_t AudioFormat;   /* 20 */
  uint16_t NbrChannels;   /* 22 */
  uint32_t SampleRate;    /* 24 */

  uint32_t ByteRate;      /* 28 */
  uint16_t BlockAlign;    /* 32 */
  uint16_t BitPerSample;  /* 34 */
  uint32_t SubChunk2ID;   /* 36 */
  uint32_t SubChunk2Size; /* 40 */
}WAVE_FormatTypeDef;

typedef struct _FILELIST_LineTypeDef {
  uint8_t type;
  uint8_t name[FILEMGR_FILE_NAME_SIZE];
}FILELIST_LineTypeDef;

typedef struct _FILELIST_FileTypeDef {
  FILELIST_LineTypeDef  file[FILEMGR_LIST_DEPDTH] ;
  uint16_t              ptr;
}FILELIST_FileTypeDef;

typedef enum {
  AUDIO_ERROR_NONE = 0,
  AUDIO_ERROR_IO,
  AUDIO_ERROR_EOF,
  AUDIO_ERROR_INVALID_VALUE,
}AUDIO_ErrorTypeDef;

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
extern AUDIO_PLAYBACK_StateTypeDef AudioState;

extern uint8_t uartMsgData;
extern char signal_text[20];

extern bool button_clicked;
//extern uint32_t step=1;
extern double time_expected;
extern uint8_t grana;
extern bool play_flag;

extern bool zagrana;
extern bool note_stop;
extern bool initialized;
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
/* menu API */
void AUDIO_MenuProcess(void);
/* wavplugin API */
AUDIO_ErrorTypeDef AUDIO_PLAYER_Init(void);
/* Disk Explorer API */
uint8_t Explorer_Process(void);
uint8_t Explorer_StorageInit(void);
//FRESULT Explorer_StorageParse(void);
uint16_t Explorer_GetWavObjectNumber(void);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
//void   MX_I2C4_Init(void);
/* USER CODE BEGIN Private defines */



//#define BUFF_SIZE 8
//extern uint16_t buff_out[BUFF_SIZE];
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
