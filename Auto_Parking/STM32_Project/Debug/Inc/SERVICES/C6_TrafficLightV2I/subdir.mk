################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/SERVICES/C6_TrafficLightV2I/C6_TrafficLight_V2I.c 

OBJS += \
./Inc/SERVICES/C6_TrafficLightV2I/C6_TrafficLight_V2I.o 

C_DEPS += \
./Inc/SERVICES/C6_TrafficLightV2I/C6_TrafficLight_V2I.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/SERVICES/C6_TrafficLightV2I/C6_TrafficLight_V2I.o: ../Inc/SERVICES/C6_TrafficLightV2I/C6_TrafficLight_V2I.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F3 -DDEBUG -DSTM32F303RETx -DNUCLEO_F303RE -c -I../Inc -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/Auto_Parking/Inc/LIB" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/Auto_Parking/Inc/APP" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/Auto_Parking/Inc/HAL" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/Auto_Parking/Inc/LIB" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/Auto_Parking/Inc/MCAL" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/Auto_Parking/Inc/SERVICES" -I"C:/Users/Abnaby/STM32CubeIDE/workspace_1.4.0/Auto_Parking/Inc/MCAL" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/SERVICES/C6_TrafficLightV2I/C6_TrafficLight_V2I.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

