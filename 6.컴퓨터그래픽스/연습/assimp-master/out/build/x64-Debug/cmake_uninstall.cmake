IF(NOT EXISTS "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/out/build/x64-Debug/install_manifest.txt")
  MESSAGE(FATAL_ERROR "Cannot find install manifest: \"D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/out/build/x64-Debug/install_manifest.txt\"")
ENDIF(NOT EXISTS "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/out/build/x64-Debug/install_manifest.txt")

FILE(READ "D:/★과제물★/3학년 2학기/School_3.2/6.컴퓨터그래픽스/연습/assimp-master/out/build/x64-Debug/install_manifest.txt" files)
STRING(REGEX REPLACE "\n" ";" files "${files}")
FOREACH(file ${files})
  MESSAGE(STATUS "Uninstalling \"$ENV{DESTDIR}${file}\"")
  EXEC_PROGRAM(
    "C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/cmake.exe" ARGS "-E remove \"$ENV{DESTDIR}${file}\""
    OUTPUT_VARIABLE rm_out
    RETURN_VALUE rm_retval
    )
  IF(NOT "${rm_retval}" STREQUAL 0)
    MESSAGE(FATAL_ERROR "Problem when removing \"$ENV{DESTDIR}${file}\"")
  ENDIF(NOT "${rm_retval}" STREQUAL 0)
ENDFOREACH(file)
