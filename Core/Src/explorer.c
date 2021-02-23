/*
 * explorer.c
 *
 *  Created on: Feb 13, 2021
 *      Author: thomas
 */


#include "main.h"
#include "fatfs.h"
#include "usb_host.h"

extern USBH_HandleTypeDef hUsbHostHS;
extern uint8_t retUSBH; /* Return value for USBH */
extern char USBHPath[4]; /* USBH logical drive path */
extern FATFS USBHFatFS; /* File system object for USBH logical drive */
extern FIL USBHFile; /* File object for USBH */

FILELIST_FileTypeDef FileList;
uint16_t NumObs = 0;


/* initialize USB key storage*/
uint8_t Explorer_StorageInit(void)
{
  /* Link the USB Key disk I/O driver */
  if((f_mount(&USBHFatFS, (TCHAR const*)USBHPath, 0) != FR_OK))
  {
    /* FatFs Initialization Error */
    return 1;
  }
  else
  {
    return 0;
  }
}

/**
  * @brief  Copies disk content in the explorer list.
  * @param  None
  * @retval Operation result
  */
FRESULT Explorer_StorageParse(void)
{
  FRESULT res = FR_OK;
  FILINFO fno;
  DIR dir;
  char *fn;

  res = f_opendir(&dir, USBHPath);
  FileList.ptr = 0;

  if(res == FR_OK)
  {
    while(USBH_MSC_IsReady(&hUsbHostHS))
    {
      res = f_readdir(&dir, &fno);
      if(res != FR_OK || fno.fname[0] == 0)
      {
        break;
      }
      if(fno.fname[0] == '.')
      {
        continue;
      }

      fn = fno.fname;

      if(FileList.ptr < FILEMGR_LIST_DEPDTH)
      {
        if((fno.fattrib & AM_DIR) == 0)
        {
          if((strstr(fn, "wav")) || (strstr(fn, "WAV")))
          {
            strncpy((char *)FileList.file[FileList.ptr].name, (char *)fn, FILEMGR_FILE_NAME_SIZE);
            FileList.file[FileList.ptr].type = FILETYPE_FILE;
            FileList.ptr++;
          }
        }
      }
    }
  }
  NumObs = FileList.ptr;
  f_closedir(&dir);
  return res;
}


/**
  * @brief  Shows audio file (*.wav) on the root
  * @param  None
  * @retval None
  */
uint8_t Explorer_Process(void)
{
  //uint8_t i = 0;
  //uint8_t line_idx = 0;
  if(Explorer_StorageInit() == FR_OK)
  {
    if(Explorer_StorageParse() ==  FR_OK)
    {
      if(FileList.ptr > 0)
      {
        return 0;
      }
      return 1;
    }
    return 2;
  }
  else
  {
    return 3;
  }
}

/**
  * @brief  Gets Wav Object Number.
  * @param  None
  * @retval None
  */
uint16_t Explorer_GetWavObjectNumber(void)
{
//	char buffer[5];
//	sprintf(signal_text, itoa(NumObs, buffer, 10));
	return NumObs;
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
