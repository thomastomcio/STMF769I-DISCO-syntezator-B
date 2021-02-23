/*
 * Polling_routines.cpp
 *
 *  Created on: Jan 10, 2021
 *      Author: thomas
 */

#include "Polling_routines.hpp"
#include "main.h"
#include <vector>
#include "MIDI.h"
//#include "stm32f769i_discovery.h"

extern UART_HandleTypeDef huart6 ;
extern UART_HandleTypeDef huart1;

//extern osSemaphoreId_t binarySemUartMsgHandle;
//uint8_t uartMsgData[256];
uint8_t uartMsgData;
uint8_t prev_uartMsgData;
uint8_t note_number_byte = 0;
//std::vector<uint8_t> data_array;
//uint8_t data_counter = 0;

bool msgRdyFlag = 0;
bool new_note_number_byte=false;
bool note_stop=0;

void PollingInit()
{
	//BSP_LED_Init(LED2);
	//enable interrupt
//	HAL_UART_Transmit(&huart1, &uartMsgData, 1, 0);
	HAL_UART_Receive_IT(&huart1, &uartMsgData, 1);
	HAL_UART_Receive_IT(&huart6, &uartMsgData, 1);
}

void PollingRoutine()
{
//	if(msgRdyFlag)
//	{
		//msgRdyFlag = 0;
		//osSemaphoreRelease(binarySemUartMsgHandle);
//	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	// claim that data is ready to read
	if((prev_uartMsgData & 0xF0) == 0x90 && (uartMsgData & 0xF0) != 0x80)
	{
		note_number_byte = uartMsgData;
		new_note_number_byte = true;
	}
	else if((uartMsgData & 0xF0) == 0x80)
	{
		note_stop=1;
	}

	//else new_note_number_byte = false;

	msgRdyFlag = 1;
//	data_array.push_back(uartMsgData);
	prev_uartMsgData = uartMsgData;

	HAL_UART_Transmit(&huart1, &uartMsgData, 1, 0);
	HAL_UART_Transmit(&huart6, &uartMsgData, 1, 0);
//	if (data_counter < 255)
//		{
//			data_counter++;
//		}else data_counter=0;
	BSP_LED_Toggle(LED2);


	// enable interrupt again
	HAL_UART_Receive_IT(&huart1, &uartMsgData, 1);
	HAL_UART_Receive_IT(&huart6, &uartMsgData, 1);


}

