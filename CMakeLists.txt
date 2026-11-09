cmake_minimum_required(VERSION 3.20)
project(lfg LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(libs/tinyxml2)

set(SFML_DIR "/opt/homebrew/opt/sfml@2/lib/cmake/SFML")
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)
file(COPY ${CMAKE_SOURCE_DIR}/code/assets DESTINATION ${CMAKE_BINARY_DIR})

set(SOURCES
    code/src/Core/main.cpp
    code/src/Core/InputManager.cpp
    code/src/Core/ResourceManager.cpp
    code/src/Core/Game.cpp
    code/src/Entities/Character.cpp
    code/src/Entities/Player.cpp
    code/src/Entities/Object.cpp
    code/src/Entities/Npc.cpp
    code/src/World/Map.cpp
    code/src/World/Collisions.cpp
    code/src/Systems/InteractiveIcon.cpp
    code/src/Systems/Frame.cpp
    code/src/Systems/DialogueWindow.cpp
)

add_executable(lfg ${SOURCES})
target_include_directories(lfg PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/code/include)
target_link_libraries(lfg sfml-graphics sfml-window sfml-audio sfml-system tinyxml2)
# target_include_directories(lfg PRIVATE ${SFML_INCLUDE_DIR})