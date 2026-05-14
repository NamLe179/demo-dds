cmake_minimum_required(VERSION 3.16)
project(DDS_HighFreq_RTI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
add_compile_options(-O3 -march=native)

# ─────────────────────────────────────────────────────────────────────────────
# Qt
# ─────────────────────────────────────────────────────────────────────────────
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
message(STATUS "Qt version: ${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}")

# ─────────────────────────────────────────────────────────────────────────────
# RTI Connext DDS
# Chạy lệnh gen code: rtiddsgen -language C++ -platform x64Linux4gcc8.3.0 -d generated/ ObjectState.idl
# ─────────────────────────────────────────────────────────────────────────────
if(NOT DEFINED NDDSHOME)
    if(DEFINED ENV{NDDSHOME})
        set(NDDSHOME $ENV{NDDSHOME})
    else()
        foreach(candidate
            "/opt/rti.com/rti_connext_dds-7.7.0"
            "/opt/rti_connext_dds-7.7.0"
            "$ENV{HOME}/rti_connext_dds-7.7.0"
        )
            if(EXISTS "${candidate}/include/ndds")
                set(NDDSHOME "${candidate}")
                message(STATUS "NDDSHOME auto-detected: ${NDDSHOME}")
                break()
            endif()
        endforeach()
    endif()
endif()

if(NOT DEFINED NDDSHOME OR NOT EXISTS "${NDDSHOME}/include/ndds")
    message(FATAL_ERROR
        "NDDSHOME không được set hoặc không hợp lệ.\n"
        "Thêm vào Qt Creator: Projects → Build → CMake → Add:\n"
        "  Name: NDDSHOME\n"
        "  Value: /opt/rti.com/rti_connext_dds-7.7.0\n"
        "Hoặc cmake -DNDDSHOME=/opt/rti.com/rti_connext_dds-7.7.0 .")
endif()
message(STATUS "NDDSHOME: ${NDDSHOME}")

# Platform 
if(NOT DEFINED CONNEXT_ARCH)
    set(CONNEXT_ARCH "x64Linux4gcc8.5.0")
endif()
message(STATUS "Connext arch: ${CONNEXT_ARCH}")

# Include và lib paths
set(CONNEXT_INCLUDE_DIR "${NDDSHOME}/include")
set(CONNEXT_INCLUDE_CPP "${NDDSHOME}/include/ndds")
set(CONNEXT_LIB_DIR     "${NDDSHOME}/lib/${CONNEXT_ARCH}")

# ── Tìm thư viện RTI ─────────────────────────────────────────────────────────
# nddscpp2 cho C++11 và nddscpp cho classic C++
find_library(CONNEXT_LIB_NDDS
    NAMES nddscpp
    PATHS ${CONNEXT_LIB_DIR}
    NO_DEFAULT_PATH
    REQUIRED)

find_library(CONNEXT_LIB_CORE
    NAMES nddscore nddsd
    PATHS ${CONNEXT_LIB_DIR}
    NO_DEFAULT_PATH
    REQUIRED)

find_library(CONNEXT_LIB_C
    NAMES nddsc
    PATHS ${CONNEXT_LIB_DIR}
    NO_DEFAULT_PATH
    REQUIRED)

if(NOT CONNEXT_LIB_NDDS OR NOT CONNEXT_LIB_CORE OR NOT CONNEXT_LIB_C)
    file(GLOB _found_libs "${CONNEXT_LIB_DIR}/libndds*.so*")
    message(STATUS "Libs found in ${CONNEXT_LIB_DIR}:")
    foreach(_l ${_found_libs})
        message(STATUS "  ${_l}")
    endforeach()
    message(FATAL_ERROR
        "Không tìm thấy thư viện RTI Connext trong: ${CONNEXT_LIB_DIR}\n"
        "Kiểm tra CONNEXT_ARCH có đúng không (hiện tại: ${CONNEXT_ARCH})\n"
        "Chạy: ls ${CONNEXT_LIB_DIR}/libndds*.so")
endif()

set(CONNEXT_LIBS
    ${CONNEXT_LIB_NDDS}
    ${CONNEXT_LIB_C}
    ${CONNEXT_LIB_CORE}
    dl pthread rt)

message(STATUS "Connext NDDS lib : ${CONNEXT_LIB_NDDS}")
message(STATUS "Connext CORE lib : ${CONNEXT_LIB_CORE}")
message(STATUS "Connext C    lib : ${CONNEXT_LIB_C}")

# ─────────────────────────────────────────────────────────────────────────────
# Generated type support 
# ─────────────────────────────────────────────────────────────────────────────
set(GENERATED_DIR ${CMAKE_SOURCE_DIR}/generated)
set(GENERATED_SOURCES
    ${GENERATED_DIR}/ObjectState.cxx
    ${GENERATED_DIR}/ObjectStatePlugin.cxx
    ${GENERATED_DIR}/ObjectStateSupport.cxx
)

# Kiểm tra các file generated 
foreach(f ${GENERATED_SOURCES})
    if(NOT EXISTS ${f})
        message(WARNING
            "File chưa được generate: ${f}\n"
            "Chạy rtiddsgen trước khi cmake:\n"
            "  \$NDDSHOME/bin/rtiddsgen -language C++11 "
            "-platform ${CONNEXT_ARCH} -d generated/ ObjectState.idl")
    endif()
endforeach()

# Static library cho generated types
add_library(dds_types STATIC ${GENERATED_SOURCES})
target_include_directories(dds_types PUBLIC
    ${GENERATED_DIR}
    ${CONNEXT_INCLUDE_DIR}
    ${CONNEXT_INCLUDE_CPP}
)
target_link_libraries(dds_types PUBLIC ${CONNEXT_LIBS})
target_compile_definitions(dds_types PUBLIC
    RTI_UNIX
    RTI_LINUX
    RTI_64BIT
)
set_target_properties(dds_types PROPERTIES AUTOMOC OFF)

# ─────────────────────────────────────────────────────────────────────────────
# 1. dds_publisher
# ─────────────────────────────────────────────────────────────────────────────
add_executable(dds_publisher
    publisher/main.cpp
    publisher/PublisherApp.cpp
    publisher/PublisherApp.h
)
set_target_properties(dds_publisher PROPERTIES
    AUTOMOC ON
    CXX_STANDARD 17
)
target_include_directories(dds_publisher PRIVATE
    ${GENERATED_DIR}
    ${CMAKE_SOURCE_DIR}/publisher
    ${CONNEXT_INCLUDE_DIR}
    ${CONNEXT_INCLUDE_CPP}
)
target_link_libraries(dds_publisher PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    dds_types
)
target_compile_definitions(dds_publisher PRIVATE
    RTI_UNIX RTI_LINUX RTI_64BIT
)

# ─────────────────────────────────────────────────────────────────────────────
# 2. dds_subscriber
# ─────────────────────────────────────────────────────────────────────────────
add_executable(dds_subscriber
    subscriber/main.cpp
    subscriber/SubscriberApp.cpp
    subscriber/SubscriberApp.h
)
set_target_properties(dds_subscriber PROPERTIES
    AUTOMOC ON
    CXX_STANDARD 17
)
target_include_directories(dds_subscriber PRIVATE
    ${GENERATED_DIR}
    ${CMAKE_SOURCE_DIR}/subscriber
    ${CONNEXT_INCLUDE_DIR}
    ${CONNEXT_INCLUDE_CPP}
)
target_link_libraries(dds_subscriber PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    dds_types
)
target_compile_definitions(dds_subscriber PRIVATE
    RTI_UNIX RTI_LINUX RTI_64BIT
)