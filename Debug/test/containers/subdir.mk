################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../test/containers/ListTest.cpp \
../test/containers/StackTest.cpp 

OBJS += \
./test/containers/ListTest.o \
./test/containers/StackTest.o 

CPP_DEPS += \
./test/containers/ListTest.d \
./test/containers/StackTest.d 


# Each subdirectory must supply rules for building sources it contributes
test/containers/%.o: ../test/containers/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/Users/iainhemstock/hpc-gcc -I"/Users/iainhemstock/GitHub/Prism/external" -I"/Users/iainhemstock/GitHub/Prism/inc" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


