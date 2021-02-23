################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../USB_HOST/App/usb_host.c 

C_DEPS += \
./USB_HOST/App/usb_host.d 

OBJS += \
./USB_HOST/App/usb_host.o 


# Each subdirectory must supply rules for building sources it contributes
USB_HOST/App/usb_host.o: ../USB_HOST/App/usb_host.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F769xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/thomas/STM32CubeIDE/workspace_1.5.1/laboratoryjny/Drivers/BSP/Components" -I"C:/Users/thomas/STM32CubeIDE/workspace_1.5.1/laboratoryjny/Drivers/BSP/Components/Common" -I"C:/Users/thomas/STM32CubeIDE/workspace_1.5.1/laboratoryjny/Drivers/BSP/STM32F769I-Discovery" -I../FATFS/Target -I../FATFS/App -I../USB_HOST/App -I../USB_HOST/Target -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc -I"C:/Users/thomas/Desktop/dl/disco_board/download/en.stm32cubef7_v1-16-0/STM32Cube_FW_F7_V1.16.0/Drivers/BSP/STM32F769I-Discovery" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"USB_HOST/App/usb_host.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

