################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/HAL/SWITCH/SW.c \
../src/HAL/SWITCH/SW_config.c 

OBJS += \
./src/HAL/SWITCH/SW.o \
./src/HAL/SWITCH/SW_config.o 

C_DEPS += \
./src/HAL/SWITCH/SW.d \
./src/HAL/SWITCH/SW_config.d 


# Each subdirectory must supply rules for building sources it contributes
src/HAL/SWITCH/%.o: ../src/HAL/SWITCH/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F401xC -DUSE_HAL_DRIVER -DHSE_VALUE=25000000 -I"E:\tourkey\LCD_PROJECT_Saved11\include" -I"E:\tourkey\LCD_PROJECT_Saved11\include\HAL" -I"E:\tourkey\LCD_PROJECT_Saved11\include" -I"E:\tourkey\LCD_PROJECT_Saved11\include\HAL" -I"E:\tourkey\LCD_PROJECT_Saved11\include\LIB" -I"E:\tourkey\LCD_PROJECT_Saved11\include\MCAL" -I"E:\tourkey\LCD_PROJECT_Saved11\include\SCHED" -I"../include" -I"E:\tourkey\LCD_PROJECT_Saved11\include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


