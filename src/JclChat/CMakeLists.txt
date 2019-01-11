
add_executable(JclChat
        src/chat.cpp)

add_custom_command(TARGET JclChat PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/config $<TARGET_FILE_DIR:JclChat>
        )

add_custom_command(TARGET JclChat PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/scripts $<TARGET_FILE_DIR:JclChat>/scripts
        )

add_custom_command(TARGET JclChat PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/css $<TARGET_FILE_DIR:JclChat>/css
        )

target_link_libraries(JclChat
        JclServer
        Poco::Foundation
        Poco::Util
        Poco::Net
        Poco::DataMySQL
        )
