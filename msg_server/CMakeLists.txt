cmake_minimum_required(VERSION 2.6)
PROJECT(msg_server)


if(NOT MUDUO_PATH)
  set(MUDUO_PATH "/home/ys/project/src9-9/db_proxy_server/muduo")
endif()

find_path(Muduo_LIBRARY_DIR libmuduo_base.a  "${MUDUO_PATH}")

set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} ${Muduo_LIBRARY_DIR})

message(STATUS ${Muduo_LIBRARY_DIR})

find_library(muduo_base muduo_base)
find_library(muduo_net muduo_net)
message(STATUS ${muduo_base})
message(STATUS ${muduo_net})

AUX_SOURCE_DIRECTORY(./ SRC_LIST)
SET(EXECUTABLE_OUTPUT_PATH  ./)

ADD_DEFINITIONS( -g -W -Wall -D_REENTRANT -D_FILE_OFFSET_BITS=64 -DAC_HAS_INFO
-DAC_HAS_WARNING -DAC_HAS_ERROR -DAC_HAS_CRITICAL -DTIXML_USE_STL
-DAC_HAS_DEBUG -DLINUX_DAEMON -std=c++11 -DENCRYPT)

INCLUDE_DIRECTORIES(./ )

LINK_DIRECTORIES(./ )
ADD_EXECUTABLE(msg_server ${SRC_LIST})

target_link_libraries(msg_server ${muduo_net})
target_link_libraries(msg_server ${muduo_base})
TARGET_LINK_LIBRARIES(msg_server pthread)
 
