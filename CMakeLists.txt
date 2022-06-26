cmake_minimum_required(VERSION 3.16)
project(Scrabble LANGUAGES CXX)

find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)

link_directories(${GTKMM_LIBRARY_DIRS})
include_directories(include ${GTKMM_INCLUDE_DIRS})

file(GLOB SOURCES "src/*.cpp" "src/ptrie/*.cpp" "src/umap/*.cpp src/umap/hmap.hpp")

add_executable(Scrabble)

target_compile_features(Scrabble PRIVATE cxx_std_20)

target_sources(Scrabble PRIVATE ${SOURCES})

target_include_directories(Scrabble PRIVATE ${GTKMM_INCLUDE_DIRS})

target_link_directories(Scrabble PRIVATE ${GTKMM_LIBRARY_DIRS})

target_link_libraries(Scrabble PRIVATE ${GTKMM_LIBRARIES})