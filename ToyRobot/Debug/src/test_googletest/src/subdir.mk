################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/test_googletest/src/test_counter.cpp 

CPP_DEPS += \
./src/test_googletest/src/test_counter.d 

OBJS += \
./src/test_googletest/src/test_counter.o 


# Each subdirectory must supply rules for building sources it contributes
src/test_googletest/src/%.o: ../src/test_googletest/src/%.cpp src/test_googletest/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/Users/ben/eclipse-workspace/googletestlib/include -O0 -g3 -Wall -c -fmessage-length=0 -std=gnu++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-test_googletest-2f-src

clean-src-2f-test_googletest-2f-src:
	-$(RM) ./src/test_googletest/src/test_counter.d ./src/test_googletest/src/test_counter.o

.PHONY: clean-src-2f-test_googletest-2f-src

