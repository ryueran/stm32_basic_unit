cmake_minimum_required(VERSION 3.15)
project(HAL_FLASH LANGUAGES C ASM)
ENABLE_LANGUAGE( ASM)
add_library(HAL_FLASH STATIC)
set(CMAKE_CXX_STANDARD 11)
# set_source_files_properties(Startup/startup_stm32f030x8.s PROPERTIES COMPILE_FLAGS "-x assembler-with-cpp")

target_sources(HAL_FLASH
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/flash_sector_f0.c
)

target_include_directories(HAL_FLASH 
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ../../soc_sp/HAL/include
    ../../soc_sp/CMSIS/Device/ST/STM32F0xx/Include
    ../../soc_sp/CMSIS/Include
)