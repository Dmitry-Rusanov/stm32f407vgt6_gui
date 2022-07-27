################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/src/lv_misc/lv_anim.c \
../lvgl/src/lv_misc/lv_area.c \
../lvgl/src/lv_misc/lv_async.c \
../lvgl/src/lv_misc/lv_bidi.c \
../lvgl/src/lv_misc/lv_color.c \
../lvgl/src/lv_misc/lv_debug.c \
../lvgl/src/lv_misc/lv_fs.c \
../lvgl/src/lv_misc/lv_gc.c \
../lvgl/src/lv_misc/lv_ll.c \
../lvgl/src/lv_misc/lv_log.c \
../lvgl/src/lv_misc/lv_math.c \
../lvgl/src/lv_misc/lv_mem.c \
../lvgl/src/lv_misc/lv_printf.c \
../lvgl/src/lv_misc/lv_task.c \
../lvgl/src/lv_misc/lv_templ.c \
../lvgl/src/lv_misc/lv_txt.c \
../lvgl/src/lv_misc/lv_txt_ap.c \
../lvgl/src/lv_misc/lv_utils.c 

OBJS += \
./lvgl/src/lv_misc/lv_anim.o \
./lvgl/src/lv_misc/lv_area.o \
./lvgl/src/lv_misc/lv_async.o \
./lvgl/src/lv_misc/lv_bidi.o \
./lvgl/src/lv_misc/lv_color.o \
./lvgl/src/lv_misc/lv_debug.o \
./lvgl/src/lv_misc/lv_fs.o \
./lvgl/src/lv_misc/lv_gc.o \
./lvgl/src/lv_misc/lv_ll.o \
./lvgl/src/lv_misc/lv_log.o \
./lvgl/src/lv_misc/lv_math.o \
./lvgl/src/lv_misc/lv_mem.o \
./lvgl/src/lv_misc/lv_printf.o \
./lvgl/src/lv_misc/lv_task.o \
./lvgl/src/lv_misc/lv_templ.o \
./lvgl/src/lv_misc/lv_txt.o \
./lvgl/src/lv_misc/lv_txt_ap.o \
./lvgl/src/lv_misc/lv_utils.o 

C_DEPS += \
./lvgl/src/lv_misc/lv_anim.d \
./lvgl/src/lv_misc/lv_area.d \
./lvgl/src/lv_misc/lv_async.d \
./lvgl/src/lv_misc/lv_bidi.d \
./lvgl/src/lv_misc/lv_color.d \
./lvgl/src/lv_misc/lv_debug.d \
./lvgl/src/lv_misc/lv_fs.d \
./lvgl/src/lv_misc/lv_gc.d \
./lvgl/src/lv_misc/lv_ll.d \
./lvgl/src/lv_misc/lv_log.d \
./lvgl/src/lv_misc/lv_math.d \
./lvgl/src/lv_misc/lv_mem.d \
./lvgl/src/lv_misc/lv_printf.d \
./lvgl/src/lv_misc/lv_task.d \
./lvgl/src/lv_misc/lv_templ.d \
./lvgl/src/lv_misc/lv_txt.d \
./lvgl/src/lv_misc/lv_txt_ap.d \
./lvgl/src/lv_misc/lv_utils.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/src/lv_misc/%.o: ../lvgl/src/lv_misc/%.c lvgl/src/lv_misc/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/rus/Yandex.Disk/Projects/stm32_linux/stm32f407/stm32f407vgt6_gui/ili9325" -I"/home/rus/Yandex.Disk/Projects/stm32_linux/stm32f407/stm32f407vgt6_gui/lvgl" -I"/home/rus/Yandex.Disk/Projects/stm32_linux/stm32f407/stm32f407vgt6_gui/lvgl/porting" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

