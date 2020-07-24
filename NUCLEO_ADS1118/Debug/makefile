################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
-include Core/Usr/Src/subdir.mk
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
NUCLEO_ADS1118.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
NUCLEO_ADS1118.list \

OBJCOPY_BIN += \
NUCLEO_ADS1118.bin \


# All Target
all: NUCLEO_ADS1118.elf secondary-outputs

# Tool invocations
NUCLEO_ADS1118.elf: $(OBJS) $(USER_OBJS) C:\work\study\stm32\cubeIDEworkspace\NUCLEO_ADS1118\STM32F103RBTX_FLASH.ld
	arm-none-eabi-gcc -o "NUCLEO_ADS1118.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"C:\work\study\stm32\cubeIDEworkspace\NUCLEO_ADS1118\STM32F103RBTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="NUCLEO_ADS1118.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

NUCLEO_ADS1118.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "NUCLEO_ADS1118.list"
	@echo 'Finished building: $@'
	@echo ' '

NUCLEO_ADS1118.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "NUCLEO_ADS1118.bin"
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
