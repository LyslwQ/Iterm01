cmake_minimum_required(VERSION 2.6)
PROJECT(db_proxy_server)


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
AUX_SOURCE_DIRECTORY(./model SRC_LIST)
AUX_SOURCE_DIRECTORY(./handler SRC_LIST)


#SET(LIBRARY_OUTPUT_PATH ./)
SET(EXECUTABLE_OUTPUT_PATH  ./)
if(APPLE)
    SET(PB_LIB_DIR ../base/pb/lib/mac)
elseif(UNIX)
    SET(PB_LIB_DIR ../base/pb/lib/linux)
endif()

SET(MYSQL_INCLUDE_DIR /usr/include/mysql)
SET(MYSQL_LIB /usr/lib64/mysql)

ADD_DEFINITIONS( -g -W -Wall -D_REENTRANT -D_FILE_OFFSET_BITS=64 -DAC_HAS_INFO
-DAC_HAS_WARNING -DAC_HAS_ERROR -DAC_HAS_CRITICAL -DTIXML_USE_STL
-DAC_HAS_DEBUG -DLINUX_DAEMON -std=c++11 -DENCRYPT)

INCLUDE_DIRECTORIES(./ ./model ./businiess ../base ../base/jsoncpp ../base/pb/protocol
../base/pb/ ${MYSQL_INCLUDE_DIR})

LINK_DIRECTORIES(./ ../base ${PB_LIB_DIR} ${MYSQL_LIB} ../base/slog/lib)

#ADD_XXXX必须在TARGET_LINK_LIBRARIES前面，否则会报错
#ADD_LIBRARY(${PROJECTNAME} SHARED/STATIC ${SRC_LIST})
ADD_EXECUTABLE(db_proxy_server ${SRC_LIST})

target_link_libraries(db_proxy_server ${muduo_net})
target_link_libraries(db_proxy_server ${muduo_base})
TARGET_LINK_LIBRARIES(db_proxy_server pthread base protobuf-lite mysqlclient_r hiredis curl slog crypto)
 
