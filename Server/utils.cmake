# this macro group source into there folders
macro(group_sources SOURCE_FILES)
    foreach(FILE ${SOURCE_FILES})
        get_filename_component(PARENT_DIR "${FILE}" PATH)

        # skip source and changes /'s to \\'s
        string(REGEX REPLACE "(\\./)?(source)/?" "" GROUP "${PARENT_DIR}")
        string(REPLACE "/" "\\" GROUP "${GROUP}")
        source_group("${GROUP}" FILES "${FILE}")
    endforeach()
endmacro()

# configure command line project properties
macro(config_command_line_tool PROJ_NAME OUTPUT_PATH SOURCE_FILES)

if (CMAKE_SYSTEM_NAME MATCHES "Windows")
    add_executable(${PROJ_NAME} ${SOURCE_FILES})
    target_link_libraries(${PROJ_NAME}
    static_jsoncpp
    static_zlib
    static_minizip
    static_baseutil
    )
elseif (CMAKE_SYSTEM_NAME MATCHES "Android")
    add_executable(${PROJ_NAME} ${SOURCE_FILES})
    target_link_libraries(${PROJ_NAME}
    static_jsoncpp
    z
    static_minizip
    static_baseutil
    )
endif ()

set_target_properties(${PROJ_NAME} PROPERTIES FOLDER tools)
set_target_properties(${PROJ_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_PATH})
set_target_properties(${PROJ_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${OUTPUT_PATH})
set_target_properties(${PROJ_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${OUTPUT_PATH})
set_target_properties(${PROJ_NAME} PROPERTIES OUTPUT_NAME_DEBUG ${PROJ_NAME}_D)
set_target_properties(${PROJ_NAME} PROPERTIES OUTPUT_NAME_RELEASE ${PROJ_NAME})
set_target_properties(${PROJ_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${OUTPUT_PATH})
endmacro()

# configure runtime project properties
macro(config_runtime PROJ_NAME OUTPUT_PATH FOLDER_NAME)
set_target_properties(${PROJ_NAME} PROPERTIES FOLDER ${FOLDER_NAME})
set_target_properties(${PROJ_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_PATH})
set_target_properties(${PROJ_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${OUTPUT_PATH})
set_target_properties(${PROJ_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${OUTPUT_PATH})
set_target_properties(${PROJ_NAME} PROPERTIES OUTPUT_NAME_DEBUG ${PROJ_NAME}_D)
set_target_properties(${PROJ_NAME} PROPERTIES OUTPUT_NAME_RELEASE ${PROJ_NAME})
set_target_properties(${PROJ_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${OUTPUT_PATH})
endmacro()
