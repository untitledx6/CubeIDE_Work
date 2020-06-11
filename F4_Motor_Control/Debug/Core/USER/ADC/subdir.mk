################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/USER/ADC/AdcDma.c 

OBJS += \
./Core/USER/ADC/AdcDma.o 

C_DEPS += \
./Core/USER/ADC/AdcDma.d 


# Each subdirectory must supply rules for building sources it contributes
Core/USER/ADC/AdcDma.o: ../Core/USER/ADC/AdcDma.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I"D:/work/study/stm32/cubeIDEworkspace/F4_Motor_Control/Core/USER/INC" -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/USER/ADC/AdcDma.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

