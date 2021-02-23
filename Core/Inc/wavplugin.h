/*
 * wavplugin.h
 *
 *  Created on: Feb 12, 2021
 *      Author: thomas
 */
#ifndef WAVPLUGIN_H_
#define WAVPLUGIN_H_

#include "main.h"

AUDIO_ErrorTypeDef AUDIO_PLAYER_Init(void);
AUDIO_ErrorTypeDef AUDIO_PLAYER_Start(uint8_t idx);
AUDIO_ErrorTypeDef AUDIO_PLAYER_Process(void);
AUDIO_ErrorTypeDef AUDIO_PLAYER_Stop(void);

#endif
