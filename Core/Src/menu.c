/*
 * menu.c
 *
 *  Created on: Feb 13, 2021
 *      Author: thomas
 */

#include "wavplugin.h"
#include "usb_host.h"


extern ApplicationTypeDef Appli_state;
char signal_text[20];


AUDIO_DEMO_StateMachine AudioDemo;
AUDIO_PLAYBACK_StateTypeDef AudioState;


//static void AUDIO_ChangeSelectMode(AUDIO_DEMO_SelectMode select_mode);

/**
  * @brief  Manages AUDIO Menu Process.
  * @param  None
  * @retval None
  */
void AUDIO_MenuProcess(void)
{
//  AUDIO_ErrorTypeDef  status;
//  TS_StateTypeDef  TS_State;
//  Point PlaybackLogoPoints[] = {{TOUCH_PLAYBACK_XMIN, TOUCH_PLAYBACK_YMIN},
//                                {TOUCH_PLAYBACK_XMAX, (TOUCH_PLAYBACK_YMIN+TOUCH_PLAYBACK_YMAX)/2},
//                                {TOUCH_PLAYBACK_XMIN, TOUCH_PLAYBACK_YMAX}};
	//sprintf(signal_text, "menu_process_entry");

  if(Appli_state == APPLICATION_READY)
  {
	  sprintf(signal_text, "USB_app_ready");
    switch(AudioDemo.state)
    {
    case AUDIO_DEMO_IDLE:

      AudioDemo.state = AUDIO_DEMO_WAIT;
      sprintf(signal_text, "idle");

      break;


    case AUDIO_DEMO_WAIT:

//      BSP_TS_GetState(&TS_State);
//      if(TS_State.touchDetected == 1)
//      {
//        if ((TS_State.touchX[0] > TOUCH_RECORD_XMIN) && (TS_State.touchX[0] < TOUCH_RECORD_XMAX) &&
//            (TS_State.touchY[0] > TOUCH_RECORD_YMIN) && (TS_State.touchY[0] < TOUCH_RECORD_YMAX))
//        {
//          AudioDemo.state = AUDIO_DEMO_IN;
//        }
//        if ((TS_State.touchX[0] > TOUCH_PLAYBACK_XMIN) && (TS_State.touchX[0] < TOUCH_PLAYBACK_XMAX) &&
//                 (TS_State.touchY[0] > TOUCH_PLAYBACK_YMIN) && (TS_State.touchY[0] < TOUCH_PLAYBACK_YMAX))
//    	if()
//        {
          AudioDemo.state = AUDIO_DEMO_PLAYBACK;
//          sprintf(signal_text, "wait");
//        }
//        if(True)//else
//        {
//          AudioDemo.state = AUDIO_DEMO_EXPLORE;
//        }

        /* Wait for touch released */
//        do
//        {
//          BSP_TS_GetState(&TS_State);
//        }while(TS_State.touchDetected > 0);
//      }
      break;

    case AUDIO_DEMO_EXPLORE:
      if(Appli_state == APPLICATION_READY)
      {
        if(Explorer_Process() > 0)
        {
//          LCD_ErrLog("There is no WAV file on the USB Key.\n");
//          AUDIO_ChangeSelectMode(AUDIO_SELECT_MENU);
          AudioDemo.state = AUDIO_DEMO_IDLE;
        }
        else
        {
          AudioDemo.state = AUDIO_DEMO_WAIT;
        }
      }
      else
      {
        AudioDemo.state = AUDIO_DEMO_WAIT;
      }
      break;

    case AUDIO_DEMO_PLAYBACK:
    	sprintf(signal_text, "playback");
      if(Appli_state == APPLICATION_READY)
      {
        if(AudioState == AUDIO_STATE_IDLE)
        {
          if(Explorer_Process() > 0)
          {
            //LCD_ErrLog("There is no WAV file on the USB Key.\n");
            //AUDIO_ChangeSelectMode(AUDIO_SELECT_MENU);
            AudioDemo.state = AUDIO_DEMO_IDLE;
            //sprintf(signal_text, "explorer_fail");
          }
          else
          {
            /* Start Playing */
            AudioState = AUDIO_STATE_INIT;
            //sprintf(signal_text, "audio_state_init");
          }


          if(AUDIO_PLAYER_Start(0) == AUDIO_ERROR_IO)
          {
            //AUDIO_ChangeSelectMode(AUDIO_SELECT_MENU);
            AudioDemo.state = AUDIO_DEMO_IDLE;
//            sprintf(signal_text, "audio_player_start_fail");
          }
        }
        else /* Not idle */
        {
          if(AUDIO_PLAYER_Process() == AUDIO_ERROR_IO)
          {
            //AUDIO_ChangeSelectMode(AUDIO_SELECT_MENU);
            AudioDemo.state = AUDIO_DEMO_IDLE;
//            sprintf(signal_text, "audio_player_process_fail");
          }
        }
      }
      else
      {
        AudioDemo.state = AUDIO_DEMO_WAIT;
      }
      break;

    default:
      break;
    }
  }

  if(Appli_state == APPLICATION_DISCONNECT)
  {
	sprintf(signal_text, "USB_disconnect");
	Appli_state = APPLICATION_IDLE;
    //AUDIO_ChangeSelectMode(AUDIO_SELECT_MENU);
    BSP_AUDIO_OUT_Stop(CODEC_PDWN_SW);
  }



  if(Appli_state == APPLICATION_IDLE)
  {
	sprintf(signal_text, "USB_idle");
  }


}

/*******************************************************************************
                            Static Functions
*******************************************************************************/

///**
//  * @brief  Changes the selection mode.
//  * @param  select_mode: Selection mode
//  * @retval None
//  */
//static void AUDIO_ChangeSelectMode(AUDIO_DEMO_SelectMode select_mode)
//{
//  if(select_mode == AUDIO_SELECT_MENU)
//  {
//    //LCD_LOG_UpdateDisplay();
//    AudioDemo.state = AUDIO_DEMO_IDLE;
//  }
//  else if(select_mode == AUDIO_PLAYBACK_CONTROL)
//  {
//    //LCD_ClearTextZone();
//  }
//}


