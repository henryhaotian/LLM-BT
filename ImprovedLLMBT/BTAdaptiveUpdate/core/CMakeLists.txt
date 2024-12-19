cmake_minimum_required(VERSION 3.0)
project(YoubotBTCore VERSION 1.0)
add_definitions(-DNON_MATLAB_PARSING)
add_definitions(-DMAX_EXT_API_CONNECTIONS=255)
#set(CMAKE_INCLUDE_CURRENT_DIR ON)
#set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

set(CMAKE_BUILD_TYPE Release)
add_definitions( -Wall -lgtest -std=c++11  -pthread -lrt )
# Needed for using threads
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

#set(YARPBTCORE_VERSION 3.4.1)

#include(GenerateExportHeader)

INCLUDE_DIRECTORIES(${VREP_API_DIR})
#########################################################
# FIND GTest
#########################################################
find_package(GTest)
include_directories(${GTEST_INCLUDE_DIRS})
if(NOT GTEST_FOUND)
    message(WARNING " GTest not found!")
endif(NOT GTEST_FOUND)

#########################################################
# FIND Lua
#########################################################

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/vrep_api/)
#set(VREP_PROGRAMMING_DIR /home/miccol/V-REP_PRO_EDU_V3_5_0_Linux/programming/remoteApi)

#add_library( vrep ${VREP_SOURCE_FILES} ${VREP_HEADER_FILES})

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include/)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/icons/)

set(BT_CORE_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/ PARENT_SCOPE)

INCLUDE_DIRECTORIES(${YARP_BT_NODES_INCLUDE_DIRS})

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/gtest/include/)

if(APPLE)
   include_directories(AFTER "/opt/X11/include")
    set(CMAKE_OSX_ARCHITECTURES "x86_64")
    if(CMAKE_GENERATOR STREQUAL Xcode)
        set(CMAKE_OSX_DEPLOYMENT_TARGET "10.8")
    endif()
endif()

file(GLOB_RECURSE BT_CORE_HEADERS ${PROJECT_SOURCE_DIR}/include/*.h)

set(BT_CORE_SOURCES
${PROJECT_SOURCE_DIR}/src/action_node.cpp
${PROJECT_SOURCE_DIR}/src/condition_node.cpp
${PROJECT_SOURCE_DIR}/src/control_node.cpp
${PROJECT_SOURCE_DIR}/src/exceptions.cpp
${PROJECT_SOURCE_DIR}/src/leaf_node.cpp
${PROJECT_SOURCE_DIR}/src/tick_engine.cpp
${PROJECT_SOURCE_DIR}/src/fallback_node.cpp
${PROJECT_SOURCE_DIR}/src/parallel_node.cpp
${PROJECT_SOURCE_DIR}/src/sequence_node.cpp
${PROJECT_SOURCE_DIR}/src/fallback_node_with_memory.cpp
${PROJECT_SOURCE_DIR}/src/sequence_node_with_memory.cpp
${PROJECT_SOURCE_DIR}/src/tree_node.cpp
${PROJECT_SOURCE_DIR}/src/youbot_nodes.cpp
${PROJECT_SOURCE_DIR}/src/vrep_utilities.cpp
)

######################################################
# SETTING BINARIES AND LIBRARY OUTPUT LOCATIONS
######################################################
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/sample)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

######################################################
# COMPILING GTEST
#######################################################

########################################################
### COMPILING LIBRARY
########################################################

#add_executable(${PROJECT_NAME} "main.cpp" ${HEADER_FILES} ${SOURCE_FILES})
#set(CMAKE_PLATFORM_USES_PATH_WHEN_NO_SONAME FALSE)
#target_link_libraries(${PROJECT_NAME} vrep)

add_library(COREBTLIBRARY STATIC ${BT_CORE_SOURCES})
##target_include_directories (COREBTLIBRARY PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
#set(CMAKE_PLATFORM_USES_PATH_WHEN_NO_SONAME FALSE)
target_link_libraries(COREBTLIBRARY vrep)
##target_link_libraries(${PROJECT_NAME} vrep)

