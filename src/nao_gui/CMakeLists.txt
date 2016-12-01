cmake_minimum_required(VERSION 2.8.3)
project(nao_gui)

find_package(Qt5Widgets REQUIRED)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  roslib
  std_msgs
)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(nao_gui_INCLUDE_DIRECTORIES
        src
        include
        resources )

include_directories(${nao_gui_INCLUDE_DIRECTORIES}
                    ${Qt5Widgets_INCLUDE_DIRS}
                    ${catkin_INCLUDE_DIRS} )

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS geometry_msgs roscpp roslib std_msgs
	DEPENDS Qt5Widgets
)

file(GLOB nao_gui_SRCS src/*.cpp)
list(REMOVE_ITEM nao_gui_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp )
file(GLOB nao_gui_HDRS include/*.h)
file(GLOB nao_gui_UIS resources/*.ui)
file(GLOB nao_gui_QRSCS resources/qrc/*.qrc)

qt5_add_resources(nao_gui_VFS ${qt_ros_QRSCS}) #VFS = Virtual File System
qt5_wrap_cpp(nao_gui_MOCS ${nao_gui_HDRS})
qt5_wrap_ui(nao_gui_UI_HDRS ${nao_gui_UIS} )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_definitions(${Qt5Widgets_DEFINITIONS}
                ${catkin_DEFINITIONS} )

add_library(${PROJECT_NAME}
            ${nao_gui_SRCS}
            ${nao_gui_MOCS}
            ${nao_gui_UI_HDRS}
            ${nao_gui_VFS} )

add_executable(nao_gui_node src/main.cpp)

target_link_libraries(nao_gui_node
												${PROJECT_NAME}
                        Qt5::Widgets
                        ${catkin_LIBRARIES} )

## Add cmake target dependencies of the library
## as an example, code may need to be generated before libraries
## either from message generation or dynamic reconfigure
# add_dependencies(nao_gui ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Declare a C++ executable
# add_executable(nao_gui_node src/nao_gui_node.cpp)

## Add cmake target dependencies of the executable
## same as for the library above
# add_dependencies(nao_gui_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a library or executable target against
# target_link_libraries(nao_gui_node
#   ${catkin_LIBRARIES}
# )

#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
# install(PROGRAMS
#   scripts/my_python_script
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark executables and/or libraries for installation
# install(TARGETS nao_gui nao_gui_node
#   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark cpp header files for installation
# install(DIRECTORY include/${PROJECT_NAME}/
#   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#   FILES_MATCHING PATTERN "*.h"
#   PATTERN ".svn" EXCLUDE
# )

## Mark other files for installation (e.g. launch and bag files, etc.)
# install(FILES
#   # myfile1
#   # myfile2
#   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
# )

#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
# catkin_add_gtest(${PROJECT_NAME}-test test/test_nao_gui.cpp)
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
# endif()

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)
