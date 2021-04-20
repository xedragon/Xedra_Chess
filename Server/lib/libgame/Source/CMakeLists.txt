cmake_minimum_required (VERSION 3.1.0)

include(${PROJECT_SOURCE_DIR}/utils.cmake)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Module)

include_directories(${PROJECT_SOURCE_DIR}/lib/libmsg/source)
include_directories(${PROJECT_SOURCE_DIR}/lib/libconfig/source)
include_directories(${PROJECT_SOURCE_DIR}/lib/libmysql/source)
include_directories(${PROJECT_SOURCE_DIR}/lib/libprotobuf/source)


project (static_game)

set(ALL_FILES
	MsgMgr.h
	MsgMgr.cpp

	ClientUser.h
	ClientUser.cpp

	Moudle/NetMoudle.h
	Moudle/NetMoudle.cpp
	
	Game/Game.h
	Game/Game.cpp
	Game/GameManager.h
	Game/GameManager.cpp

	Game/Gobang/GobangManager.h
	Game/Gobang/GobangManager.cpp
	Game/Gobang/GobangGame.h
	Game/Gobang/GobangGame.cpp
	
	Game/Chess/ChessManager.h
	Game/Chess/ChessManager.cpp
	Game/Chess/ChessPiece.h
	Game/Chess/ChessPiece.cpp
	Game/Chess/ChessGame.h
	Game/Chess/ChessGame.cpp
)

group_sources("${ALL_FILES}")

# Êä³öÂ·¾¶
set(LIBRARY_OUTPUT_PATH ${LIBRARY_PATH})
add_library(${PROJECT_NAME} ${ALL_FILES})

# Creates folder "external" and adds target project
# SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER lib)

