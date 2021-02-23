################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/STM32F769I-Discovery/stm32f769i_discovery.c \
../Drivers/BSP/STM32F769I-Discovery/stm32f769i_discovery_audio.c 

C_DEPS += \
./Drivers/BSP/STM32F769I-Discovery/stm32f769i_discovery.d \
./Drivers/BSP/STM32F769I-Discovery/stm32f769i_discovery_audio.d 

OBJS += \
./Drivers/BSP/STM32F769I-Discovery/stm32f769i_discovery.o \
./Drivers/BSP/STM32F769I-Discovery/stm32f769i_discovery_audio.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/STM32F769I-Discovery/stm32f769i_discovery.o: ../Drivers/BSP/STM32F769I-Discovery/stm32f769i_discovery.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F769xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/thomas/STM32CubeIDE/workspace_1.5.1/laboratoryjny/Drivers/BSP/Components" -I"C:/Users/thomas/STM32CubeIDE/workspace_1.5.1/laboratoryjny/Drivers/BSP/Components/Common" -I"C:/Users/thomas/STM32CubeIDE/workspace_1.5.1/laboratoryjny/Drivers/BSP/STM32F769I-Discovery" -I../FATFS/Target -I../FATFS/App -I../USB_HOST/App -I../USB_HOST/Target -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc -I"C:/Users/thomas/Desktop/dl/disco_board/download/en.stm32cubef7_v1-16-0/STM32Cube_FW_F7_V1.16.0/Drivers/BSP/STM32F769I-Discovery" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/BSP/STM32F769I-Discovery/stm32f769i_discovery.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/BSP/STM32F769I-Discovery/stm32f769i_discovery_audio.o: ../Drivers/BSP/STM32F769I-Discovery/stm32f769i_discovery_audio.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F769xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/thomas/STM32CubeIDE/workspace_1.5.1/laboratoryjny/Drivers/BSP/Components" -I"C:/Users/thomas/STM32CubeIDE/workspace_1.5.1/laboratoryjny/Drivers/BSP/Components/Common" -I"C:/Users/thomas/STM32CubeIDE/workspace_1.5.1/laboratoryjny/Drivers/BSP/STM32F769I-Discovery" -I../FATFS/Target -I../FATFS/App -I../USB_HOST/App -I../USB_HOST/Target -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc -I"C:/Users/thomas/Desktop/dl/disco_board/download/en.stm32cubef7_v1-16-0/STM32Cube_FW_F7_V1.16.0/Drivers/BSP/STM32F769I-Discovery" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/BSP/STM32F769I-Discovery/stm32f769i_discovery_audio.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

