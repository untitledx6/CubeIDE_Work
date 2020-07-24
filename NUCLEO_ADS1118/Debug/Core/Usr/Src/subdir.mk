################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Usr/Src/ADS1118.c 

OBJS += \
./Core/Usr/Src/ADS1118.o 

C_DEPS += \
./Core/Usr/Src/ADS1118.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Usr/Src/ADS1118.o: ../Core/Usr/Src/ADS1118.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I"C:/work/study/stm32/cubeIDEworkspace/NUCLEO_ADS1118/Core/Usr/INC" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Usr/Src/ADS1118.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

