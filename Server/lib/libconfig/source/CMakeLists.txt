cmake_minimum_required (VERSION 3.1.0)

include(${PROJECT_SOURCE_DIR}/utils.cmake)
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/automake)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/tabletool)

project (static_config)

set(ALL_FILES

tabletool/myconfig.h
tabletool/readtablefield.h
tabletool/readtablefile.cpp
tabletool/readtablefile.h
tabletool/singleton.h

automake/tableconfig.h
automake/tableconfig.cpp
automake/tablestruct.h


ConfigModule.cpp
ConfigModule.h
)

group_sources("${ALL_FILES}")

# Êä³öÂ·¾¶
set(LIBRARY_OUTPUT_PATH ${LIBRARY_PATH})
add_library(${PROJECT_NAME} ${ALL_FILES})

# Creates folder "external" and adds target project
# SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER lib)

