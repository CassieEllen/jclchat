add_executable(CreateDB
        src/CreateDB.cpp
        src/CreateDB.hpp
        )

target_link_libraries(CreateDB
  JclModel
  Poco::Util
  Poco::DataMySQL
        )
