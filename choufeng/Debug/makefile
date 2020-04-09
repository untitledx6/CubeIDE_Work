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
choufeng.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
choufeng.list \

OBJCOPY_HEX += \
choufeng.hex \

OBJCOPY_BIN += \
choufeng.bin \


# All Target
all: choufeng.elf secondary-outputs

# Tool invocations
choufeng.elf: $(OBJS) $(USER_OBJS) D:\work\study\stm32\cubeIDEworkspace\choufeng\STM32F103C8TX_FLASH.ld
	arm-none-eabi-gcc -o "choufeng.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"D:\work\study\stm32\cubeIDEworkspace\choufeng\STM32F103C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="choufeng.map" -Wl,--gc-sections -static -u_printf_float --specs=nano.specs -mfloat-abi=soft -mthumb -u _printf_float -u _scanf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

choufeng.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "choufeng.list"
	@echo 'Finished building: $@'
	@echo ' '

choufeng.hex: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "choufeng.hex"
	@echo 'Finished building: $@'
	@echo ' '

choufeng.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "choufeng.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
