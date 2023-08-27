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

add_executable(${bin} 
  src/main.cpp
  src/mainWidget.cpp
  src/muteIcon.cpp
  src/volumeIcon.cpp
  src/volumeText.cpp
  src/trayWindow.cpp
  src/constants.h
  src/mainWidget.h
  src/muteIcon.h
  src/trayWindow.h
  src/volume.h
  src/volumeIcon.h
  src/volumeIndicator.h
  src/volumeText.h
  library.qrc
)

target_link_libraries(${bin} qxtglobalshortcut)
target_link_libraries(${bin} Qt5::Widgets)
target_link_libraries(${bin} Qt5::Xml)
target_link_libraries(${bin} Qt5::Svg)