################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/porting/lv_port_disp.c \
../lvgl/porting/lv_port_fs_template.c \
../lvgl/porting/lv_port_indev_template.c 

OBJS += \
./lvgl/porting/lv_port_disp.o \
./lvgl/porting/lv_port_fs_template.o \
./lvgl/porting/lv_port_indev_template.o 

C_DEPS += \
./lvgl/porting/lv_port_disp.d \
./lvgl/porting/lv_port_fs_template.d \
./lvgl/porting/lv_port_indev_template.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/porting/%.o: ../lvgl/porting/%.c lvgl/porting/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/rus/Yandex.Disk/Projects/stm32_linux/stm32f407/stm32f407vgt6_gui/ili9325" -I"/home/rus/Yandex.Disk/Projects/stm32_linux/stm32f407/stm32f407vgt6_gui/lvgl" -I"/home/rus/Yandex.Disk/Projects/stm32_linux/stm32f407/stm32f407vgt6_gui/lvgl/porting" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

