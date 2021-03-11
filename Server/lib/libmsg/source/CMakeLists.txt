cmake_minimum_required (VERSION 3.1.0)

include(../../../utils.cmake)

project (static_msg)

include_directories(${CMAKE_SOURCE_DIR}/lib/libprotobuf/source)


set(ALL_FILES
	msg/Msg.pb.h
	msg/Msg.pb.cc
	msg/MsgChat.pb.h
	msg/MsgChat.pb.cc
)

group_sources("${ALL_FILES}")

add_library(${PROJECT_NAME} ${ALL_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER lib)
