cmake_minimum_required(VERSION 3.0)

project(IoDrums)

# Finding dependencies
INCLUDE(FindPkgConfig)
# RtMidi
pkg_check_modules(RTMIDI REQUIRED rtmidi)

# Include dependencies
include_directories(src) 
include_directories(${RTMIDI_INCLUDE_DIRS})

# Components
set(PLAYER src/player/MidiPlayer.cpp)
set(SRC    src/main.cpp ${PLAYER})

add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} ${RTMIDI_LIBRARIES})
