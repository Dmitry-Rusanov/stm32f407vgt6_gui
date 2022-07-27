################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ili9325/porting/lv_port_disp.c \
../ili9325/porting/lv_port_fs_template.c \
../ili9325/porting/lv_port_indev.c 

OBJS += \
./ili9325/porting/lv_port_disp.o \
./ili9325/porting/lv_port_fs_template.o \
./ili9325/porting/lv_port_indev.o 

C_DEPS += \
./ili9325/porting/lv_port_disp.d \
./ili9325/porting/lv_port_fs_template.d \
./ili9325/porting/lv_port_indev.d 


# Each subdirectory must supply rules for building sources it contributes
ili9325/porting/%.o: ../ili9325/porting/%.c ili9325/porting/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/rus/Yandex.Disk/Projects/stm32_linux/stm32f407/stm32f407vgt6_gui/lvgl" -I"/home/rus/Yandex.Disk/Projects/stm32_linux/stm32f407/stm32f407vgt6_gui/ili9325" -I"/home/rus/Yandex.Disk/Projects/stm32_linux/stm32f407/stm32f407vgt6_gui/ili9325/porting" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

