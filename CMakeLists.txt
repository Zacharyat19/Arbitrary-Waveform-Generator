cmake_minimum_required(VERSION 3.20)
project(SpiAwgSim VERSION 1.0 LANGUAGES CXX)

cmake_policy(SET CMP0144 NEW)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(verilator REQUIRED)

set(VERILOG_SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/hw/DAC_SPI.sv
)

set(CXX_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/SpiDriver.cpp
)

add_executable(awg_sim ${CXX_SOURCES})

verilate(awg_sim
    SOURCES ${VERILOG_SOURCES}
    TRACE
    PREFIX Vdac_spi
)

target_include_directories(awg_sim PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/Inc 
    ${CMAKE_CURRENT_BINARY_DIR}
)