cmake_minimum_required(VERSION 3.1.0)

include(../../../utils.cmake)

project (static_mysql)

set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(LINK_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)

# 添加lib_mysql
set(LIBRARY_OUTPUT_PATH ${LIBRARY_PATH})
 add_library(libmysql SHARED IMPORTED)
 set_property(TARGET libmysql PROPERTY IMPORTED_LOCATION ${LINK_DIR}/libmysql.dll)
 set_property(TARGET libmysql PROPERTY IMPORTED_IMPLIB ${LINK_DIR}/libmysql.lib) # 多了lib信息

# 添加static_mysql
include_directories(${INC_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
link_directories(${LINK_DIR})

aux_source_directory(. ALL_FILES)
add_library(${PROJECT_NAME} ${ALL_FILES})

 # 链接 libmysql
 target_include_directories(${PROJECT_NAME} PUBLIC ${INC_DIR})
 target_link_libraries(${PROJECT_NAME} PUBLIC libmysql)

# 拷贝.dll
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
