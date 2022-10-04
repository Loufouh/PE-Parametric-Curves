cmake_minimum_required(VERSION 3.12)
project(Modelisation3D_TP3)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GSL REQUIRED)

list(APPEND EXTRA_DIRS ${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIRS} ${GSL_INCLUDE_DIRS})
list(APPEND EXTRA_LIBS ${OPENGL_LIBRARIES} ${GSL_LIBRARIES})

if(APPLE)
    list(APPEND EXTRA_LIBS "/Library/Developer/CommandLineTools/SDKs/MacOSX12.3.sdk/System/Library/Frameworks/GLUT.framework")
else()
    list(APPEND EXTRA_LIBS ${GLUT_LIBRARIES})
endif()

include_directories(
        ${EXTRA_DIRS}
)

add_executable(
        tp
        tp.cpp

        src/Camera.cpp src/Camera.h
        src/Trackball.cpp   src/Trackball.h
        src/Vec3.h

        Hermite/hermite.cpp Hermite/hermite.h
        Berstein/berstein.cpp Berstein/berstein.h
        Casteljau/casteljau.cpp Casteljau/casteljau.h
)
target_link_libraries(
        tp
        ${EXTRA_LIBS}
)
