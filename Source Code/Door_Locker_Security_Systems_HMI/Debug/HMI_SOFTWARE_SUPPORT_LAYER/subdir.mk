################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HMI_SOFTWARE_SUPPORT_LAYER/HMI_software_support.c 

OBJS += \
./HMI_SOFTWARE_SUPPORT_LAYER/HMI_software_support.o 

C_DEPS += \
./HMI_SOFTWARE_SUPPORT_LAYER/HMI_software_support.d 


# Each subdirectory must supply rules for building sources it contributes
HMI_SOFTWARE_SUPPORT_LAYER/%.o: ../HMI_SOFTWARE_SUPPORT_LAYER/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


