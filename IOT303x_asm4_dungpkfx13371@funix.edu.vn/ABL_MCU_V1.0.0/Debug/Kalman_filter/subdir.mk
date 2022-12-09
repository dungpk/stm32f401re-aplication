################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/IOT/Kalman_filter/kalman_filter.c 

OBJS += \
./Kalman_filter/kalman_filter.o 

C_DEPS += \
./Kalman_filter/kalman_filter.d 


# Each subdirectory must supply rules for building sources it contributes
Kalman_filter/kalman_filter.o: D:/IOT/Kalman_filter/kalman_filter.c Kalman_filter/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F401RETx -DSTM32F4 -c -I"D:/IOT/Kalman_filter" -I../Inc -I"D:/IOT/Kalman_filter" -I"D:/IOT/SDK_1.0.3_NUCLEO-F401RE/shared/Drivers/CMSIS/Include" -I"D:/IOT/SDK_1.0.3_NUCLEO-F401RE/shared/Drivers/STM32F401RE_StdPeriph_Driver/inc" -I"D:/IOT/SDK_1.0.3_NUCLEO-F401RE/shared/Middle/button" -I"D:/IOT/SDK_1.0.3_NUCLEO-F401RE/shared/Middle/buzzer" -I"D:/IOT/SDK_1.0.3_NUCLEO-F401RE/shared/Middle/led" -I"D:/IOT/SDK_1.0.3_NUCLEO-F401RE/shared/Middle/rtos" -I"D:/IOT/SDK_1.0.3_NUCLEO-F401RE/shared/Middle/sensor" -I"D:/IOT/SDK_1.0.3_NUCLEO-F401RE/shared/Middle/serial" -I"D:/IOT/SDK_1.0.3_NUCLEO-F401RE/shared/Middle/ucglib" -I"D:/IOT/SDK_1.0.3_NUCLEO-F401RE/shared/Utilities" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Kalman_filter/kalman_filter.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

