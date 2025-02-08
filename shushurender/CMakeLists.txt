cmake_minimum_required(VERSION 3.13)

project(shushurender VERSION 1.0)

# compiler flag
set(CMAKE_DEBUG_POSTFIX "_d")

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Od")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g0")
endif()

#----------------------------------------------------SET OUTPUT PATH------------------------------------------------------------

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(RUN_DIR ${PROJECT_SOURCE_DIR}/bin)
if(MSVC)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE")
endif()
if (CMAKE_BUILD_TYPE MATCHES "Debug")
    add_compile_definitions(_DEBUG)
endif()

# for multi-config builds (e.g. msvc)
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/bin )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/lib )
    set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/lib )
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )

#----------------------------------------------------THIRD PARTY LIBS-----------------------------------------------------------
# opengl
find_package(OpenGL REQUIRED)

# glfw
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(thirdparty/glfw)

# assimp
add_subdirectory(thirdparty/assimp)
if(MSVC)
    set_target_properties(assimp PROPERTIES OUTPUT_NAME assimp )
endif()

# imgui
add_subdirectory(thirdparty/imgui)
target_link_libraries(imgui PUBLIC glfw)

# glm
add_subdirectory(thirdparty/glm)

#----------------------------------------------------INCLUDE THIRDPARTY----------------------------------------------------------
include_directories(thirdparty/glfw/include)
include_directories(thirdparty/imgui)
include_directories(thirdparty/glm)
include_directories(thirdparty/glad/include)

#----------------------------------------------------LINKING LIBS PATH-----------------------------------------------------------
link_directories(${CMAKE_BINARY_DIR}/lib)

#----------------------------------------------------LINK EXECUTABLE AND LIBS----------------------------------------------------
set(LIBS ${OPENGL_LIBRARIES} optimized glfw3 assimp imgui debug glfw3_d assimp_d imgui_d)

#----------------------------------------------------COMPILE EXECUTABLE----------------------------------------------------------
# create filter in solution explorer
function(assign_source_group)
    foreach(_source IN ITEMS ${ARGN})
        if (IS_ABSOLUTE "${_source}")
            file(RELATIVE_PATH _source_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${_source}")
        else()
            set(_source_rel "${_source}")
        endif()
        get_filename_component(_source_path "${_source_rel}" PATH)
        string(REPLACE "/" "\\" _source_path_msvc "${_source_path}")
        source_group("${_source_path_msvc}" FILES "${_source}")
    endforeach()
endfunction(assign_source_group)

set(
    source_list 
    "thirdparty/glad/src/glad.c"
    "source/tools/stb_image.h"
    "source/tools/stb_image.cpp"
    "source/tools/debug_tools.h"
    "source/tools/debug_message.h"
    "source/tools/debug_message.cpp"    
    "source/platform/platform.h"
    "source/platform/platform.cpp"
    "source/render/shushurender.h"
    "source/render/shushurender.cpp"
    "source/render/backend/graphics_backend.h"
    "source/render/backend/opengl/opengl_handler.h"
)

assign_source_group(${source_list})

include_directories("source")

add_executable(shushurender WIN32 ${source_list})

target_compile_features(shushurender PRIVATE cxx_std_17)

set_property(TARGET shushurender PROPERTY DEBUG_POSTFIX _d)
if(MSVC)
    set_property(TARGET shushurender PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
endif()

target_link_libraries(shushurender ${LIBS})
add_dependencies(shushurender glfw assimp imgui)

ADD_CUSTOM_TARGET(debug ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE:STRING=Debug ${PROJECT_SOURCE_DIR})
ADD_CUSTOM_TARGET(release ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE:STRING=Release ${PROJECT_SOURCE_DIR})