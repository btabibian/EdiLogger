cmake_minimum_required(VERSION 2.6.4 FATAL_ERROR)

include("${CMAKE_CURRENT_SOURCE_DIR}/bootstrap.cmake")
use(NAOQI-PLUGINS-TOOLS)

create_module( edilogger )
include_directories(../common)

SET ( LOGGER_SRCS
  src/loggermain.cpp
  src/logger.cpp
  ../common/TcpListener.cpp
  ../common/ALMessages.cpp
)

configure_src_module( edilogger ${LOGGER_SRCS} )

use_lib( edilogger ALCOMMON ALMATH LIBCORE TOOLS ALVALUE)
