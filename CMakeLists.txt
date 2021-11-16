cmake_minimum_required(VERSION 3.0.0)
project(scott-pilgrim-contra-os-bugs VERSION 0.1.0)

add_executable(scott-pilgrim-contra-os-bugs)

target_sources(
  scott-pilgrim-contra-os-bugs
  PRIVATE
  src/pages/intro/intro.c
  src/pages/menu/menu.c
  src/pages/menu/settings.c
  src/pages/game/venceu.c
  src/pages/game/segunda.c
  src/pages/game/game.c
  src/main.c
)

target_include_directories(
  scott-pilgrim-contra-os-bugs
  PUBLIC
  src/
)

target_link_libraries(
  scott-pilgrim-contra-os-bugs
  PUBLIC
  -lmingw32
  -lliballegro_monolith-debug
)
