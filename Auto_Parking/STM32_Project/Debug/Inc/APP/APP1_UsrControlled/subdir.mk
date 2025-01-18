################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/APP/APP1_UsrControlled/APP1_UsrControlled.c 

OBJS += \
./Inc/APP/APP1_UsrControlled/APP1_UsrControlled.o 

C_DEPS += \
./Inc/APP/APP1_UsrControlled/APP1_UsrControlled.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/APP/APP1_UsrControlled/APP1_UsrControlled.o: ../Inc/APP/APP1_UsrControlled/APP1_UsrControlled.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F3 -DDEBUG -DSTM32F303RETx -DNUCLEO_F303RE -c -I../Inc -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/Auto_Parking/Inc/LIB" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/Auto_Parking/Inc/APP" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/Auto_Parking/Inc/HAL" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/Auto_Parking/Inc/LIB" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/Auto_Parking/Inc/MCAL" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/Auto_Parking/Inc/SERVICES" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/Auto_Parking/Inc/MCAL" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/APP/APP1_UsrControlled/APP1_UsrControlled.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

