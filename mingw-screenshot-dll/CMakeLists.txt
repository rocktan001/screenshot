cmake_minimum_required(VERSION 3.17)
project(Screencapture)

#set(CMAKE_CXX_STANDARD 14)

#编译类型
SET(CMAKE_BUILD_TYPE "Debug")

#包含目录
include_directories(include)
#set_source_files_properties(hello.rc PROPERTIES LANGUAGE RC)

#宏
#ADD_DEFINITIONS(-DUNICODE)
#ADD_DEFINITIONS(-D_UNICODE)

#Win32
#Release
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s -lcomctl32 -Wl,--subsystem,windows")

#Debug
if (MINGW)
#输出只有window 窗口，没有控制台
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}  -lcomctl32 -Wl,--subsystem,windows")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}  -lcomctl32 -Wl,--subsystem,console")
endif()

if (MSVC)
#输出带控制台窗口
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}  /SUBSYSTEM:console /ENTRY:WinMainCRTStartup")
endif()

#源代码文件
#set(SRC_LIST ${SRC_LIST} test/test_api.cpp)
#set(SRC_LIST ${SRC_LIST} test/test_win_api.cpp)
set(SRC_LIST ${SRC_LIST} interface/interface.cpp)
set(SRC_LIST ${SRC_LIST} src/Base.cpp src/ScreenCapture.cpp src/Types.cpp src/Utils.cpp)
set(SRC_LIST ${SRC_LIST} src/win/ScreenCaptureDuplicateOutputDirect3D11.cpp)
set(SRC_LIST ${SRC_LIST} src/win/ScreenCapturePointerDirect3D11.cpp)
set(SRC_LIST ${SRC_LIST} src/win/ScreenCaptureRendererDirect3D11.cpp)
set(SRC_LIST ${SRC_LIST} src/win/ScreenCaptureUtilsDirect3D11.cpp)


#生成文件
#add_executable(Screencapture ${SRC_LIST})
#生成文件
add_library( Screencapture SHARED   ${SRC_LIST} )







