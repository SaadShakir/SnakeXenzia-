cmake_minimum_required(VERSION 3.16)
project(SnakeXenzia)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.6 COMPONENTS graphics window system audio REQUIRED)

add_executable(SnakeXenzia
    main.cpp
    Menu.cpp
    SnakeGame.cpp
)

target_link_libraries(SnakeXenzia
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)

# Find the main SFML folder from the SFMLConfig.cmake folder.
get_filename_component(SFML_ROOT "${SFML_DIR}/../../.." ABSOLUTE)

# Copy assets beside the program after building.
add_custom_command(TARGET SnakeXenzia POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/assets"
    "$<TARGET_FILE_DIR:SnakeXenzia>/assets"
)

# Copy SFML runtime DLLs, including Audio and its dependencies
# (such as OpenAL32 and audio decoding DLLs), beside the executable.
if(WIN32)
    add_custom_command(TARGET SnakeXenzia POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${SFML_ROOT}/bin"
        "$<TARGET_FILE_DIR:SnakeXenzia>"
    )
endif()
endif()
