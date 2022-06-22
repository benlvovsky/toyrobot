################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ToyRobotRunner.cpp \
../src/cmdproc.cpp \
../src/toyrobot.cpp 

CPP_DEPS += \
./src/ToyRobotRunner.d \
./src/cmdproc.d \
./src/toyrobot.d 

OBJS += \
./src/ToyRobotRunner.o \
./src/cmdproc.o \
./src/toyrobot.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/ToyRobotRunner.d ./src/ToyRobotRunner.o ./src/cmdproc.d ./src/cmdproc.o ./src/toyrobot.d ./src/toyrobot.o

.PHONY: clean-src

