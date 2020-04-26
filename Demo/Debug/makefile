################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
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
Demo1_GREEN_lED.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Demo1_GREEN_lED.list \

OBJCOPY_BIN += \
Demo1_GREEN_lED.bin \


# All Target
all: Demo1_GREEN_lED.elf secondary-outputs

# Tool invocations
Demo1_GREEN_lED.elf: $(OBJS) $(USER_OBJS) D:\work\study\stm32\cubeIDEworkspace\Demo\STM32F103RBTX_FLASH.ld
	arm-none-eabi-gcc -o "Demo1_GREEN_lED.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"D:\work\study\stm32\cubeIDEworkspace\Demo\STM32F103RBTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Demo1_GREEN_lED.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Demo1_GREEN_lED.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Demo1_GREEN_lED.list"
	@echo 'Finished building: $@'
	@echo ' '

Demo1_GREEN_lED.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Demo1_GREEN_lED.bin"
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
