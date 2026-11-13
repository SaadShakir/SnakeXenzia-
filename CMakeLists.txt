cmake_minimum_required(VERSION 3.16)
project(SnakeXenzia)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

add_executable(SnakeXenzia
    main.cpp
    Menu.cpp
    SnakeGame.cpp
)

target_link_libraries(SnakeXenzia
    sfml-graphics
    sfml-window
    sfml-system
)

# Find the main SFML folder from the SFMLConfig.cmake folder.
get_filename_component(SFML_ROOT "${SFML_DIR}/../../.." ABSOLUTE)

# Copy the font and other assets beside the program after building.
add_custom_command(TARGET SnakeXenzia POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/assets"
    "$<TARGET_FILE_DIR:SnakeXenzia>/assets"
)

# Copy the correct SFML DLL files for Debug or Release builds.
if(WIN32)
    add_custom_command(TARGET SnakeXenzia POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SFML_ROOT}/bin/$<IF:$<CONFIG:Debug>,sfml-graphics-d-2.dll,sfml-graphics-2.dll>"
        "$<TARGET_FILE_DIR:SnakeXenzia>"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SFML_ROOT}/bin/$<IF:$<CONFIG:Debug>,sfml-window-d-2.dll,sfml-window-2.dll>"
        "$<TARGET_FILE_DIR:SnakeXenzia>"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SFML_ROOT}/bin/$<IF:$<CONFIG:Debug>,sfml-system-d-2.dll,sfml-system-2.dll>"
        "$<TARGET_FILE_DIR:SnakeXenzia>"
    )
endif()
