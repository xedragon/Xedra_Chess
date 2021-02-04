cmake_minimum_required (VERSION 3.1.0)

include(${PROJECT_SOURCE_DIR}/utils.cmake)

project (static_jsoncpp)

set(ALL_FILES
json/config.h
json/features.h
json/forwards.h
json/json_batchallocator.h
json/json_internalarray.inl
json/json_internalmap.inl
json/json_lib.h
json/json_reader.cpp
json/json_tool.h
json/json_value.cpp
json/json_valueiterator.inl
json/json_writer.cpp
json/reader.h
json/value.h
json/writer.h
)

group_sources("${ALL_FILES}")

# Êä³öÂ·¾¶
set(LIBRARY_OUTPUT_PATH ${LIBRARY_PATH})
add_library(${PROJECT_NAME} ${ALL_FILES})

# Creates folder "external" and adds target project
# SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER lib)

