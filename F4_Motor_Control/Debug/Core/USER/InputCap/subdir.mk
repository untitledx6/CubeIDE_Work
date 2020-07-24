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
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I"C:/work/study/stm32/cubeIDEworkspace/F4_Motor_Control/Core/USER/INC" -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/USER/InputCap/inputcap.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

