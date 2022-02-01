cmake_minimum_required(VERSION 3.0.0)
project(scott-pilgrim-contra-os-bugs VERSION 0.1.0)

add_executable(scott-pilgrim-contra-os-bugs)

target_sources(
  scott-pilgrim-contra-os-bugs
  PRIVATE
  src/config/construct.c
  src/config/initialize.c
  src/pages/cutscenes/intro.c
  src/pages/cutscenes/mathewintro.c
  src/pages/cutscenes/mathewfinal.c
  src/pages/cutscenes/lucasleeintro.c
  src/pages/cutscenes/lucasleefinal.c
  src/pages/cutscenes/roxanneintro.c
  src/pages/cutscenes/roxannefinal.c
  src/pages/cutscenes/toddintro.c
  src/pages/cutscenes/toddfinal.c
  src/pages/cutscenes/final.c
  src/pages/cutscenes/tutorial.c
  src/pages/menu/menu.c
  src/pages/menu/settings.c
  src/pages/game/fase1/fase1.c
  src/pages/game/fase2/fase2.c
#   src/pages/game/fase3/fase3.c
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
