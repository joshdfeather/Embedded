################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/Applications/ti/ccs1280/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=softlib --tmu_support=tmu0 --vcu_support=vcu2 --include_path="/Users/joshfeather/Documents/Embedded Coursework/Group53_Task1" --include_path="/Users/joshfeather/ti/C2000Ware_5_03_00_00/device_support/f2837xd/common/include" --include_path="/Users/joshfeather/ti/C2000Ware_5_03_00_00/device_support/f2837xd/common/source" --include_path="/Users/joshfeather/ti/C2000Ware_5_03_00_00/device_support/f2837xd/headers/include" --include_path="/Users/joshfeather/ti/C2000Ware_5_03_00_00/device_support/f2837xd/headers/source" --include_path="/Applications/ti/ccs1280/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --advice:performance=all --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


