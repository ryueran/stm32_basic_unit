cmake_minimum_required(VERSION 3.15)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

set(ASM_OPTIONS "-x assembler-with-cpp") 
set(OBJECT_GEN "-mcpu=cortex-m0")
set(OBJECT_GEN "-mthumb")
set(CMAKE_C_FLAGS "-mcpu=cortex-m0 -mthumb --specs=nosys.specs -pipe -fno-common -ffunction-sections -fdata-sections -mthumb -mno-thumb-interwork -mfpu=vfp -msoft-float")
set(CMAKE_ASM_FLAGS "-mcpu=cortex-m0 -mthumb")


project (led LANGUAGES C ASM)
add_executable(led_demo main.c stm32_hal_msp.c stm32f0xx_it.c)

add_subdirectory(HAL)
add_subdirectory(Third_Party/FreeRTOS)

target_link_libraries(led_demo soc_sp HAL_FLASH free_rtos)

target_include_directories(soc_sp 
PUBLIC
    HAL/include
    HAL/include/Legacy
    CMSIS/Device/ST/STM32F0xx/Include
    CMSIS/Include
    ../soc_sp/BSP/h_nec
    Third_Party/FreeRTOS/Source/include
)

target_include_directories(led_demo
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/HAL
)
