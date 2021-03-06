add_library(DisplayMod STATIC
            Display.cpp)

target_include_directories(DisplayMod PRIVATE
                            ${IRUKAKUN_OTHELLO_INCLUDE_DIRS})

add_executable(IrukakunOthello
                Main.cpp)

target_link_libraries(IrukakunOthello
                        DisplayMod)

target_include_directories(IrukakunOthello
                            PRIVATE ${IRUKAKUN_OTHELLO_INCLUDE_DIRS})
