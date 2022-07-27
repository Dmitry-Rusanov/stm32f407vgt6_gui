################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/examples/libs/png/img_wink_png.c \
../lvgl/examples/libs/png/lv_example_png_1.c 

OBJS += \
./lvgl/examples/libs/png/img_wink_png.o \
./lvgl/examples/libs/png/lv_example_png_1.o 

C_DEPS += \
./lvgl/examples/libs/png/img_wink_png.d \
./lvgl/examples/libs/png/lv_example_png_1.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/examples/libs/png/%.o: ../lvgl/examples/libs/png/%.c lvgl/examples/libs/png/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/rus/Yandex.Disk/Projects/stm32_linux/stm32f407/stm32f407vgt6_gui/lvgl" -I"/home/rus/Yandex.Disk/Projects/stm32_linux/stm32f407/stm32f407vgt6_gui/ili9325" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

