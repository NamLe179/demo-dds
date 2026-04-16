cmake_minimum_required(VERSION 3.16)
project(DDS_HighFreq LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
add_compile_options(-O3 -march=native)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
message(STATUS "Qt version: ${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}")

find_package(fastdds 3 REQUIRED)
message(STATUS "FastDDS version: ${fastdds_VERSION}")

#  Fast DDS statistics
set(FASTDDS_STATS_PROFILE_SOURCE ${CMAKE_SOURCE_DIR}/config/fastdds_statistics_profiles.xml)
set(FASTDDS_STATS_PROFILE_FILE ${CMAKE_BINARY_DIR}/fastdds_statistics_profiles.xml)
configure_file(${FASTDDS_STATS_PROFILE_SOURCE} ${FASTDDS_STATS_PROFILE_FILE} COPYONLY)
message(STATUS "Fast DDS statistics profile: ${FASTDDS_STATS_PROFILE_FILE}")

set(GENERATED_DIR ${CMAKE_SOURCE_DIR}/generated)
set(GENERATED_SOURCES
    ${GENERATED_DIR}/ObjectStatePubSubTypes.cxx
    ${GENERATED_DIR}/ObjectStateTypeObjectSupport.cxx
)

# Static library 
add_library(dds_types STATIC ${GENERATED_SOURCES})
target_include_directories(dds_types PUBLIC ${GENERATED_DIR})
target_link_libraries(dds_types PUBLIC fastdds)
set_target_properties(dds_types PROPERTIES AUTOMOC OFF)

# 1. dds_publisher
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
)
target_link_libraries(dds_publisher PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    dds_types
    fastdds
)
target_compile_definitions(dds_publisher PRIVATE
    FASTDDS_STATISTICS_DEFAULT_PROFILES_FILE="${FASTDDS_STATS_PROFILE_FILE}"
)

# 2. dds_subscriber
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
)
target_link_libraries(dds_subscriber PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    dds_types
    fastdds
)
target_compile_definitions(dds_subscriber PRIVATE
    FASTDDS_STATISTICS_DEFAULT_PROFILES_FILE="${FASTDDS_STATS_PROFILE_FILE}"
)