cmake_minimum_required(VERSION 3.0.0)
project(Ändleite VERSION 0.1.0)

include(CTest)
enable_testing()

find_package(SDL2 REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-narrowing")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lSDL2")

include_directories(header ${SDL2_INCLUDE_DIRS})

add_executable(andleite
    source/main.cpp

    source/entity.cpp
    source/fvec2.cpp
    source/gamemanager.cpp
    source/input.cpp
    source/ivec2.cpp
    source/map.cpp
    source/maprenderer.cpp
    source/observer.cpp
    source/raycaster.cpp
    source/region.cpp
    source/sprite.cpp
    source/window.cpp

    header/entity.h
    header/fvec2.h
    header/gamemanager.h
    header/input.h
    header/ivec2.h
    header/map.h
    header/maprenderer.h
    header/observer.h
    header/raycaster.h
    header/region.h
    header/sprite.h
    header/window.h
)
target_link_libraries(andleite ${SDL2_LIBRARIES})


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
