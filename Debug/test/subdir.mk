################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../test/BitvectorTest.cpp \
../test/DequeTest.cpp \
../test/ListTest.cpp \
../test/PairTest.cpp \
../test/SharedDataPointerTest.cpp \
../test/SharedDataTest.cpp \
../test/StackTest.cpp \
../test/StringTest.cpp \
../test/TimeTest.cpp \
../test/algorithmsTest.cpp \
../test/functorTest.cpp 

OBJS += \
./test/BitvectorTest.o \
./test/DequeTest.o \
./test/ListTest.o \
./test/PairTest.o \
./test/SharedDataPointerTest.o \
./test/SharedDataTest.o \
./test/StackTest.o \
./test/StringTest.o \
./test/TimeTest.o \
./test/algorithmsTest.o \
./test/functorTest.o 

CPP_DEPS += \
./test/BitvectorTest.d \
./test/DequeTest.d \
./test/ListTest.d \
./test/PairTest.d \
./test/SharedDataPointerTest.d \
./test/SharedDataTest.d \
./test/StackTest.d \
./test/StringTest.d \
./test/TimeTest.d \
./test/algorithmsTest.d \
./test/functorTest.d 


# Each subdirectory must supply rules for building sources it contributes
test/%.o: ../test/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/Users/iainhemstock/hpc-gcc -I"/Users/iainhemstock/GitHub/Prism/external" -I"/Users/iainhemstock/GitHub/Prism/inc" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


