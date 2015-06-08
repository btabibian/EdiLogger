cmake_minimum_required(VERSION 2.6.4 FATAL_ERROR)

include("${CMAKE_CURRENT_SOURCE_DIR}/bootstrap.cmake")
use(NAOQI-PLUGINS-TOOLS)
include_directories(../common)
create_module( communication )

SET ( COMMUNICATION_SRCS
  src/communicationmain.cpp
  src/comclient.h
  src/comclient.cpp
  ../common/ALMessages.cpp

)

configure_src_module( communication ${COMMUNICATION_SRCS} )

use_lib( communication ALCOMMON ALMATH LIBCORE TOOLS ALVALUE)
