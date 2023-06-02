cmake_minimum_required (VERSION 3.11)

# --- Fetch FTXUI --------------------------------------------------------------
include(FetchContent)

set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG v3.0.0
)

FetchContent_GetProperties(ftxui)
if(NOT ftxui_POPULATED)
  FetchContent_Populate(ftxui)
  add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

# ------------------------------------------------------------------------------

find_package(SqliteOrm REQUIRED)

project(typing-game
  LANGUAGES CXX
  VERSION 1.0.0
)


set(CLIENT_SRC
  src/client.cpp

  src/utils/md5.cpp
  src/utils/string.cpp

  src/models/user.cpp
  src/models/word.cpp

  src/view/player.cpp
  src/view/char.cpp
  src/view/login.cpp
  src/view/rank.cpp
  src/view/maker.cpp

  src/view/ui.cpp

  src/rpc/rpc.cpp
  src/rpc/client.cpp
  src/rpc/p2p.cpp
)

set(SERVER_SRC
  src/server.cpp
  src/db.cpp

  src/utils/md5.cpp
  src/utils/string.cpp

  src/models/user.cpp
  src/models/word.cpp

  src/rpc/rpc.cpp
  src/rpc/server.cpp
)

add_executable(typing-game-client ${CLIENT_SRC})
target_include_directories(typing-game-client PRIVATE src)

target_link_libraries(typing-game-client
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component

  ws2_32
)

add_executable(typing-game-server ${SERVER_SRC})
target_include_directories(typing-game-server PRIVATE src)

target_link_libraries(typing-game-server
  sqlite_orm::sqlite_orm

  ws2_32
)