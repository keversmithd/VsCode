cmake_minimum_required(VERSION 3.15)

project(CLASS_TEMPLATE LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)



set(HEADER_DIR ${PROJECT_SOURCE_DIR}/headers)
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/sources)
set(WHEADER_DIR "X:/1.4 C++/Vscode/Dependencies/Wrappers")
set(WSOURCE_DIR "X:/1.4 C++/Vscode/Dependencies/Wrappers")

file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/sources/*.cpp")
file(GLOB HEADERS "${PROJECT_SOURCE_DIR}/headers/*.h")
file(GLOB WSOURCES "X:/1.4 C++/Vscode/Dependencies/Wrappers/*.cpp")
file(GLOB WHEADERS "X:/1.4 C++/Vscode/Dependencies/Wrappers/*.h")

set(IM_HEADER_DIR "X:/1.4 C++/Vscode/Dependencies/vendor/imgui")

file(GLOB IM_SOURCES "X:/1.4 C++/Vscode/Dependencies/vendor/imgui/*.cpp")


# Add the sources and headers to the project
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}")
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${WSOURCES} ${WHEADERS} ${IM_SOURCES}  main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ${HEADER_DIR} ${WHEADER_DIR} ${IM_HEADER_DIR})


include_directories("X:/1.4 C++/Vscode/Dependencies/GLEW/include")
include_directories("X:/1.4 C++/Vscode/Dependencies/OpenCL/include")
include_directories("X:/1.4 C++/Vscode/Dependencies/GLFW/include")
include_directories("X:/1.4 C++/Vscode/Dependencies/vendor")
target_link_libraries(${PROJECT_NAME} opengl32)
target_link_libraries(${PROJECT_NAME} "${PROJECT_SOURCE_DIR}/glfw3.dll")
target_link_libraries(${PROJECT_NAME} "${PROJECT_SOURCE_DIR}/glew32.dll")
target_link_libraries(${PROJECT_NAME} "X:\\1.4 C++\\Vscode\\Dependencies\\OpenCL\\lib\\OpenCL.lib")

set_property(TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<CONFIG:Debug>:Debug")
set_property(TARGET ${PROJECT_NAME} PROPERTY INTERPROCEDURAL_OPTIMIZATION "true")
set_property(TARGET ${PROJECT_NAME} PROPERTY MSVC_INCREMENTAL_LINK "true")