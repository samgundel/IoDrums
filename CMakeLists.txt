cmake_minimum_required(VERSION 3.0)

project(IoDrums)

# Finding dependencies
include(FindPkgConfig)
# RtMidi
pkg_check_modules(RTMIDI REQUIRED rtmidi)

find_package(Threads REQUIRED)
set(THREADS_PREFER_PTHREAD_FLAG ON)

# Include dependencies
include_directories(src) 
include_directories(${RTMIDI_INCLUDE_DIRS})

# Components
set(PLAYER src/player/MidiPlayer.cpp)
set(XDK    src/xdk/XDKSerialPortReader.cpp)
set(SRC    src/main.cpp ${PLAYER} ${XDK})

add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} ${RTMIDI_LIBRARIES} Threads::Threads)
