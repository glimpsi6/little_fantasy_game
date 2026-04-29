cmake_minimum_required(VERSION 3.10)
project(lfg)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(libs/tinyxml2)

set(SFML_DIR "/opt/homebrew/opt/sfml@2/lib/cmake/SFML")
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)
file(COPY ${CMAKE_SOURCE_DIR}/code/assets DESTINATION ${CMAKE_BINARY_DIR})

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/code/include
    ${CMAKE_CURRENT_SOURCE_DIR}/code/src
)

set(HEADERS
    code/include/Core/Game.h
    code/include/Core/GameStateManager.h
    code/include/Core/InputManager.h
    code/include/Core/ResourceManager.h
    code/include/Entities/Entity.h
    code/include/Entities/Character.h
    code/include/Entities/Player.h
    code/include/Entities/Npc.h
    code/include/World/Map.h
    code/include/World/Collisions.h
)

set(SOURCES
    code/src/Core/main.cpp
    code/src/Core/InputManager.cpp
    code/src/Core/ResourceManager.cpp
    code/src/Core/Game.cpp
    code/src/Entities/Character.cpp
    code/src/Entities/Player.cpp
    code/src/Entities/Npc.cpp
    code/src/World/Map.cpp
    code/src/World/Collisions.cpp
)

add_executable(game ${SOURCES} ${HEADERS})
target_link_libraries(game sfml-graphics sfml-window sfml-audio sfml-system tinyxml2)
