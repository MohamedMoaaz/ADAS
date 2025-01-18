################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include Inc/SERVICES/SYS_DIG_Mng/subdir.mk
-include Inc/SERVICES/C6_TrafficLightV2I/subdir.mk
-include Inc/SERVICES/C5_PARKING/subdir.mk
-include Inc/SERVICES/C4_SLOT_FIND/subdir.mk
-include Inc/SERVICES/C3_VCLE_ALIGN/subdir.mk
-include Inc/SERVICES/C2_VCLE_CNTRL/subdir.mk
-include Inc/SERVICES/C1_US_SLCT/subdir.mk
-include Inc/MCAL/UART/subdir.mk
-include Inc/MCAL/STK/subdir.mk
-include Inc/MCAL/RCC/subdir.mk
-include Inc/MCAL/PWM/subdir.mk
-include Inc/MCAL/NVIC/subdir.mk
-include Inc/MCAL/ICU/subdir.mk
-include Inc/MCAL/GPIO/subdir.mk
-include Inc/LIB/subdir.mk
-include Inc/HAL/US/subdir.mk
-include Inc/HAL/DCMOTOR/subdir.mk
-include Inc/APP/APP1_UsrControlled/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Auto_Parking.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Auto_Parking.list \

OBJCOPY_BIN += \
Auto_Parking.bin \


# All Target
all: Auto_Parking.elf secondary-outputs

# Tool invocations
Auto_Parking.elf: $(OBJS) $(USER_OBJS) C:\Users\Abnaby\STM32CubeIDE\workspace_1.4.0\Auto_Parking\STM32F303RETX_FLASH.ld
	arm-none-eabi-gcc -o "Auto_Parking.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\Abnaby\STM32CubeIDE\workspace_1.4.0\Auto_Parking\STM32F303RETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Auto_Parking.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Auto_Parking.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Auto_Parking.list"
	@echo 'Finished building: $@'
	@echo ' '

Auto_Parking.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Auto_Parking.bin"
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
