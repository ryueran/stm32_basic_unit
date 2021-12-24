cmake_minimum_required(VERSION 3.15)
project(free_rtos LANGUAGES C ASM)
ENABLE_LANGUAGE( ASM)
add_library(free_rtos STATIC)
set(CMAKE_CXX_STANDARD 11)
# set_source_files_properties(Startup/startup_stm32f030x8.s PROPERTIES COMPILE_FLAGS "-x assembler-with-cpp")

target_sources(free_rtos
PUBLIC
    Source/croutine.c
    Source/event_groups.c
    Source/list.c
    Source/queue.c
    Source/stream_buffer.c
    Source/tasks.c
    Source/timers.c
    Source/portable/GCC/ARM_CM0/port.c
    Source/portable/MemMang/heap_1.c
)

target_include_directories(free_rtos 
PUBLIC
    Source/portable/GCC/ARM_CM0
    Source
    Source/include
    ${CMAKE_CURRENT_SOURCE_DIR}
)