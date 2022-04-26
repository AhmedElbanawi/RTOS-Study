################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC.c \
../CO_SCH.c \
../DIO.c \
../DIO_CFG.c \
../KEYPAD.c \
../KEYPAD_CFG.c \
../LCD.c \
../QUEUE.c \
../TMP_SENSOR.c \
../TMR0.c \
../URT.c \
../main.c 

OBJS += \
./ADC.o \
./CO_SCH.o \
./DIO.o \
./DIO_CFG.o \
./KEYPAD.o \
./KEYPAD_CFG.o \
./LCD.o \
./QUEUE.o \
./TMP_SENSOR.o \
./TMR0.o \
./URT.o \
./main.o 

C_DEPS += \
./ADC.d \
./CO_SCH.d \
./DIO.d \
./DIO_CFG.d \
./KEYPAD.d \
./KEYPAD_CFG.d \
./LCD.d \
./QUEUE.d \
./TMP_SENSOR.d \
./TMR0.d \
./URT.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


