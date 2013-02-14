################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
dsp_bios_cfg.cmd: ../dsp_bios_.tcf
	@echo 'Building file: $<'
	@echo 'Invoking: TConf Script Compiler'
	"C:/Program Files (x86)/Texas Instruments/xdctools_3_22_01_21/tconf" -b -Dconfig.importPath="C:/Program Files (x86)/Texas Instruments/bios_5_41_10_36/packages;" "$<"
	@echo 'Finished building: $<'
	@echo ' '

dsp_bios_cfg.s??: dsp_bios_cfg.cmd
dsp_bios_cfg_c.c: dsp_bios_cfg.cmd
dsp_bios_cfg.h: dsp_bios_cfg.cmd
dsp_bios_cfg.h??: dsp_bios_cfg.cmd
dsp_bios_.cdb: dsp_bios_cfg.cmd

dsp_bios_cfg.obj: .//dsp_bios_cfg.s?? $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c6000/bin/cl6x" -mv6700 -g --define="_DEBUG" --define="CHIP_6713" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c6000/include" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/C6000/dsk6713/include" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/C6000/csl/include" --include_path="C:/Users/Rich/Documents/Work/ICL 3rd Year/RTDSP/Lab3b/RTDSP/Debug" --include_path="C:/Program Files (x86)/Texas Instruments/bios_5_41_10_36/packages/ti/bios/include" --include_path="C:/Program Files (x86)/Texas Instruments/bios_5_41_10_36/packages/ti/rtdx/include/c6000" --diag_warning=225 --abi=coffabi --preproc_with_compile --preproc_dependency="dsp_bios_cfg.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

dsp_bios_cfg_c.obj: .//dsp_bios_cfg_c.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c6000/bin/cl6x" -mv6700 -g --define="_DEBUG" --define="CHIP_6713" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c6000/include" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/C6000/dsk6713/include" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/C6000/csl/include" --include_path="C:/Users/Rich/Documents/Work/ICL 3rd Year/RTDSP/Lab3b/RTDSP/Debug" --include_path="C:/Program Files (x86)/Texas Instruments/bios_5_41_10_36/packages/ti/bios/include" --include_path="C:/Program Files (x86)/Texas Instruments/bios_5_41_10_36/packages/ti/rtdx/include/c6000" --diag_warning=225 --abi=coffabi --preproc_with_compile --preproc_dependency="dsp_bios_cfg_c.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

sine.obj: ../sine.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c6000/bin/cl6x" -mv6700 -g --define="_DEBUG" --define="CHIP_6713" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c6000/include" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/C6000/dsk6713/include" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/C6000/csl/include" --include_path="C:/Users/Rich/Documents/Work/ICL 3rd Year/RTDSP/Lab3b/RTDSP/Debug" --include_path="C:/Program Files (x86)/Texas Instruments/bios_5_41_10_36/packages/ti/bios/include" --include_path="C:/Program Files (x86)/Texas Instruments/bios_5_41_10_36/packages/ti/rtdx/include/c6000" --diag_warning=225 --abi=coffabi --preproc_with_compile --preproc_dependency="sine.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '


