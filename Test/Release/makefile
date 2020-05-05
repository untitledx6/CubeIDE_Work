################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/subdir.mk
-include Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
-include Core/USER/WIFI/subdir.mk
-include Core/USER/PID/subdir.mk
-include Core/USER/OLED/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
NUCLEO_FreeRTOS_LedAndOled.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
NUCLEO_FreeRTOS_LedAndOled.list \

OBJCOPY_BIN += \
NUCLEO_FreeRTOS_LedAndOled.bin \


# All Target
all: NUCLEO_FreeRTOS_LedAndOled.elf secondary-outputs

# Tool invocations
NUCLEO_FreeRTOS_LedAndOled.elf: $(OBJS) $(USER_OBJS) D:\work\study\stm32\cubeIDEworkspace\Test\STM32F103RBTX_FLASH.ld
	arm-none-eabi-gcc -o "NUCLEO_FreeRTOS_LedAndOled.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"D:\work\study\stm32\cubeIDEworkspace\Test\STM32F103RBTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="NUCLEO_FreeRTOS_LedAndOled.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

NUCLEO_FreeRTOS_LedAndOled.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "NUCLEO_FreeRTOS_LedAndOled.list"
	@echo 'Finished building: $@'
	@echo ' '

NUCLEO_FreeRTOS_LedAndOled.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "NUCLEO_FreeRTOS_LedAndOled.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
