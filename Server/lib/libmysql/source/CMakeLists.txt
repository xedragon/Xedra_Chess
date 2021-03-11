cmake_minimum_required(VERSION 3.1.0)

include(${PROJECT_SOURCE_DIR}/utils.cmake)


set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(LINK_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)

# Ìí¼Ólib_mysql
set(LIBRARY_OUTPUT_PATH ${LIBRARY_PATH})
add_library(libmysql SHARED IMPORTED)
set_property(TARGET libmysql PROPERTY IMPORTED_LOCATION ${LINK_DIR}/libmysql.dll)
set_property(TARGET libmysql PROPERTY IMPORTED_IMPLIB ${LINK_DIR}/libmysql.lib)

# Ìí¼Óstatic_mysql
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${INC_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

project (static_mysql)

set(ALL_FILES
	MySqlServer.h
	MySqlServer.cpp
	
	IQueryResult.h
	MySqlQueryResult.h
)

group_sources("${ALL_FILES}")
add_library(${PROJECT_NAME} ${ALL_FILES})

# Á´½Ó libmysql
link_directories(${LINK_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${INC_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC libmysql)

# ¿½±´.dll
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/"
    $<TARGET_FILE_DIR:${PROJECT_NAME}>)



# FIND_LIBRARY(MY_LIB libmysql.dll ${CMAKE_CURRENT_SOURCE_DIR}/lib)
# target_link_libraries(${PROJECT_NAME} ${MY_LIB})
# FIND_LIBRARY(MY_LIB libmysql.lib ${CMAKE_CURRENT_SOURCE_DIR}/lib)
# target_link_libraries(${PROJECT_NAME} ${MY_LIB})

# Creates folder "external" and adds target project
# SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER lib)
