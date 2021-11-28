# Install script for directory: D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/out/install/x64-Debug")
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

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlibassimp5.1.0-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/assimp-5.1" TYPE FILE FILES
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/out/build/x64-Debug/generated/assimpConfig.cmake"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/out/build/x64-Debug/generated/assimpConfigVersion.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlibassimp5.1.0-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/assimp-5.1/assimpTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/assimp-5.1/assimpTargets.cmake"
         "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/out/build/x64-Debug/CMakeFiles/Export/lib/cmake/assimp-5.1/assimpTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/assimp-5.1/assimpTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/assimp-5.1/assimpTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/assimp-5.1" TYPE FILE FILES "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/out/build/x64-Debug/CMakeFiles/Export/lib/cmake/assimp-5.1/assimpTargets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/assimp-5.1" TYPE FILE FILES "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/out/build/x64-Debug/CMakeFiles/Export/lib/cmake/assimp-5.1/assimpTargets-debug.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlibassimp5.1.0-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/out/build/x64-Debug/assimp.pc")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/out/build/x64-Debug/contrib/zlib/cmake_install.cmake")
  include("D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/out/build/x64-Debug/code/cmake_install.cmake")
  include("D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/out/build/x64-Debug/tools/assimp_cmd/cmake_install.cmake")
  include("D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/out/build/x64-Debug/test/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/out/build/x64-Debug/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
