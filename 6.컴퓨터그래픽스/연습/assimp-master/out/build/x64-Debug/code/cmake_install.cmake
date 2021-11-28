# Install script for directory: D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code

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

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/out/build/x64-Debug/lib/assimp-vc142-mtd.lib")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/out/build/x64-Debug/bin/assimp-vc142-mtd.dll")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp" TYPE FILE FILES
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/anim.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/aabb.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/ai_assert.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/camera.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/color4.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/color4.inl"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/out/build/x64-Debug/code/../include/assimp/config.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/ColladaMetaData.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/commonMetaData.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/defs.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/cfileio.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/light.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/material.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/material.inl"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/matrix3x3.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/matrix3x3.inl"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/matrix4x4.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/matrix4x4.inl"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/mesh.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/pbrmaterial.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/GltfMaterial.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/postprocess.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/quaternion.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/quaternion.inl"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/scene.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/metadata.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/texture.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/types.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/vector2.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/vector2.inl"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/vector3.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/vector3.inl"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/version.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/cimport.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/importerdesc.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/Importer.hpp"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/DefaultLogger.hpp"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/ProgressHandler.hpp"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/IOStream.hpp"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/IOSystem.hpp"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/Logger.hpp"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/LogStream.hpp"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/NullLogger.hpp"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/cexport.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/Exporter.hpp"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/DefaultIOStream.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/DefaultIOSystem.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/ZipArchiveIOSystem.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/SceneCombiner.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/fast_atof.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/qnan.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/BaseImporter.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/Hash.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/MemoryIOWrapper.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/ParsingUtils.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/StreamReader.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/StreamWriter.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/StringComparison.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/StringUtils.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/SGSpatialSort.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/GenericProperty.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/SpatialSort.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/SkeletonMeshBuilder.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/SmallVector.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/SmoothingGroups.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/SmoothingGroups.inl"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/StandardShapes.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/RemoveComments.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/Subdivision.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/Vertex.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/LineSplitter.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/TinyFormatter.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/Profiler.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/LogAux.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/Bitmap.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/XMLTools.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/IOStreamBuffer.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/CreateAnimMesh.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/XmlParser.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/BlobIOSystem.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/MathFunctions.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/Exceptional.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/ByteSwapper.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp/Compiler" TYPE FILE FILES
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/Compiler/pushpack1.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/Compiler/poppack1.h"
    "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/code/../include/assimp/Compiler/pstdint.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/out/build/x64-Debug/code/assimp-vc142-mtd.pdb")
  endif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/out/build/x64-Debug/code/assimp-vc142-mt.pdb")
  endif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
endif()

