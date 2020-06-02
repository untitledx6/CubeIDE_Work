################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/USER/WIFI/wifi.c 

OBJS += \
./Core/USER/WIFI/wifi.o 

C_DEPS += \
./Core/USER/WIFI/wifi.d 


# Each subdirectory must supply rules for building sources it contributes
Core/USER/WIFI/wifi.o: ../Core/USER/WIFI/wifi.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I"D:/work/study/stm32/cubeIDEworkspace/NUCLEO_IAP_BootLoader/Core/USER/INC" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/USER/WIFI/wifi.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

