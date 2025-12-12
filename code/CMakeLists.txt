cmake_minimum_required(VERSION 3.10)
project(lfg)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_DIR "/opt/homebrew/opt/sfml@2/lib/cmake/SFML")
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

set(SOURCES
    src/main.cpp
    src/player.cpp
    src/map.cpp
)

set(HEADERS
    include/player.h
    include/map.h
)

add_executable(game ${SOURCES} ${HEADERS})
target_include_directories(game PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(game sfml-graphics sfml-window sfml-system)
