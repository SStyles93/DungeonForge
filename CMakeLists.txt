cmake_minimum_required(VERSION 3.31)

project("DungeonForge")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STRANDARD_REQUIRED ON) 

include(C:/vcpkg/scripts/buildsystems/vcpkg.cmake)

find_package(fmt CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
#find_package(GTest CONFIG REQUIRED)
#find_package(benchmark CONFIG REQUIRED)

#TRACY
option(ENABLE_PROFILER "Enable Tracy Profiling" OFF)
if(ENABLE_PROFILER)
add_subdirectory(external/tracy)
endif()

#PROGRAM FILES
file(GLOB_RECURSE SRC_FILES src/*.cpp include/*.hpp)
add_executable(DungeonForge ${SRC_FILES})
target_link_libraries(DungeonForge PUBLIC fmt::fmt)
target_link_libraries(DungeonForge PUBLIC imgui::imgui)
target_link_libraries(DungeonForge PUBLIC nlohmann_json::nlohmann_json)
target_link_libraries(DungeonForge PUBLIC SDL2::SDL2)

if(ENABLE_PROFILER)
target_link_libraries(DungeonForge PUBLIC TracyClient)
target_compile_definitions(DungeonForge PUBLIC TRACY_ENABLE)
endif()
target_include_directories(DungeonForge PUBLIC ${Stb_INCLUDE_DIR})
target_include_directories(DungeonForge PUBLIC include/)

#TESTS
#add_executable(Tests tests/tests.cpp src/Camera.cpp include/Camera.hpp src/DungeonForge.cpp include/DungeonForge.hpp src/Scene.cpp include/Scene.hpp)
#target_link_libraries(Tests PUBLIC GTest::gtest GTest::gtest_main)# GTest::gmock GTest::gmock_main)
#target_link_libraries(Tests PUBLIC imgui::imgui)
#target_link_libraries(Tests PUBLIC nlohmann_json::nlohmann_json)
#target_link_libraries(Tests PUBLIC SDL2::SDL2)
#target_include_directories(Tests PUBLIC include/)

#BENCHMARKS
#add_executable(Benchmarks benchmarks/benchmark.cpp src/Camera.cpp include/Camera.hpp src/DungeonForge.cpp include/DungeonForge.hpp src/Scene.cpp include/Scene.hpp)
#target_link_libraries(Benchmarks PUBLIC fmt::fmt)
#target_link_libraries(Benchmarks PUBLIC imgui::imgui)
#target_link_libraries(Benchmarks PUBLIC nlohmann_json::nlohmann_json)
#target_link_libraries(Benchmarks PUBLIC SDL2::SDL2)
#target_link_libraries(Benchmarks PRIVATE benchmark::benchmark benchmark::benchmark_main)
#target_include_directories(Benchmarks PUBLIC ${Stb_INCLUDE_DIR})
#target_include_directories(Benchmarks PUBLIC include/)

##ASSETS
##file(GLOB_RECURSE ASSET_FILES assets/*)
##foreach(ASSET_FILE ${ASSET_FILES})
##file(COPY ${ASSET_FILE} DESTINATION ../assets)
##endforeach()

if (MSVC)
    # MinimumSize/MaximumSpeed flag
    add_compile_options(/O2 /fp:fast)
else()
    # Optimize speed + add openMP
    add_compile_options(-O3 -ffast-math -fopenmp=libomp)
endif()