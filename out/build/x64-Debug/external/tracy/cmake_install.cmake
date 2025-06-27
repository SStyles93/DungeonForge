# Install script for directory: C:/00_Dev/DungeonForge/external/tracy

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/00_Dev/DungeonForge/out/install/x64-Debug")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "lib" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/00_Dev/DungeonForge/out/build/x64-Debug/external/tracy/TracyClient.lib")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/tracy/tracy" TYPE FILE FILES
    "C:/00_Dev/DungeonForge/external/tracy/public/tracy/TracyC.h"
    "C:/00_Dev/DungeonForge/external/tracy/public/tracy/Tracy.hpp"
    "C:/00_Dev/DungeonForge/external/tracy/public/tracy/TracyD3D11.hpp"
    "C:/00_Dev/DungeonForge/external/tracy/public/tracy/TracyD3D12.hpp"
    "C:/00_Dev/DungeonForge/external/tracy/public/tracy/TracyLua.hpp"
    "C:/00_Dev/DungeonForge/external/tracy/public/tracy/TracyOpenCL.hpp"
    "C:/00_Dev/DungeonForge/external/tracy/public/tracy/TracyOpenGL.hpp"
    "C:/00_Dev/DungeonForge/external/tracy/public/tracy/TracyVulkan.hpp"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/tracy/client" TYPE FILE FILES
    "C:/00_Dev/DungeonForge/external/tracy/public/client/tracy_concurrentqueue.h"
    "C:/00_Dev/DungeonForge/external/tracy/public/client/tracy_rpmalloc.hpp"
    "C:/00_Dev/DungeonForge/external/tracy/public/client/tracy_SPSCQueue.h"
    "C:/00_Dev/DungeonForge/external/tracy/public/client/TracyKCore.hpp"
    "C:/00_Dev/DungeonForge/external/tracy/public/client/TracyArmCpuTable.hpp"
    "C:/00_Dev/DungeonForge/external/tracy/public/client/TracyCallstack.h"
    "C:/00_Dev/DungeonForge/external/tracy/public/client/TracyCallstack.hpp"
    "C:/00_Dev/DungeonForge/external/tracy/public/client/TracyCpuid.hpp"
    "C:/00_Dev/DungeonForge/external/tracy/public/client/TracyDebug.hpp"
    "C:/00_Dev/DungeonForge/external/tracy/public/client/TracyDxt1.hpp"
    "C:/00_Dev/DungeonForge/external/tracy/public/client/TracyFastVector.hpp"
    "C:/00_Dev/DungeonForge/external/tracy/public/client/TracyLock.hpp"
    "C:/00_Dev/DungeonForge/external/tracy/public/client/TracyProfiler.hpp"
    "C:/00_Dev/DungeonForge/external/tracy/public/client/TracyRingBuffer.hpp"
    "C:/00_Dev/DungeonForge/external/tracy/public/client/TracyScoped.hpp"
    "C:/00_Dev/DungeonForge/external/tracy/public/client/TracyStringHelpers.hpp"
    "C:/00_Dev/DungeonForge/external/tracy/public/client/TracySysPower.hpp"
    "C:/00_Dev/DungeonForge/external/tracy/public/client/TracySysTime.hpp"
    "C:/00_Dev/DungeonForge/external/tracy/public/client/TracySysTrace.hpp"
    "C:/00_Dev/DungeonForge/external/tracy/public/client/TracyThread.hpp"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/tracy/common" TYPE FILE FILES
    "C:/00_Dev/DungeonForge/external/tracy/public/common/tracy_lz4.hpp"
    "C:/00_Dev/DungeonForge/external/tracy/public/common/tracy_lz4hc.hpp"
    "C:/00_Dev/DungeonForge/external/tracy/public/common/TracyAlign.hpp"
    "C:/00_Dev/DungeonForge/external/tracy/public/common/TracyAlloc.hpp"
    "C:/00_Dev/DungeonForge/external/tracy/public/common/TracyApi.h"
    "C:/00_Dev/DungeonForge/external/tracy/public/common/TracyColor.hpp"
    "C:/00_Dev/DungeonForge/external/tracy/public/common/TracyForceInline.hpp"
    "C:/00_Dev/DungeonForge/external/tracy/public/common/TracyMutex.hpp"
    "C:/00_Dev/DungeonForge/external/tracy/public/common/TracyProtocol.hpp"
    "C:/00_Dev/DungeonForge/external/tracy/public/common/TracyQueue.hpp"
    "C:/00_Dev/DungeonForge/external/tracy/public/common/TracySocket.hpp"
    "C:/00_Dev/DungeonForge/external/tracy/public/common/TracyStackFrames.hpp"
    "C:/00_Dev/DungeonForge/external/tracy/public/common/TracySystem.hpp"
    "C:/00_Dev/DungeonForge/external/tracy/public/common/TracyUwp.hpp"
    "C:/00_Dev/DungeonForge/external/tracy/public/common/TracyYield.hpp"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/Tracy/TracyTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/Tracy/TracyTargets.cmake"
         "C:/00_Dev/DungeonForge/out/build/x64-Debug/external/tracy/CMakeFiles/Export/b11871b887d9a65b4500cc2803d48638/TracyTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/Tracy/TracyTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/Tracy/TracyTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Tracy" TYPE FILE FILES "C:/00_Dev/DungeonForge/out/build/x64-Debug/external/tracy/CMakeFiles/Export/b11871b887d9a65b4500cc2803d48638/TracyTargets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Tracy" TYPE FILE FILES "C:/00_Dev/DungeonForge/out/build/x64-Debug/external/tracy/CMakeFiles/Export/b11871b887d9a65b4500cc2803d48638/TracyTargets-debug.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Tracy" TYPE FILE FILES "C:/00_Dev/DungeonForge/out/build/x64-Debug/external/tracy/TracyConfig.cmake")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "C:/00_Dev/DungeonForge/out/build/x64-Debug/external/tracy/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
