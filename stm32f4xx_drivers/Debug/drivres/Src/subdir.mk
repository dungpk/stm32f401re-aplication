################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivres/Src/stm32f401_gpio_driver.c \
../drivres/Src/stm32f401_spi_driver.c 

OBJS += \
./drivres/Src/stm32f401_gpio_driver.o \
./drivres/Src/stm32f401_spi_driver.o 

C_DEPS += \
./drivres/Src/stm32f401_gpio_driver.d \
./drivres/Src/stm32f401_spi_driver.d 


# Each subdirectory must supply rules for building sources it contributes
drivres/Src/stm32f401_gpio_driver.o: ../drivres/Src/stm32f401_gpio_driver.c drivres/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F401RETx -DSTM32F4 -c -I../Inc -I"D:/IOT/IoT303/stm32f4xx_drivers/drivres/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"drivres/Src/stm32f401_gpio_driver.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
drivres/Src/stm32f401_spi_driver.o: ../drivres/Src/stm32f401_spi_driver.c drivres/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F401RETx -DSTM32F4 -c -I../Inc -I"D:/IOT/IoT303/stm32f4xx_drivers/drivres/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"drivres/Src/stm32f401_spi_driver.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

