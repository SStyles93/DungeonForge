cmake_minimum_required(VERSION 3.31)


project("DungeonForge")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STRANDARD_REQUIRED ON) 

set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")

find_package(fmt CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(ImGui-SFML CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(SFML COMPONENTS graphics CONFIG REQUIRED)
#find_package(GTest CONFIG REQUIRED)
#find_package(benchmark CONFIG REQUIRED)


##TRACY
#option(ENABLE_PROFILER "Enable Tracy Profiling" OFF)
#if(ENABLE_PROFILER)
#add_subdirectory(external/tracy)
#endif()

#PROGRAM FILES
file(GLOB_RECURSE SRC_FILES src/*.cpp include/*.hpp)
add_executable(TestApp ${SRC_FILES})
target_include_directories(TestApp PUBLIC include/)
target_link_libraries(TestApp PUBLIC fmt::fmt)
target_link_libraries(TestApp PUBLIC nlohmann_json::nlohmann_json)
target_link_libraries(TestApp PUBLIC ImGui-SFML::ImGui-SFML)
target_link_libraries(TestApp PUBLIC sfml-system sfml-network sfml-graphics sfml-window)

##DEBUG
#if(ENABLE_PROFILER)
#target_link_libraries(TestApp PUBLIC TracyClient)
#target_compile_definitions(TestApp PUBLIC TRACY_ENABLE)
#endif()
#target_include_directories(TestApp PUBLIC ${Stb_INCLUDE_DIR})
#target_include_directories(TestApp PUBLIC include/)

#TESTS
#add_executable(Tests tests/tests.cpp src/Camera.cpp include/Camera.hpp src/DungeonForge.cpp include/DungeonForge.hpp src/Scene.cpp include/Scene.hpp)
#target_link_libraries(Tests PUBLIC GTest::gtest GTest::gtest_main)# GTest::gmock GTest::gmock_main)
#target_link_libraries(Tests PUBLIC imgui::imgui)
#target_link_libraries(Tests PUBLIC nlohmann_json::nlohmann_json)
##target_link_libraries(Test PUBLIC imgui::imgui)
#target_link_libraries(Tests PUBLIC SDL3::SDL3)
#target_include_directories(Tests PUBLIC include/)

#BENCHMARKS
#add_executable(Benchmarks benchmarks/benchmark.cpp src/Camera.cpp include/Camera.hpp src/DungeonForge.cpp include/DungeonForge.hpp src/Scene.cpp include/Scene.hpp)
#target_link_libraries(Benchmarks PUBLIC fmt::fmt)
#target_link_libraries(Benchmarks PUBLIC imgui::imgui)
#target_link_libraries(Benchmarks PUBLIC nlohmann_json::nlohmann_json)
#target_link_libraries(Benchmarks PUBLIC SDL3::SDL3)
#target_link_libraries(Benchmarks PRIVATE benchmark::benchmark benchmark::benchmark_main)
#target_include_directories(Benchmarks PUBLIC ${Stb_INCLUDE_DIR})
#target_include_directories(Benchmarks PUBLIC include/)

##ASSETS
##file(GLOB_RECURSE ASSET_FILES assets/*)
##foreach(ASSET_FILE ${ASSET_FILES})
##file(COPY ${ASSET_FILE} DESTINATION ../assets)
##endforeach()

#if (MSVC)
#    # MinimumSize/MaximumSpeed flag
#    add_compile_options(/O2 /fp:fast)
#else()
#    # Optimize speed + add openMP
#    add_compile_options(-O3 -ffast-math -fopenmp=libomp)
#endif()