################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Project/STM32F10x_StdPeriph_Examples/TIM/InputCapture/main.c \
D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Project/STM32F10x_StdPeriph_Examples/TIM/InputCapture/stm32f10x_it.c \
D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Project/STM32F10x_StdPeriph_Examples/TIM/InputCapture/system_stm32f10x.c 

OBJS += \
./STM32F10x_StdPeriph_Lib_V3.6.0/Project/STM32F10x_StdPeriph_Examples/TIM/InputCapture/main.o \
./STM32F10x_StdPeriph_Lib_V3.6.0/Project/STM32F10x_StdPeriph_Examples/TIM/InputCapture/stm32f10x_it.o \
./STM32F10x_StdPeriph_Lib_V3.6.0/Project/STM32F10x_StdPeriph_Examples/TIM/InputCapture/system_stm32f10x.o 

C_DEPS += \
./STM32F10x_StdPeriph_Lib_V3.6.0/Project/STM32F10x_StdPeriph_Examples/TIM/InputCapture/main.d \
./STM32F10x_StdPeriph_Lib_V3.6.0/Project/STM32F10x_StdPeriph_Examples/TIM/InputCapture/stm32f10x_it.d \
./STM32F10x_StdPeriph_Lib_V3.6.0/Project/STM32F10x_StdPeriph_Examples/TIM/InputCapture/system_stm32f10x.d 


# Each subdirectory must supply rules for building sources it contributes
STM32F10x_StdPeriph_Lib_V3.6.0/Project/STM32F10x_StdPeriph_Examples/TIM/InputCapture/main.o: D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Project/STM32F10x_StdPeriph_Examples/TIM/InputCapture/main.c STM32F10x_StdPeriph_Lib_V3.6.0/Project/STM32F10x_StdPeriph_Examples/TIM/InputCapture/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F401RETx -DSTM32F4 -c -I../Inc -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/CMSIS/Documentation" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/STM32F10x_StdPeriph_Driver/src" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/STM32F10x_StdPeriph_Driver/src" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/STM3210C_EVAL" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/STM32F10x_StdPeriph_Driver/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"STM32F10x_StdPeriph_Lib_V3.6.0/Project/STM32F10x_StdPeriph_Examples/TIM/InputCapture/main.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
STM32F10x_StdPeriph_Lib_V3.6.0/Project/STM32F10x_StdPeriph_Examples/TIM/InputCapture/stm32f10x_it.o: D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Project/STM32F10x_StdPeriph_Examples/TIM/InputCapture/stm32f10x_it.c STM32F10x_StdPeriph_Lib_V3.6.0/Project/STM32F10x_StdPeriph_Examples/TIM/InputCapture/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F401RETx -DSTM32F4 -c -I../Inc -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/CMSIS/Documentation" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/STM32F10x_StdPeriph_Driver/src" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/STM32F10x_StdPeriph_Driver/src" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/STM3210C_EVAL" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/STM32F10x_StdPeriph_Driver/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"STM32F10x_StdPeriph_Lib_V3.6.0/Project/STM32F10x_StdPeriph_Examples/TIM/InputCapture/stm32f10x_it.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
STM32F10x_StdPeriph_Lib_V3.6.0/Project/STM32F10x_StdPeriph_Examples/TIM/InputCapture/system_stm32f10x.o: D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Project/STM32F10x_StdPeriph_Examples/TIM/InputCapture/system_stm32f10x.c STM32F10x_StdPeriph_Lib_V3.6.0/Project/STM32F10x_StdPeriph_Examples/TIM/InputCapture/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F401RETx -DSTM32F4 -c -I../Inc -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/CMSIS/Documentation" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/STM32F10x_StdPeriph_Driver/src" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/STM32F10x_StdPeriph_Driver/src" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/STM3210C_EVAL" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/STM32F10x_StdPeriph_Driver/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"STM32F10x_StdPeriph_Lib_V3.6.0/Project/STM32F10x_StdPeriph_Examples/TIM/InputCapture/system_stm32f10x.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

