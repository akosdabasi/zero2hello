cmake_minimum_required(VERSION 4.0)

#specify search paths for 'include' command to look for cmake modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

project(z2h)
message("Build type: "              ${CMAKE_BUILD_TYPE})

#for simpler reference and to access it in included files
set(proj_path	${CMAKE_CURRENT_LIST_DIR})

#specify the language
enable_language(C ASM)
set(CMAKE_C_STANDARD                11)
set(CMAKE_C_STANDARD_REQUIRED       ON)

#target specification
set(target_name                 ${CMAKE_PROJECT_NAME})
include(source_list)
add_executable(${target_name} ${source_list})

include(include_list)
target_include_directories(${target_name} PRIVATE ${include_list})

set(compiler_definitions
	CMAKE_BUILD
)
target_compile_definitions(${target_name} PRIVATE ${compiler_definitions})

set(compiler_flags 
	-fdata-sections 		#create seperate sections for data -> garbage collection
	-ffunction-sections 	#create sperate sections for functions -> garbage collection
	-ffreestanding 			#no operating system used
	-mthumb					#generate code with thumb instruction set
    -mcpu=cortex-m3			
    -mfloat-abi=soft		#software floating point
	-Wall					#enables the most useful warnings
	-Wextra					#enables extra warnings
	-Werror					#treats all warnings as errors
	-Wshadow				#warns when local variable shadows an other variablefsa
)
target_compile_options(${target_name} PRIVATE
	${compiler_flags}	
)

set(linker_script               ${CMAKE_CURRENT_LIST_DIR}/linker.ld)
set(linker_flags 
	LINKER:-gc-sections				#enable garbage collection
	LINKER:-Map=${target_name}.map	#generate map file
	LINKER:--print-memory-usage
	-T${linker_script}				#use the defined linker script
	--specs=nosys.specs				#use nonsys.specs that disables standards systems libraries and startup files
)
target_link_options(${target_name} PRIVATE
	${linker_flags}
)

#execute post-build to print size
add_custom_command(TARGET ${target_name} POST_BUILD
	COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${target_name}>
)

#convert output to hex
add_custom_command(TARGET ${target_name} POST_BUILD
	COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${target_name}> ${target_name}.hex
)

#convert to bin
add_custom_command(TARGET ${target_name} POST_BUILD
	COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${target_name}> ${target_name}.bin
)