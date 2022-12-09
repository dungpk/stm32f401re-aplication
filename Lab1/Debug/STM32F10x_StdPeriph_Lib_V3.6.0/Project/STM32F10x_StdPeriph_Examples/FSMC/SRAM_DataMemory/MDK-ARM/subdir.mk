################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Project/STM32F10x_StdPeriph_Examples/FSMC/SRAM_DataMemory/MDK-ARM/startup_stm32f10x_hd.s \
D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Project/STM32F10x_StdPeriph_Examples/FSMC/SRAM_DataMemory/MDK-ARM/startup_stm32f10x_hd_vl.s \
D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Project/STM32F10x_StdPeriph_Examples/FSMC/SRAM_DataMemory/MDK-ARM/startup_stm32f10x_xl.s 

OBJS += \
./STM32F10x_StdPeriph_Lib_V3.6.0/Project/STM32F10x_StdPeriph_Examples/FSMC/SRAM_DataMemory/MDK-ARM/startup_stm32f10x_hd.o \
./STM32F10x_StdPeriph_Lib_V3.6.0/Project/STM32F10x_StdPeriph_Examples/FSMC/SRAM_DataMemory/MDK-ARM/startup_stm32f10x_hd_vl.o \
./STM32F10x_StdPeriph_Lib_V3.6.0/Project/STM32F10x_StdPeriph_Examples/FSMC/SRAM_DataMemory/MDK-ARM/startup_stm32f10x_xl.o 

S_DEPS += \
./STM32F10x_StdPeriph_Lib_V3.6.0/Project/STM32F10x_StdPeriph_Examples/FSMC/SRAM_DataMemory/MDK-ARM/startup_stm32f10x_hd.d \
./STM32F10x_StdPeriph_Lib_V3.6.0/Project/STM32F10x_StdPeriph_Examples/FSMC/SRAM_DataMemory/MDK-ARM/startup_stm32f10x_hd_vl.d \
./STM32F10x_StdPeriph_Lib_V3.6.0/Project/STM32F10x_StdPeriph_Examples/FSMC/SRAM_DataMemory/MDK-ARM/startup_stm32f10x_xl.d 


# Each subdirectory must supply rules for building sources it contributes
STM32F10x_StdPeriph_Lib_V3.6.0/Project/STM32F10x_StdPeriph_Examples/FSMC/SRAM_DataMemory/MDK-ARM/startup_stm32f10x_hd.o: D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Project/STM32F10x_StdPeriph_Examples/FSMC/SRAM_DataMemory/MDK-ARM/startup_stm32f10x_hd.s STM32F10x_StdPeriph_Lib_V3.6.0/Project/STM32F10x_StdPeriph_Examples/FSMC/SRAM_DataMemory/MDK-ARM/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -c -x assembler-with-cpp -MMD -MP -MF"STM32F10x_StdPeriph_Lib_V3.6.0/Project/STM32F10x_StdPeriph_Examples/FSMC/SRAM_DataMemory/MDK-ARM/startup_stm32f10x_hd.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"
STM32F10x_StdPeriph_Lib_V3.6.0/Project/STM32F10x_StdPeriph_Examples/FSMC/SRAM_DataMemory/MDK-ARM/startup_stm32f10x_hd_vl.o: D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Project/STM32F10x_StdPeriph_Examples/FSMC/SRAM_DataMemory/MDK-ARM/startup_stm32f10x_hd_vl.s STM32F10x_StdPeriph_Lib_V3.6.0/Project/STM32F10x_StdPeriph_Examples/FSMC/SRAM_DataMemory/MDK-ARM/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -c -x assembler-with-cpp -MMD -MP -MF"STM32F10x_StdPeriph_Lib_V3.6.0/Project/STM32F10x_StdPeriph_Examples/FSMC/SRAM_DataMemory/MDK-ARM/startup_stm32f10x_hd_vl.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"
STM32F10x_StdPeriph_Lib_V3.6.0/Project/STM32F10x_StdPeriph_Examples/FSMC/SRAM_DataMemory/MDK-ARM/startup_stm32f10x_xl.o: D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Project/STM32F10x_StdPeriph_Examples/FSMC/SRAM_DataMemory/MDK-ARM/startup_stm32f10x_xl.s STM32F10x_StdPeriph_Lib_V3.6.0/Project/STM32F10x_StdPeriph_Examples/FSMC/SRAM_DataMemory/MDK-ARM/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -c -x assembler-with-cpp -MMD -MP -MF"STM32F10x_StdPeriph_Lib_V3.6.0/Project/STM32F10x_StdPeriph_Examples/FSMC/SRAM_DataMemory/MDK-ARM/startup_stm32f10x_xl.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

