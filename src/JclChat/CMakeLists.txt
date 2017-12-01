
# Define an executable
add_executable(JclChat
    src/chat.cpp)

#  message("CMAKE_SOURCE_DIR=${CMAKE_SOURCE_DIR}")
#  message("CMAKE_CURRENT_SOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR}")
#  message("CMAKE_CURRENT_SOURCE_DIR/config=${CMAKE_CURRENT_SOURCE_DIR}/config")
  
add_custom_command(TARGET JclChat PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_CURRENT_SOURCE_DIR}/config $<TARGET_FILE_DIR:JclChat>)

# Define the libraries this project depends upon
target_link_libraries(JclChat
  Util
  JclModel
  JclServer
  #HtmlPages
  ${POCO_LIBRARIES}
  )
