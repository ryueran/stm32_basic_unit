cmake_minimum_required(VERSION 3.9)
project(unit_test C)
enable_testing()

add_library(fff INTERFACE)
target_include_directories(fff INTERFACE fff)

add_library(unity OBJECT
    unity/src/unity.c
)

target_include_directories(unity PUBLIC ${CMAKE_CURRENT_LIST_DIR}/unity/src/)

set_source_files_properties(
    ../lib/src/platform/linux/string.c
    PROPERTIES COMPILE_DEFINITIONS _GNU_SOURCE
)

add_executable(test_base64
    test_example.c
    ../HAL/flash_sector_f0.c
)

get_property(targets DIRECTORY "${CMAKE_CURRENT_LIST_DIR}" PROPERTY BUILDSYSTEM_TARGETS)
foreach(tgt ${targets})
    get_target_property(target_type ${tgt} TYPE)
    if (target_type STREQUAL "EXECUTABLE")
        # add_dependencies(${tgt} cio::cio) # Necessary to generage version_private.h before compiling the tests.
        target_link_libraries(${tgt} fff unity)
        set_target_properties(${tgt} PROPERTIES
            C_STANDARD 11
            C_STANDARD_REQUIRED ON
            C_EXTENSIONS OFF
            C_CLANG_TIDY ""
        )
        target_include_directories(
            ${tgt} PUBLIC 
            ${includes}
            ../HAL
            ../../soc_sp/HAL/include
            ../../soc_sp/CMSIS/Device/ST/STM32F0xx/Include
            ../../soc_sp/CMSIS/Include
            )
        add_test(NAME lob COMMAND ${tgt})
    endif()

	if(CIO_ENABLE_LTO AND NOT ${target_type} STREQUAL "INTERFACE_LIBRARY")
        set_property(TARGET ${tgt} PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
    endif()
endforeach()
