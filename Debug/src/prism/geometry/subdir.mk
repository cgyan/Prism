################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/prism/geometry/Circle.cpp \
../src/prism/geometry/Matrix4.cpp \
../src/prism/geometry/Point.cpp \
../src/prism/geometry/Pointf.cpp \
../src/prism/geometry/Quaternion.cpp \
../src/prism/geometry/Rect.cpp \
../src/prism/geometry/Size.cpp \
../src/prism/geometry/Vector2.cpp \
../src/prism/geometry/Vector3.cpp \
../src/prism/geometry/Vector4.cpp 

OBJS += \
./src/prism/geometry/Circle.o \
./src/prism/geometry/Matrix4.o \
./src/prism/geometry/Point.o \
./src/prism/geometry/Pointf.o \
./src/prism/geometry/Quaternion.o \
./src/prism/geometry/Rect.o \
./src/prism/geometry/Size.o \
./src/prism/geometry/Vector2.o \
./src/prism/geometry/Vector3.o \
./src/prism/geometry/Vector4.o 

CPP_DEPS += \
./src/prism/geometry/Circle.d \
./src/prism/geometry/Matrix4.d \
./src/prism/geometry/Point.d \
./src/prism/geometry/Pointf.d \
./src/prism/geometry/Quaternion.d \
./src/prism/geometry/Rect.d \
./src/prism/geometry/Size.d \
./src/prism/geometry/Vector2.d \
./src/prism/geometry/Vector3.d \
./src/prism/geometry/Vector4.d 


# Each subdirectory must supply rules for building sources it contributes
src/prism/geometry/%.o: ../src/prism/geometry/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/Users/iainhemstock/hpc-gcc -I"/Users/iainhemstock/GitHub/Prism/external" -I"/Users/iainhemstock/GitHub/Prism/inc" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


