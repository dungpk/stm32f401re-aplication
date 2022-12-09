################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/STM32L152_EVAL/stm32l152_eval.c \
D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/STM32L152_EVAL/stm32l152_eval_glass_lcd.c \
D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/STM32L152_EVAL/stm32l152_eval_i2c_ee.c \
D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/STM32L152_EVAL/stm32l152_eval_lcd.c 

OBJS += \
./STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/STM32L152_EVAL/stm32l152_eval.o \
./STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/STM32L152_EVAL/stm32l152_eval_glass_lcd.o \
./STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/STM32L152_EVAL/stm32l152_eval_i2c_ee.o \
./STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/STM32L152_EVAL/stm32l152_eval_lcd.o 

C_DEPS += \
./STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/STM32L152_EVAL/stm32l152_eval.d \
./STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/STM32L152_EVAL/stm32l152_eval_glass_lcd.d \
./STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/STM32L152_EVAL/stm32l152_eval_i2c_ee.d \
./STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/STM32L152_EVAL/stm32l152_eval_lcd.d 


# Each subdirectory must supply rules for building sources it contributes
STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/STM32L152_EVAL/stm32l152_eval.o: D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/STM32L152_EVAL/stm32l152_eval.c STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/STM32L152_EVAL/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F401RETx -DSTM32F4 -c -I../Inc -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/CMSIS/Documentation" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/STM32F10x_StdPeriph_Driver/src" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/STM32F10x_StdPeriph_Driver/src" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/STM3210C_EVAL" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/STM32F10x_StdPeriph_Driver/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/STM32L152_EVAL/stm32l152_eval.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/STM32L152_EVAL/stm32l152_eval_glass_lcd.o: D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/STM32L152_EVAL/stm32l152_eval_glass_lcd.c STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/STM32L152_EVAL/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F401RETx -DSTM32F4 -c -I../Inc -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/CMSIS/Documentation" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/STM32F10x_StdPeriph_Driver/src" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/STM32F10x_StdPeriph_Driver/src" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/STM3210C_EVAL" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/STM32F10x_StdPeriph_Driver/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/STM32L152_EVAL/stm32l152_eval_glass_lcd.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/STM32L152_EVAL/stm32l152_eval_i2c_ee.o: D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/STM32L152_EVAL/stm32l152_eval_i2c_ee.c STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/STM32L152_EVAL/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F401RETx -DSTM32F4 -c -I../Inc -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/CMSIS/Documentation" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/STM32F10x_StdPeriph_Driver/src" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/STM32F10x_StdPeriph_Driver/src" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/STM3210C_EVAL" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/STM32F10x_StdPeriph_Driver/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/STM32L152_EVAL/stm32l152_eval_i2c_ee.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/STM32L152_EVAL/stm32l152_eval_lcd.o: D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/STM32L152_EVAL/stm32l152_eval_lcd.c STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/STM32L152_EVAL/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F401RETx -DSTM32F4 -c -I../Inc -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/CMSIS/Documentation" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/STM32F10x_StdPeriph_Driver/src" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/STM32F10x_StdPeriph_Driver/src" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/STM3210C_EVAL" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/STM32F10x_StdPeriph_Driver/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/STM32L152_EVAL/stm32l152_eval_lcd.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

