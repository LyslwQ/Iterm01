# Install script for directory: /home/ys/project/src9-9/muduo/muduo/base

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/home/ys/project/src9-9/build/release-install")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "release")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "0")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/ys/project/src9-9/build/release/lib/libmuduo_base.a")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/ys/project/src9-9/build/release/lib/libmuduo_base_cpp11.a")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/muduo/base" TYPE FILE FILES
    "/home/ys/project/src9-9/muduo/muduo/base/AsyncLogging.h"
    "/home/ys/project/src9-9/muduo/muduo/base/Atomic.h"
    "/home/ys/project/src9-9/muduo/muduo/base/BlockingQueue.h"
    "/home/ys/project/src9-9/muduo/muduo/base/BoundedBlockingQueue.h"
    "/home/ys/project/src9-9/muduo/muduo/base/Condition.h"
    "/home/ys/project/src9-9/muduo/muduo/base/copyable.h"
    "/home/ys/project/src9-9/muduo/muduo/base/CountDownLatch.h"
    "/home/ys/project/src9-9/muduo/muduo/base/CurrentThread.h"
    "/home/ys/project/src9-9/muduo/muduo/base/Date.h"
    "/home/ys/project/src9-9/muduo/muduo/base/Exception.h"
    "/home/ys/project/src9-9/muduo/muduo/base/FileUtil.h"
    "/home/ys/project/src9-9/muduo/muduo/base/GzipFile.h"
    "/home/ys/project/src9-9/muduo/muduo/base/LogFile.h"
    "/home/ys/project/src9-9/muduo/muduo/base/Logging.h"
    "/home/ys/project/src9-9/muduo/muduo/base/LogStream.h"
    "/home/ys/project/src9-9/muduo/muduo/base/Mutex.h"
    "/home/ys/project/src9-9/muduo/muduo/base/ProcessInfo.h"
    "/home/ys/project/src9-9/muduo/muduo/base/Singleton.h"
    "/home/ys/project/src9-9/muduo/muduo/base/StringPiece.h"
    "/home/ys/project/src9-9/muduo/muduo/base/Thread.h"
    "/home/ys/project/src9-9/muduo/muduo/base/ThreadLocal.h"
    "/home/ys/project/src9-9/muduo/muduo/base/ThreadLocalSingleton.h"
    "/home/ys/project/src9-9/muduo/muduo/base/ThreadPool.h"
    "/home/ys/project/src9-9/muduo/muduo/base/Timestamp.h"
    "/home/ys/project/src9-9/muduo/muduo/base/TimeZone.h"
    "/home/ys/project/src9-9/muduo/muduo/base/Types.h"
    "/home/ys/project/src9-9/muduo/muduo/base/WeakCallback.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/home/ys/project/src9-9/build/release/muduo/base/tests/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

