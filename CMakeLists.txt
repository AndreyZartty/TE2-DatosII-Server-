cmake_minimum_required(VERSION 3.14)
project(TE2_DatosII_Server_)

set(CMAKE_CXX_STANDARD 14)

add_executable(TE2_DatosII_Server_ main.cpp Node.cpp Node.h List.cpp List.h ArbolBinario.cpp ArbolBinario.h)

find_package(PkgConfig REQUIRED)
pkg_check_modules(JSON-C json-c)
link_libraries(${JSON-C_LIBRARIES})
target_link_libraries(TE2_DatosII_Server_ ${JSON-C_LIBRARIES})
