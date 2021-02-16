cmake_minimum_required (VERSION 3.1.0)

include(${PROJECT_SOURCE_DIR}/utils.cmake)

project (static_baseutil)

set(ALL_FILES
	LogUtil.h
	LogUtil.cpp
	RandomUtil.h
	RandomUtil.cpp
	StringUtil.h
	StringUtil.cpp
	tinyxml2.h
	tinyxml2.cpp
	FileUtil.h
	FileUtil.cpp
	format.h
	format.cc
	
	utf8/utf8.h
	utf8/core.h
	utf8/checked.h
	utf8/unchecked.h
	
)

group_sources("${ALL_FILES}")

# Êä³öÂ·¾¶
set(LIBRARY_OUTPUT_PATH ${LIBRARY_PATH})
add_library(${PROJECT_NAME} ${ALL_FILES})

# Creates folder "external" and adds target project
# SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER lib)

