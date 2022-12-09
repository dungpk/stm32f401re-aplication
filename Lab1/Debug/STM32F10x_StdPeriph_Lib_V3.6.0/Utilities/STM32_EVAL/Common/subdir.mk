################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/Common/fonts.c \
D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/Common/lcd_log.c \
D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/Common/stm32_eval_i2c_ee.c \
D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/Common/stm32_eval_i2c_tsensor.c \
D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/Common/stm32_eval_sdio_sd.c \
D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/Common/stm32_eval_spi_flash.c \
D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/Common/stm32_eval_spi_sd.c 

OBJS += \
./STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/Common/fonts.o \
./STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/Common/lcd_log.o \
./STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/Common/stm32_eval_i2c_ee.o \
./STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/Common/stm32_eval_i2c_tsensor.o \
./STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/Common/stm32_eval_sdio_sd.o \
./STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/Common/stm32_eval_spi_flash.o \
./STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/Common/stm32_eval_spi_sd.o 

C_DEPS += \
./STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/Common/fonts.d \
./STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/Common/lcd_log.d \
./STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/Common/stm32_eval_i2c_ee.d \
./STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/Common/stm32_eval_i2c_tsensor.d \
./STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/Common/stm32_eval_sdio_sd.d \
./STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/Common/stm32_eval_spi_flash.d \
./STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/Common/stm32_eval_spi_sd.d 


# Each subdirectory must supply rules for building sources it contributes
STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/Common/fonts.o: D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/Common/fonts.c STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/Common/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F401RETx -DSTM32F4 -c -I../Inc -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/CMSIS/Documentation" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/STM32F10x_StdPeriph_Driver/src" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/STM32F10x_StdPeriph_Driver/src" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/STM3210C_EVAL" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/STM32F10x_StdPeriph_Driver/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/Common/fonts.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/Common/lcd_log.o: D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/Common/lcd_log.c STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/Common/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F401RETx -DSTM32F4 -c -I../Inc -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/CMSIS/Documentation" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/STM32F10x_StdPeriph_Driver/src" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/STM32F10x_StdPeriph_Driver/src" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/STM3210C_EVAL" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/STM32F10x_StdPeriph_Driver/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/Common/lcd_log.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/Common/stm32_eval_i2c_ee.o: D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/Common/stm32_eval_i2c_ee.c STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/Common/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F401RETx -DSTM32F4 -c -I../Inc -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/CMSIS/Documentation" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/STM32F10x_StdPeriph_Driver/src" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/STM32F10x_StdPeriph_Driver/src" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/STM3210C_EVAL" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/STM32F10x_StdPeriph_Driver/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/Common/stm32_eval_i2c_ee.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/Common/stm32_eval_i2c_tsensor.o: D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/Common/stm32_eval_i2c_tsensor.c STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/Common/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F401RETx -DSTM32F4 -c -I../Inc -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/CMSIS/Documentation" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/STM32F10x_StdPeriph_Driver/src" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/STM32F10x_StdPeriph_Driver/src" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/STM3210C_EVAL" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/STM32F10x_StdPeriph_Driver/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/Common/stm32_eval_i2c_tsensor.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/Common/stm32_eval_sdio_sd.o: D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/Common/stm32_eval_sdio_sd.c STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/Common/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F401RETx -DSTM32F4 -c -I../Inc -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/CMSIS/Documentation" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/STM32F10x_StdPeriph_Driver/src" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/STM32F10x_StdPeriph_Driver/src" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/STM3210C_EVAL" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/STM32F10x_StdPeriph_Driver/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/Common/stm32_eval_sdio_sd.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/Common/stm32_eval_spi_flash.o: D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/Common/stm32_eval_spi_flash.c STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/Common/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F401RETx -DSTM32F4 -c -I../Inc -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/CMSIS/Documentation" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/STM32F10x_StdPeriph_Driver/src" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/STM32F10x_StdPeriph_Driver/src" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/STM3210C_EVAL" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/STM32F10x_StdPeriph_Driver/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/Common/stm32_eval_spi_flash.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/Common/stm32_eval_spi_sd.o: D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/Common/stm32_eval_spi_sd.c STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/Common/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F401RETx -DSTM32F4 -c -I../Inc -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/CMSIS/Documentation" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/STM32F10x_StdPeriph_Driver/src" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/STM32F10x_StdPeriph_Driver/src" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/STM3210C_EVAL" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x" -I"D:/IOT/IoT303/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/STM32F10x_StdPeriph_Driver/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"STM32F10x_StdPeriph_Lib_V3.6.0/Utilities/STM32_EVAL/Common/stm32_eval_spi_sd.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

