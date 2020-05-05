################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/USER/OLED/oled.c 

OBJS += \
./Core/USER/OLED/oled.o 

C_DEPS += \
./Core/USER/OLED/oled.d 


# Each subdirectory must supply rules for building sources it contributes
Core/USER/OLED/oled.o: ../Core/USER/OLED/oled.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/work/study/stm32/cubeIDEworkspace/Test/Core/USER/INC" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/USER/OLED/oled.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

