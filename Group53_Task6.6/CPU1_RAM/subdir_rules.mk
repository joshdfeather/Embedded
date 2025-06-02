################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
build-986866687: ../c2000.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"/Applications/ti/ccs1280/ccs/utils/sysconfig_1.21.0/sysconfig_cli.sh" --script "/Users/joshfeather/Documents/Embedded Coursework/Group53_Task6.6/c2000.syscfg" -o "syscfg" -s "/Users/joshfeather/ti/C2000Ware_5_03_00_00/.metadata/sdk.json" -d "F2837xD" --compiler ccs
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/board.c: build-986866687 ../c2000.syscfg
syscfg/board.h: build-986866687
syscfg/board.cmd.genlibs: build-986866687
syscfg/board.opt: build-986866687
syscfg/board.json: build-986866687
syscfg/pinmux.csv: build-986866687
syscfg/c2000ware_libraries.cmd.genlibs: build-986866687
syscfg/c2000ware_libraries.opt: build-986866687
syscfg/c2000ware_libraries.c: build-986866687
syscfg/c2000ware_libraries.h: build-986866687
syscfg/clocktree.h: build-986866687
syscfg: build-986866687

syscfg/%.obj: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/Applications/ti/ccs1280/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --include_path="/Users/joshfeather/Documents/Embedded Coursework/Group53_Task6.6" --include_path="/Users/joshfeather/Documents/Embedded Coursework/Group53_Task6.6/device" --include_path="/Users/joshfeather/ti/C2000Ware_5_03_00_00/driverlib/f2837xd/driverlib" --include_path="/Applications/ti/ccs1280/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --define=DEBUG --define=CPU1 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="syscfg/$(basename $(<F)).d_raw" --include_path="/Users/joshfeather/Documents/Embedded Coursework/Group53_Task6.6/CPU1_RAM/syscfg" --obj_directory="syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/Applications/ti/ccs1280/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --include_path="/Users/joshfeather/Documents/Embedded Coursework/Group53_Task6.6" --include_path="/Users/joshfeather/Documents/Embedded Coursework/Group53_Task6.6/device" --include_path="/Users/joshfeather/ti/C2000Ware_5_03_00_00/driverlib/f2837xd/driverlib" --include_path="/Applications/ti/ccs1280/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --define=DEBUG --define=CPU1 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="/Users/joshfeather/Documents/Embedded Coursework/Group53_Task6.6/CPU1_RAM/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


