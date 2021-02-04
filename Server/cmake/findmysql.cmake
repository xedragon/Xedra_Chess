#　指定库头文件所在路径
FIND_PATH(calc_INCLUDE_DIR mysql.h ${CMAKE_CURRENT_SOURCE_DIR}/include)

#　指定库文件所在路径
FIND_LIBRARY(calc_LIBRARY libmysql.lib ${CMAKE_CURRENT_SOURCE_DIR}/lib)

#　为了下游可以继续使用
set(calc_FOUND FALSE)
if (calc_INCLUDE_DIR AND calc_LIBRARY)
	set(calc_FOUND TRUE)
endif()