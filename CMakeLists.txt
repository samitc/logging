cmake_minimum_required(VERSION 3.1)
project(log)
set(COMMON_SOURCE
        Log/BasePattern.cpp
        Log/CharUtilities.cpp
        Log/Configuration.cpp
        Log/ConsoleWriter.cpp
        Log/DateTime.cpp
        Log/DateTimePattern.cpp
        Log/DynamicLogger.cpp
        Log/FileWriter.cpp
        Log/ILoggerData.cpp
        Log/ILoggerWriter.cpp
        Log/ILogStatement.cpp
        Log/IPreMessage.cpp
        Log/LoggerData.cpp
        Log/LoggerManager.cpp
        Log/LogData.cpp
        Log/LogFilter.cpp
        Log/Logger.cpp
        Log/LoggerName.cpp
        Log/LoggerNamePattern.cpp
        Log/LogLevel.cpp
        Log/LogLevelPattern.cpp
        Log/LogStatement.cpp
        Log/Msg.cpp
        Log/MsgPattern.cpp
        Log/NetworkWriter.cpp
        Log/OutputProcess.cpp
        Log/PreMessage.cpp
        Log/ProcessData.cpp
        Log/ProcessDataPattern.cpp
        Log/ProcessLog.cpp
        Log/ProcessName.cpp
        Log/ProcessNamePattern.cpp
        Log/ThreadId.cpp
        Log/ThreadIdPattern.cpp
        Log/XmlLogger.cpp
		Log/LString.cpp
        )
set(TEST_SOURCE
        LogTesting/PerformanceTest.cpp
        LogTesting/PerformanceTest.h
        LogTesting/LogTesting.cpp
        LogTesting/GeneralTest.h
        LogTesting/GeneralTest.cpp
        LogTesting/LogStatementTest.cpp
        LogTesting/LoggerTest.cpp
        LogTesting/LoggerListener.h
        LogTesting/LoggerListener.cpp
        LogTesting/DateTimeTest.cpp)
set(CMAKE_DEBUG_POSTFIX "d")
ADD_LIBRARY(log STATIC ${COMMON_SOURCE})
find_package(Threads)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules")
INCLUDE(AddCcons)
INCLUDE(AddGTest)
if (AddGTest_FOUND)
	add_executable(logTesting ${TEST_SOURCE})
	add_dependencies(logTesting log)
    add_dependencies(logTesting gtest)
	target_link_libraries(logTesting log)
    target_link_libraries(logTesting 
		debug ${GTEST_DEBUG_LIBRARIES}
		optimized ${GTEST_RELEASE_LIBRARIES})
	add_custom_command(TARGET logTesting PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/LogTesting/Log.config $<TARGET_FILE_DIR:logTesting>)
	add_custom_command(TARGET logTesting PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/LogTesting/TestOutput.py $<TARGET_FILE_DIR:logTesting>)
endif (AddGTest_FOUND)
if (MSYS OR MINGW)
    set(DISABLE_PTHREADS ON)
else ()
    set(DISABLE_PTHREADS OFF)
endif ()
if ("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
	add_definitions(-DWINDOWS)
elseif ("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
	add_definitions(-DLINUX)
	target_link_libraries (log rt)
endif()
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /GF")
endif()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
add_dependencies(log ccons)
target_link_libraries(log
            debug ${CCONS_DEBUG_DIRECTORY}/${CCONS_DEBUG_LIBRARIES}
            optimized ${CCONS_RELEASE_DIRECTORY}/${CCONS_RELEASE_LIBRARIES}
            )
TARGET_LINK_LIBRARIES(log ${CMAKE_THREAD_LIBS_INIT})
