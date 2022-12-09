################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/main.o: ../Src/main.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32F10X_MD -DDEBUG -DSTM32F100C8Tx -DSTM32 -DSTM32F1 -c -I../Inc -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/CMSIS/CM3/CoreSupport" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/STM32F10x_StdPeriph_Driver/src" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/STM32F10x_StdPeriph_Driver/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/main.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/syscalls.o: ../Src/syscalls.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32F10X_MD -DDEBUG -DSTM32F100C8Tx -DSTM32 -DSTM32F1 -c -I../Inc -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/CMSIS/CM3/CoreSupport" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/STM32F10x_StdPeriph_Driver/src" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/STM32F10x_StdPeriph_Driver/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/syscalls.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/sysmem.o: ../Src/sysmem.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32F10X_MD -DDEBUG -DSTM32F100C8Tx -DSTM32 -DSTM32F1 -c -I../Inc -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/CMSIS/CM3/CoreSupport" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/STM32F10x_StdPeriph_Driver/src" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/STM32F10x_StdPeriph_Driver/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/sysmem.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

