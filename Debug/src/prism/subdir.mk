################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/prism/Char.cpp \
../src/prism/Circle.cpp \
../src/prism/Fraction.cpp \
../src/prism/Mathf.cpp \
../src/prism/Matrix4.cpp \
../src/prism/Point.cpp \
../src/prism/Pointf.cpp \
../src/prism/Quaternion.cpp \
../src/prism/Rect.cpp \
../src/prism/Size.cpp \
../src/prism/String.cpp \
../src/prism/Vector2.cpp \
../src/prism/Vector3.cpp \
../src/prism/Vector4.cpp 

OBJS += \
./src/prism/Char.o \
./src/prism/Circle.o \
./src/prism/Fraction.o \
./src/prism/Mathf.o \
./src/prism/Matrix4.o \
./src/prism/Point.o \
./src/prism/Pointf.o \
./src/prism/Quaternion.o \
./src/prism/Rect.o \
./src/prism/Size.o \
./src/prism/String.o \
./src/prism/Vector2.o \
./src/prism/Vector3.o \
./src/prism/Vector4.o 

CPP_DEPS += \
./src/prism/Char.d \
./src/prism/Circle.d \
./src/prism/Fraction.d \
./src/prism/Mathf.d \
./src/prism/Matrix4.d \
./src/prism/Point.d \
./src/prism/Pointf.d \
./src/prism/Quaternion.d \
./src/prism/Rect.d \
./src/prism/Size.d \
./src/prism/String.d \
./src/prism/Vector2.d \
./src/prism/Vector3.d \
./src/prism/Vector4.d 


# Each subdirectory must supply rules for building sources it contributes
src/prism/%.o: ../src/prism/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/Users/iainhemstock/hpc-gcc -I"/Users/iainhemstock/GitHub/Prism/external" -I"/Users/iainhemstock/GitHub/Prism/inc" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


