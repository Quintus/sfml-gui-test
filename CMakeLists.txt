cmake_minimum_required(VERSION 2.8.0)
project(ceguitest CXX)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")
add_definitions("-Wall -Wextra -pedantic -std=c++11")

find_package(PkgConfig)
find_package(OpenGL REQUIRED)
find_package(SFML COMPONENTS graphics window system REQUIRED)
find_package(DevIL COMPONENTS REQUIRED)
find_package(CEGUI COMPONENTS OpenGL)
pkg_check_modules(LibXmlPP REQUIRED libxml++-2.6)

add_definitions(${CEGUI_DEFINITIONS})
include_directories(
  ${SFML_INCLUDE_DIRS}
  ${CEGUI_INCLUDE_DIR}
  ${OPENGL_INCLUDE_DIR}
  ${LibXmlPP_INCLUDE_DIRS})

add_executable(ceguitest-manual src/manual_window_creation.cpp)
add_executable(ceguitest-xml src/xml_window_creation.cpp)
target_link_libraries(ceguitest-manual
  ${CEGUI_LIBRARIES}
  ${SFML_LIBRARIES}
  ${OPENGL_LIBRARIES}
  ${LibXmlPP_LIBRARIES})
target_link_libraries(ceguitest-xml
  ${CEGUI_LIBRARIES}
  ${SFML_LIBRARIES}
  ${OPENGL_LIBRARIES}
  ${LibXmlPP_LIBRARIES})
