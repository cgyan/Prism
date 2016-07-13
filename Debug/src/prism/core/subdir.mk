################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/prism/core/Mathf.cpp \
../src/prism/core/String.cpp 

OBJS += \
./src/prism/core/Mathf.o \
./src/prism/core/String.o 

CPP_DEPS += \
./src/prism/core/Mathf.d \
./src/prism/core/String.d 


# Each subdirectory must supply rules for building sources it contributes
src/prism/core/%.o: ../src/prism/core/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/Users/iainhemstock/hpc-gcc -I"/Users/iainhemstock/GitHub/Prism/external" -I"/Users/iainhemstock/GitHub/Prism/inc" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


