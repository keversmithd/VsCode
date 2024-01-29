cmake_minimum_required(VERSION 3.15)
project(ASIOFresh LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_BUILD_TYPE "Ninja")
set(CMAKE_BUILD_TYPE Debug)

#IMGUI
set(IM_HEADER_DIR "${PROJECT_SOURCE_DIR}/../Dependencies/vendor/imgui")
file(GLOB IM_SOURCES "${PROJECT_SOURCE_DIR}/../Dependencies/vendor/imgui/*.cpp")


set(HEADER_DIR ${PROJECT_SOURCE_DIR}/headers)
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/sources)
set(ASIO_DIR_HEAD ${PROJECT_SOURCE_DIR}/ASIOSDK/headers)
set(ASIO_DIR_SOURCE ${PROJECT_SOURCE_DIR}/ASIOSDK/sources)
file(GLOB_RECURSE HEADER_FILES "${HEADER_DIR}/*.h")
file(GLOB_RECURSE SOURCE_FILE "${SOURCE_DIR}/*.cpp*")
file(GLOB_RECURSE ASIO_HEADER_FILES "${ASIO_DIR_HEAD}/*.h")
file(GLOB_RECURSE ASIO_SOURCE_FILE "${ASIO_DIR_SOURCE}/*.cpp*")


set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}")
add_executable(${PROJECT_NAME} ${SOURCE_FILE} ${HEADER_FILES} ${ASIO_SOURCE_FILE} ${ASIO_HEADER_FILES} ${IM_SOURCES}  test.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ${HEADER_DIR}  ${ASIO_DIR_HEAD} ${IM_HEADER_DIR})
target_link_libraries(${PROJECT_NAME} ole32 winmm uuid)

#Vendor Header
include_directories("${PROJECT_SOURCE_DIR}/../Dependencies/vendor")

#OpenGL Tools
include_directories("${PROJECT_SOURCE_DIR}/OpenGLTools")
include_directories("${PROJECT_SOURCE_DIR}/OpenGLTools/Cameras")
include_directories("${PROJECT_SOURCE_DIR}/OpenGLTools/Collisions")
include_directories("${PROJECT_SOURCE_DIR}/OpenGLTools/Geometry")
include_directories("${PROJECT_SOURCE_DIR}/OpenGLTools/glmmath")

include_directories("${PROJECT_SOURCE_DIR}/CStringTools")

#Graphic Objects
include_directories("${PROJECT_SOURCE_DIR}/Objects")
include_directories("${PROJECT_SOURCE_DIR}/Objects/GraphicVector")
include_directories("${PROJECT_SOURCE_DIR}/Objects/InstancedGeometry")
include_directories("${PROJECT_SOURCE_DIR}/Objects/BoundingVolume")
include_directories("${PROJECT_SOURCE_DIR}/Objects/Frustrum")

#Extensions Marching Cubes
include_directories("${PROJECT_SOURCE_DIR}/MarchingCubes")
include_directories("${PROJECT_SOURCE_DIR}/MarchingCubes/primitives")


#Vol Parser
include_directories("${PROJECT_SOURCE_DIR}/VolParser")


#Bit Space Header
include_directories("${PROJECT_SOURCE_DIR}/AsioCallbacks")

#Libraries
#OpenGL GLFW3
include_directories("${PROJECT_SOURCE_DIR}/../Dependencies/GLEW/include")
include_directories("${PROJECT_SOURCE_DIR}/../Dependencies/GLFW/include")

#Custom Callbacks Folder



#Library source code
target_link_libraries(${PROJECT_NAME} opengl32)
target_link_libraries(${PROJECT_NAME} "${PROJECT_SOURCE_DIR}/glfw3.dll")
target_link_libraries(${PROJECT_NAME} "${PROJECT_SOURCE_DIR}/glew32.dll")
set_property(TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set_property(TARGET ${PROJECT_NAME} PROPERTY INTERPROCEDURAL_OPTIMIZATION "true")
set_property(TARGET ${PROJECT_NAME} PROPERTY MSVC_INCREMENTAL_LINK "true")