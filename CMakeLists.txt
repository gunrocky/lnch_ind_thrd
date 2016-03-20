cmake_minimum_required(VERSION 3.5)

project(lnch_ind_thrd LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lnch_ind_thrd main.cpp)

include(GNUInstallDirs)
install(TARGETS lnch_ind_thrd
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ggdb3 -Wpedantic -Wall -Wextra -Wconversion -Wsign-conversion -Werror")
message(STATUS "C++ FLAGS: ${CMAKE_CXX_FLAGS}")
message(STATUS "C++ DEBUG FLAGS: ${CMAKE_CXX_FLAGS_DEBUG}")
