################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/CMSIS/CM3/CoreSupport/core_cm3.c 

OBJS += \
./Libraries/CMSIS/CM3/CoreSupport/core_cm3.o 

C_DEPS += \
./Libraries/CMSIS/CM3/CoreSupport/core_cm3.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/CMSIS/CM3/CoreSupport/core_cm3.o: D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/CMSIS/CM3/CoreSupport/core_cm3.c Libraries/CMSIS/CM3/CoreSupport/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32F10X_MD -DDEBUG -DSTM32F100C8Tx -DSTM32 -DSTM32F1 -c -I../Inc -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/CMSIS/CM3/CoreSupport" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/STM32F10x_StdPeriph_Driver/src" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/STM32F10x_StdPeriph_Driver/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Libraries/CMSIS/CM3/CoreSupport/core_cm3.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

