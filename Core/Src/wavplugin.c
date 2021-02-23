/*
 * wavplugin.c
 *
 *  Created on: Feb 12, 2021
 *      Author: thomas
 */

#include "wavplugin.h"
//#include "Midi.h"


ALIGN_32BYTES (static AUDIO_OUT_BufferTypeDef  BufferCtl);
static int16_t FilePos = 0;
static uint32_t uwVolume = 54; // __IO

WAVE_FormatTypeDef WaveFormat;
FIL WavFile;
extern FILELIST_FileTypeDef FileList;
extern bool play_flag;
extern uint8_t grana;
extern bool button_clicked;

int16_t TempBufferptr[AUDIO_OUT_BUFFER_SIZE];
double time_expected=0.5;
bool zagrana = 0;
bool initialized = 0;
//
uint32_t bytes_to_read = 0;
uint32_t bytes_readed = 0;
//UINT new_rate=0;
//double rev = 1./48000;//0.000020333;
//int cnter=0;
//uint pbp = 0;

static AUDIO_ErrorTypeDef GetFileInfo(uint16_t file_idx, WAVE_FormatTypeDef *info);
static uint8_t PlayerInit(uint32_t AudioFreq);


AUDIO_ErrorTypeDef AUDIO_PLAYER_Init(void)
{
  if(BSP_AUDIO_OUT_Init(OUTPUT_DEVICE_AUTO, uwVolume, SAI_AUDIO_FREQUENCY_48K) == 0)
  {
    return AUDIO_ERROR_NONE;
  }
  else
  {
    return AUDIO_ERROR_IO;
  }
}


// funkcja odtwarzająca dane z pliku WAV
AUDIO_ErrorTypeDef AUDIO_PLAYER_Start(uint8_t idx)
{
  uint32_t bytesread;

  f_close(&WavFile);
  if(Explorer_GetWavObjectNumber() > idx)
  {
    GetFileInfo(idx, &WaveFormat);

    /*Adjust the Audio frequency */
//    time_expected += 0.2;
//    grana = 127;
    double duration = WaveFormat.FileSize/4.;
    UINT new_rate = duration*1./time_expected;
//    new_rate = (grana*1./127)*48000;
    new_rate = grana*1./127*48000;
    bytes_to_read = 3*new_rate;
//    rev = 1./new_rate;
//    new_rate = 48000;
    PlayerInit(new_rate); // alt arg: WaveFormat.SampleRate

    BufferCtl.state = BUFFER_OFFSET_NONE;


    /* Get Data from USB Flash Disk */
    f_lseek(&WavFile, 0);

    /* Fill whole buffer at first time */
//		if(f_read(&WavFile,
//			&TempBufferptr[0],
//			AUDIO_OUT_BUFFER_SIZE,//size/2,
//			(void *)&bytesread) == FR_OK)
//		{

			/* Clean Data Cache to update the content of the SRAM */
			SCB_CleanDCache_by_Addr((uint32_t*)&BufferCtl.buff[0], AUDIO_OUT_BUFFER_SIZE);

			AudioState = AUDIO_STATE_PLAY;

			memset(&BufferCtl.buff[0], 0, AUDIO_OUT_BUFFER_SIZE);
//			memcpy(&BufferCtl.buff[0], &TempBufferptr[0], AUDIO_OUT_BUFFER_SIZE);

//			BufferCtl.state = BUFFER_OFFSET_NONE;
//			BufferCtl.fptr += bytesread;
//
//			bytes_readed += bytesread;
//			if (bytes_readed > bytes_to_read)
//			{
//			zagrana=1;
//			bytes_readed=0;
////			initialized=0;
//			}
		  //AUDIO_PlaybackDisplayButtons();
		  //BSP_LCD_DisplayStringAt(250, LINE(9), (uint8_t *)"  [PLAY ]", LEFT_MODE);
	//      {
//	        if(bytesread != 0)
//	        {
			  BSP_AUDIO_OUT_Play((uint16_t*)&BufferCtl.buff[0], AUDIO_OUT_BUFFER_SIZE);
			  return AUDIO_ERROR_NONE;
//	        }

//		}
  }
  return AUDIO_ERROR_IO;
}


/**/
AUDIO_ErrorTypeDef AUDIO_PLAYER_Process(void)
{
  uint32_t bytesread;//, elapsed_time;
  AUDIO_ErrorTypeDef audio_error = AUDIO_ERROR_NONE;
  //uint8_t str[16];
  //static uint32_t prev_elapsed_time = 0xFFFFFFFF;

  switch(AudioState)
  {
  case AUDIO_STATE_PLAY:
	  if (button_clicked)
	  {
		  BSP_AUDIO_OUT_Stop(CODEC_PDWN_SW);
		  AudioState = AUDIO_STATE_NEXT;
		  button_clicked = 0;
		  break;
	  }
	  if(BufferCtl.fptr >= WaveFormat.FileSize )
	  {

	    f_lseek(&WavFile, 0);
	    BufferCtl.fptr=0;

	  }

	  if (play_flag && !zagrana && !initialized)
	  {
		  AUDIO_PLAYER_Start(FilePos);
		  initialized=1;
		  break;
	  }

//    double duration = WaveFormat.FileSize*1./WaveFormat.SampleRate;
//    UINT step = 1;//duration*1./time_expected;
//    UINT size = AUDIO_OUT_BUFFER_SIZE/2; //uwaga na size=0 !!!
//    TempBufferptr = realloc(TempBufferptr, AUDIO_OUT_BUFFER_SIZE/2*sizeof(uint8_t));
//    if (TempBufferptr == NULL) {
//        Error_Handler();
//        return AUDIO_ERROR_IO;
//      }

//    int16_t temp=0;
/* BUFFER_OFFSET_HALF*/

	  if (play_flag && !zagrana)
	  {
					if(BufferCtl.state == BUFFER_OFFSET_HALF)
					{
						 if(f_read(&WavFile,
									  &TempBufferptr[0],
									  AUDIO_OUT_BUFFER_SIZE/2,//size/2,
									(void *)&bytesread) != FR_OK)
						 {

							/* Clean Data Cache to update the content of the SRAM */
							SCB_CleanDCache_by_Addr((uint32_t*)&BufferCtl.buff[0], AUDIO_OUT_BUFFER_SIZE/2);
							BSP_AUDIO_OUT_Stop(CODEC_PDWN_SW);
							return AUDIO_ERROR_IO;
						 }


					  	 memcpy(&BufferCtl.buff[0], &TempBufferptr[0], AUDIO_OUT_BUFFER_SIZE/2);


					  	 BufferCtl.state = BUFFER_OFFSET_NONE;
					  	 BufferCtl.fptr += bytesread;

						bytes_readed += bytesread;
						if (bytes_readed > bytes_to_read)
						{
							zagrana=1;
							bytes_readed=0;
//							initialized=0;
						}
					}

/* BUFFER_OFFSET_FULL*/
					if(BufferCtl.state == BUFFER_OFFSET_FULL)
					{
						  if(f_read(&WavFile,
								  &TempBufferptr[0],
								  AUDIO_OUT_BUFFER_SIZE/2,//size/2,
									(void *)&bytesread) != FR_OK)
						  {
							/* Clean Data Cache to update the content of the SRAM */
								SCB_CleanDCache_by_Addr((uint32_t*)&BufferCtl.buff[AUDIO_OUT_BUFFER_SIZE /2], AUDIO_OUT_BUFFER_SIZE/2);
								BSP_AUDIO_OUT_Stop(CODEC_PDWN_SW);
								return AUDIO_ERROR_IO;
						  }

						  memcpy(&BufferCtl.buff[AUDIO_OUT_BUFFER_SIZE/2], &TempBufferptr[0], AUDIO_OUT_BUFFER_SIZE/2);


						  BufferCtl.state = BUFFER_OFFSET_NONE;
						  BufferCtl.fptr += bytesread;

							bytes_readed += bytesread;
							if (bytes_readed > bytes_to_read)
							{
								zagrana=1;
								bytes_readed=0;
//								initialized=0;
							}
						}



	  }
	  else
	  {
		  memset(&BufferCtl.buff[0], 0, AUDIO_OUT_BUFFER_SIZE);
	  }



    break;

  case AUDIO_STATE_STOP:
//    BSP_LCD_SetTextColor(LCD_COLOR_RED);
//    BSP_LCD_FillRect(TOUCH_STOP_XMIN, TOUCH_STOP_YMIN , /* Stop rectangle */
//                     TOUCH_STOP_XMAX - TOUCH_STOP_XMIN,
//                     TOUCH_STOP_YMAX - TOUCH_STOP_YMIN);
    BSP_AUDIO_OUT_Stop(CODEC_PDWN_SW);
    AudioState = AUDIO_STATE_IDLE;
    audio_error = AUDIO_ERROR_IO;
    break;

  case AUDIO_STATE_NEXT:
	zagrana=0;
	play_flag=0;
	if(++FilePos >= Explorer_GetWavObjectNumber())
	{
	  FilePos = 0;
	}
	BSP_AUDIO_OUT_Stop(CODEC_PDWN_SW);
	AUDIO_PLAYER_Start(FilePos);
	if(uwVolume == 0)
	{
	  BSP_AUDIO_OUT_SetVolume(uwVolume);
	}
	break;

//  case AUDIO_STATE_PREVIOUS:
//    if(--FilePos < 0)
//    {
//      FilePos = AUDIO_GetWavObjectNumber() - 1;
//    }
//    BSP_AUDIO_OUT_Stop(CODEC_PDWN_SW);
//    AUDIO_PLAYER_Start(FilePos);
//    if(uwVolume == 0)
//    {
//      BSP_AUDIO_OUT_SetVolume(uwVolume);
//    }
//    break;
//
//  case AUDIO_STATE_PAUSE:
//    BSP_LCD_SetTextColor(LCD_COLOR_CYAN);
//    BSP_LCD_DisplayStringAt(250, LINE(9), (uint8_t *)"  [PAUSE]", LEFT_MODE);
//    BSP_LCD_SetTextColor(LCD_COLOR_RED);    /* Display red pause rectangles */
//    BSP_LCD_FillRect(TOUCH_PAUSE_XMIN, TOUCH_PAUSE_YMIN , 15, TOUCH_PAUSE_YMAX - TOUCH_PAUSE_YMIN);
//    BSP_LCD_FillRect(TOUCH_PAUSE_XMIN + 20, TOUCH_PAUSE_YMIN, 15, TOUCH_PAUSE_YMAX - TOUCH_PAUSE_YMIN);
//    BSP_AUDIO_OUT_Pause();
//    AudioState = AUDIO_STATE_WAIT;
//    break;
//
//  case AUDIO_STATE_RESUME:
//    BSP_LCD_SetTextColor(LCD_COLOR_CYAN);
//    BSP_LCD_DisplayStringAt(250, LINE(9), (uint8_t *)"  [PLAY ]", LEFT_MODE);
//                                            /* Display blue cyan pause rectangles */
//    BSP_LCD_FillRect(TOUCH_PAUSE_XMIN, TOUCH_PAUSE_YMIN , 15, TOUCH_PAUSE_YMAX - TOUCH_PAUSE_YMIN);
//    BSP_LCD_FillRect(TOUCH_PAUSE_XMIN + 20, TOUCH_PAUSE_YMIN, 15, TOUCH_PAUSE_YMAX - TOUCH_PAUSE_YMIN);
//    BSP_AUDIO_OUT_Resume();
//    if(uwVolume == 0)
//    {
//      BSP_AUDIO_OUT_SetVolume(uwVolume);
//    }
//    AudioState = AUDIO_STATE_PLAY;
//    break;
//
//  case AUDIO_STATE_VOLUME_UP:
//    if( uwVolume <= 90)
//    {
//      uwVolume += 10;
//    }
//    BSP_AUDIO_OUT_SetVolume(uwVolume);
//    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//    sprintf((char *)str,  "Volume : %lu ", uwVolume);
//    BSP_LCD_DisplayStringAtLine(9, str);
//    AudioState = AUDIO_STATE_PLAY;
//    break;
//
//  case AUDIO_STATE_VOLUME_DOWN:
//    if( uwVolume >= 10)
//    {
//      uwVolume -= 10;
//    }
//    BSP_AUDIO_OUT_SetVolume(uwVolume);
//    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//    sprintf((char *)str,  "Volume : %lu ", uwVolume);
//    BSP_LCD_DisplayStringAtLine(9, str);
//    AudioState = AUDIO_STATE_PLAY;
//    break;

  case AUDIO_STATE_WAIT:
  case AUDIO_STATE_IDLE:
  case AUDIO_STATE_INIT:
  default:
    /* Update audio state machine according to touch acquisition */
//    AUDIO_AcquireTouchButtons();
    break;
  }
  return audio_error;
}


AUDIO_ErrorTypeDef AUDIO_PLAYER_Stop(void)
{
  AudioState = AUDIO_STATE_STOP;
  FilePos = 0;

  BSP_AUDIO_OUT_Stop(CODEC_PDWN_SW);
  f_close(&WavFile);
  return AUDIO_ERROR_NONE;
}



void BSP_AUDIO_OUT_TransferComplete_CallBack(void)
{
  if(AudioState == AUDIO_STATE_PLAY)
  {
    BufferCtl.state = BUFFER_OFFSET_FULL;
  }
}


void BSP_AUDIO_OUT_HalfTransfer_CallBack(void)
{
  if(AudioState == AUDIO_STATE_PLAY)
  {
    BufferCtl.state = BUFFER_OFFSET_HALF;
  }
}
/*******************************************************************************
                            Static Functions
*******************************************************************************/


static AUDIO_ErrorTypeDef GetFileInfo(uint16_t file_idx, WAVE_FormatTypeDef *info)
{
  uint32_t bytesread;
  //uint32_t duration;
  //uint8_t str[FILEMGR_FILE_NAME_SIZE + 20];

  if(f_open(&WavFile, (char *)FileList.file[file_idx].name, FA_OPEN_EXISTING | FA_READ) == FR_OK)
  {
    /* Fill the buffer to Send */
    if(f_read(&WavFile, info, sizeof(WaveFormat), (void *)&bytesread) == FR_OK)
    {
      //BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
      //sprintf((char *)str, "Playing file (%d/%d): %s",
      //        file_idx + 1, FileList.ptr,
      //        (char *)FileList.file[file_idx].name);
      //BSP_LCD_ClearStringLine(4);
      //BSP_LCD_DisplayStringAtLine(4, str);

      //BSP_LCD_SetTextColor(LCD_COLOR_CYAN);
      //sprintf((char *)str,  "Sample rate : %d Hz", (int)(info->SampleRate));
      //BSP_LCD_ClearStringLine(6);
      //BSP_LCD_DisplayStringAtLine(6, str);

      //sprintf((char *)str,  "Channels number : %d", info->NbrChannels);
      //BSP_LCD_ClearStringLine(7);
      //BSP_LCD_DisplayStringAtLine(7, str);

      //duration = info->FileSize / info->ByteRate;
      //sprintf((char *)str, "File Size : %d KB [%02d:%02d]", (int)(info->FileSize/1024), (int)(duration/60), (int)(duration%60));
      //BSP_LCD_ClearStringLine(8);
      //BSP_LCD_DisplayStringAtLine(8, str);
      //BSP_LCD_DisplayStringAt(263, LINE(8), (uint8_t *)"[00:00]", LEFT_MODE);

      //BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
      //sprintf((char *)str,  "Volume : %lu", uwVolume);
      //BSP_LCD_ClearStringLine(9);
      //BSP_LCD_DisplayStringAtLine(9, str);
      return AUDIO_ERROR_NONE;
    }
    f_close(&WavFile);
  }
  return AUDIO_ERROR_IO;
}




static uint8_t PlayerInit(uint32_t AudioFreq)
{
  /* Initialize the Audio codec and all related peripherals (I2S, I2C, IOExpander, IOs...) */
  if(BSP_AUDIO_OUT_Init(OUTPUT_DEVICE_BOTH, uwVolume, AudioFreq) != 0)
  {
    return 1;
  }
  else
  {
    BSP_AUDIO_OUT_SetAudioFrameSlot(CODEC_AUDIOFRAME_SLOT_02);
    return 0;
  }
}





//      	int cnter=0;
//      	double under_sinus=0;
//      	uint16_t temp_2=0;
//		for(UINT i=0; 2*i<=AUDIO_OUT_BUFFER_SIZE/2; i+=1)
//		{
////			if(4*cnter+3<AUDIO_OUT_BUFFER_SIZE/2)
////			{
//			under_sinus = 2*M_PI*i;
//			under_sinus *= under_sinus*1000*rev;
//			temp = (int16_t)32500.0*(sin(under_sinus)*0.5+1);
//			temp_2 = (uint16_t)temp;
////			TempBufferptr[AUDIO_OUT_BUFFER_SIZE/2+4*cnter]= temp_2>>8;
////			TempBufferptr[AUDIO_OUT_BUFFER_SIZE/2+4*cnter+1] = temp_2;
////			TempBufferptr[AUDIO_OUT_BUFFER_SIZE/2+4*cnter+2] = temp_2>>8;
////			TempBufferptr[AUDIO_OUT_BUFFER_SIZE/2+4*cnter+3] = temp_2;
//
////			TempBufferptr[2*cnter+1]=255*(sin(2*M_PI*i*1000*rev)*0.5+0.5);
////			TempBufferptr[2*cnter]=127;
//
//			if(2*i+1<AUDIO_OUT_BUFFER_SIZE/2)TempBufferptr[2*i+1]+=250*(sin(2*M_PI*pbp*1000*rev)*0.5);
//			TempBufferptr[2*i]+=250*(sin(2*M_PI*pbp*1000*rev)*0.5);
//			pbp++;
////			cnter++;
////			}
////			else break;
//		}
//		if(pbp*1000*rev>1)
//				{
//					pbp=0;
//		}

//      	int cnter = 0;
//		for(UINT i=0; i<size; i+=step)
//		{
//			BufferCtl.buff[(AUDIO_OUT_BUFFER_SIZE/2)+(cnter)]=TempBufferptr[i];
//			cnter++;
//		}

//    /* Display elapsed time */
//    elapsed_time = BufferCtl.fptr / WaveFormat.ByteRate;
//    if(prev_elapsed_time != elapsed_time)
//    {
//      prev_elapsed_time = elapsed_time;
//      sprintf((char *)str, "[%02d:%02d]", (int)(elapsed_time /60), (int)(elapsed_time%60));
//      BSP_LCD_SetTextColor(LCD_COLOR_CYAN);
//      BSP_LCD_DisplayStringAt(263, LINE(8), str, LEFT_MODE);
//      BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//    }
//
//    /* Update audio state machine according to touch acquisition */
//    AUDIO_AcquireTouchButtons();
