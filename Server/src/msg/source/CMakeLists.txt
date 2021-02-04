cmake_minimum_required (VERSION 3.1.0)

include(../../../utils.cmake)

project (static_msg)

include_directories(${PROJECT_SOURCE_DIR}/../../../external/libprotobuf/source)


set(ALL_FILES

)

group_sources("${ALL_FILES}")

add_library(${PROJECT_NAME} ${ALL_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER sandbox)
