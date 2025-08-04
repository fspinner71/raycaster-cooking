cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(raycaster-cooking)

include_directories(include)
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

# add_library(SDL3 SHARED IMPORTED)
# add_library(SDL3_image SHARED IMPORTED)
# add_library(SDL3_ttf SHARED IMPORTED)
# add_library(SDL3_mixer SHARED IMPORTED)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi-") # or remove /Zi

# Disable debug information generation during linking for Release executables
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /DEBUG- /PDB:NONE") 

find_library(SDL3_PATH NAMES SDL3 HINTS ${CMAKE_SOURCE_DIR}/libs)
find_library(SDL3_IMAGE_PATH NAMES SDL3_image HINTS ${CMAKE_SOURCE_DIR}/libs)
find_library(SDL3_TTF_PATH NAMES SDL3_ttf HINTS ${CMAKE_SOURCE_DIR}/libs)
find_library(SDL3_MIXER_PATH NAMES SDL3_mixer HINTS ${CMAKE_SOURCE_DIR}/libs)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin")


add_executable(game ${SOURCES})

target_compile_options(game PRIVATE -w)
if(MSVW)
    target_compile_options(game PRIVATE /wd)
endif()

if (WIN32)

    message("WIN32 variable is TRUE, running Windows-specific commands.")

    add_custom_command(TARGET game POST_BUILD        
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  
            "${PROJECT_SOURCE_DIR}/libs/SDL3.dll" 
            $<TARGET_FILE_DIR:game>)            

    add_custom_command(TARGET game POST_BUILD  
        COMMAND ${CMAKE_COMMAND} -E copy_if_different 
            "${PROJECT_SOURCE_DIR}/libs/SDL3_ttf.dll"
            $<TARGET_FILE_DIR:game>)     

    add_custom_command(TARGET game POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${PROJECT_SOURCE_DIR}/libs/SDL3_image.dll"
            $<TARGET_FILE_DIR:game>)     

    add_custom_command(TARGET game POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${PROJECT_SOURCE_DIR}/libs/SDL3_mixer.dll"
            $<TARGET_FILE_DIR:game>)     


else()
    # Commands or logic for other operating systems
    message("WIN32 variable is FALSE, running non-Windows specific commands.")
endif()

add_custom_target(copy_assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/bin/assets
)
add_dependencies(game copy_assets)

if(SDL3_PATH)
    target_link_libraries(game ${SDL3_PATH})
else()
    message(FATAL_ERROR "SDL3 not found!")
endif()

if(SDL3_IMAGE_PATH)
    target_link_libraries(game ${SDL3_IMAGE_PATH})
else()
    message(FATAL_ERROR "SDL3_image not found!")
endif()

if(SDL3_TTF_PATH)
    target_link_libraries(game ${SDL3_TTF_PATH})
else()
    message(FATAL_ERROR "SDL3_ttf not found!")
endif()

if(SDL3_MIXER_PATH)
    target_link_libraries(game ${SDL3_MIXER_PATH})
else()
    message(FATAL_ERROR "SDL3_mixer not found!")
endif()