cmake_minimum_required(VERSION 3.10)
project(lfg)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(libs/tinyxml2)

set(SFML_DIR "/opt/homebrew/opt/sfml@2/lib/cmake/SFML")
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)
file(COPY ${CMAKE_SOURCE_DIR}/code/assets DESTINATION ${CMAKE_BINARY_DIR})

set(HEADERS
    code/include/Game.h
    code/include/GameStateManager.h
    code/include/InputManager.h
    code/include/ResourceManager.h
    code/include/Entity.h
    code/include/Character.h
    code/include/Player.h
    code/include/Collisions.h
)

set(SOURCES
    code/src/main.cpp
    code/src/InputManager.cpp
    code/src/ResourceManager.cpp
    code/src/Map.cpp
    code/src/Player.cpp
    code/src/Collisions.cpp
)

add_executable(game ${SOURCES} ${HEADERS})
target_include_directories(game PRIVATE ${CMAKE_SOURCE_DIR}/code/include)
target_link_libraries(game sfml-graphics sfml-window sfml-audio sfml-system tinyxml2)
