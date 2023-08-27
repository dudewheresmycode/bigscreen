cmake_minimum_required(VERSION 2.8.8)
project(bigscreen)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(qxtglobalshortcut REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Xml REQUIRED)
find_package(Qt5Svg REQUIRED)

set(bin bigscreen)

include_directories(src)

FILE(GLOB src_sources src/*.cpp)
FILE(GLOB src_headers src/*.h)

add_executable(${bin} 
  ${src_sources}
  ${src_headers}
  library.qrc
)

target_link_libraries(${bin} qxtglobalshortcut)
target_link_libraries(${bin} Qt5::Widgets)
target_link_libraries(${bin} Qt5::Xml)
target_link_libraries(${bin} Qt5::Svg)