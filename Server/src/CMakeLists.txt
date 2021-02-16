# CMakeList.txt: Design Mode 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

include(${PROJECT_SOURCE_DIR}/utils.cmake)

# 全局配置
option(USE_MYMATH "Use provided math implementation" ON)

configure_file(
	"${PROJECT_SOURCE_DIR}/config.h.in"
	"${PROJECT_SOURCE_DIR}/config.h"
)


# 输出路径
set(EXECUTABLE_OUTPUT_PATH ${EXECUTUBLE_PATH})

# 包含源码路径
include_directories(${PROJECT_SOURCE_DIR}/lib)
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/lib/libmsg/source)
include_directories(${PROJECT_SOURCE_DIR}/lib/libprotobuf/source)
include_directories(${PROJECT_SOURCE_DIR}/lib/libbaseutil/source)

link_directories(${LIBRARY_PATH})
link_directories(${LIBRARY_PATH}/libmysql/source/lib)
link_directories(${LIBRARY_PATH}/libconfig/source/lib)

# 添加源码
set(ALl_FILES

main.h
main.cpp

Facade.h
Facade.cpp

MsgMgr.h
MsgMgr.cpp

ClientUser.h
ClientUser.cpp

Moudle/Moudle.h
Moudle/Moudle.cpp

Moudle/NetMoudle.h
Moudle/NetMoudle.cpp

)
# 源码分组
group_sources("${ALL_FILES}")
# 将源代码添加到此项目的可执行文件。
add_executable ("Chess" ${ALl_FILES})
# 静态链接库
target_link_libraries(${PROJECT_NAME} static_jsoncpp)
target_link_libraries(${PROJECT_NAME} static_protobuf)
target_link_libraries(${PROJECT_NAME} static_mysql)
target_link_libraries(${PROJECT_NAME} static_config)
target_link_libraries(${PROJECT_NAME} static_msg)
target_link_libraries(${PROJECT_NAME} static_baseutil)
target_link_libraries(${PROJECT_NAME} ws2_32)

# TODO: 如有需要，请添加测试并安装目标。
