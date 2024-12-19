cmake_minimum_required(VERSION 3.2)

project(behavior_tree_editor)
add_definitions(-std=c++11  -pthread)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

set(Qt5_DIR "/opt/Qt5.9.2/5.9.2/gcc_64/lib/cmake/Qt5")
find_package(Qt5 COMPONENTS Core Widgets Gui OpenGL Xml)
if(Qt5_FOUND)
else(Qt5_FOUND)
  message(WARNING "Qt5 not found!")
endif(Qt5_FOUND)

find_package(Lua REQUIRED)
if(Lua_FOUND)
else(Lua_FOUND)
  message(WARNING "Lua not found!")
endif(Lua_FOUND)

INCLUDE_DIRECTORIES(${VREP_API_DIR})

find_package(Threads)
if(Threads_FOUND)
  message(STATUS "Threads found")
else(Threads_FOUND)
  message(WARNING "Threads not found!")
endif(Threads_FOUND)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_definitions(${Qt5Widgets_DEFINITIONS} -DNODE_EDITOR_STATIC -std=c++11)
set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

INCLUDE_DIRECTORIES(${catkin_INCLUDE_DIRS} ./qt_nodeditor/include )
INCLUDE_DIRECTORIES(${BT_CORE_INCLUDE_DIR})
INCLUDE_DIRECTORIES(./bt_editor)

file(GLOB_RECURSE LIB_CPPS  ./qt_nodeditor/src/*.cpp )
file(GLOB_RECURSE APP_CPPS  ./bt_editor/*.cpp )

qt5_add_resources(RESOURCES ./qt_nodeditor/resources/resources.qrc)

# Tell CMake to create the helloworld executable
add_library(qt_node_editor STATIC ${LIB_CPPS} ${RESOURCES})
target_link_libraries(qt_node_editor
                      Qt5::Core  Qt5::Widgets
                      Qt5::Gui   Qt5::OpenGL
                      Qt5::Xml  )

QT5_WRAP_UI(FORMS_HEADERS
  ./bt_editor/mainwindow.ui
  )

add_executable(BT ${APP_CPPS} ${FORMS_HEADERS} )
target_link_libraries(BT LINK_PUBLIC COREBTLIBRARY qt_node_editor ${CMAKE_THREAD_LIBS_INIT})

