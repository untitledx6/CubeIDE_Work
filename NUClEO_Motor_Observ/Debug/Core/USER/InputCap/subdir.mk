################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/USER/InputCap/inputcap.c 

OBJS += \
./Core/USER/InputCap/inputcap.o 

C_DEPS += \
./Core/USER/InputCap/inputcap.d 


# Each subdirectory must supply rules for building sources it contributes
Core/USER/InputCap/inputcap.o: ../Core/USER/InputCap/inputcap.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I"D:/work/study/stm32/cubeIDEworkspace/NUClEO_Motor_Observ/Core/USER/INC" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/USER/InputCap/inputcap.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

