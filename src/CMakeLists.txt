# ConsoleMod
add_library(ConsoleMod STATIC
            Console.cpp)

target_include_directories(ConsoleMod
                            PRIVATE ${IRUKAKUN_OTHELLO_INCLUDE_PLATFORM_DIRS})

# DisplayMod
add_library(DisplayMod STATIC
            Display.cpp)

target_link_libraries(DisplayMod
                        ConsoleMod)

target_include_directories(DisplayMod
                            PRIVATE ${IRUKAKUN_OTHELLO_INCLUDE_PLATFORM_DIRS}
                            PUBLIC ${IRUKAKUN_OTHELLO_INCLUDE_DIRS})

#OthelloGameMod
add_library(OthelloGameMod STATIC
            OthelloGame.cpp)

target_link_libraries(OthelloGameMod
                        DisplayMod)

target_include_directories(OthelloGameMod
                            PUBLIC ${IRUKAKUN_OTHELLO_INCLUDE_DIRS})

# IrukakunOthello
add_executable(IrukakunOthello
                Main.cpp)

target_link_libraries(IrukakunOthello
                        OthelloGameMod)

target_include_directories(IrukakunOthello
                            PRIVATE ${IRUKAKUN_OTHELLO_INCLUDE_DIRS})
