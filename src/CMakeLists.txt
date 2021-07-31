# ConsoleMod
add_library(ConsoleMod STATIC
            Console.cpp)

target_include_directories(ConsoleMod
                            PRIVATE ${IRUKAKUN_OTHELLO_INCLUDE_PLATFORM_DIRS})

# DisplayMod
add_library(DisplayMod STATIC
            Display.cpp)

target_link_libraries(DisplayMod
                        PRIVATE ConsoleMod)

target_include_directories(DisplayMod
                            PRIVATE ${IRUKAKUN_OTHELLO_INCLUDE_PLATFORM_DIRS}
                            PUBLIC ${IRUKAKUN_OTHELLO_INCLUDE_DIRS})

#OthelloGameMod
add_library(OthelloGameMod STATIC
            OthelloGame.cpp)

target_link_libraries(OthelloGameMod
                        PRIVATE DisplayMod)

target_include_directories(OthelloGameMod
                            PRIVATE ${IRUKAKUN_OTHELLO_INCLUDE_PLATFORM_DIRS}
                            PUBLIC ${IRUKAKUN_OTHELLO_INCLUDE_DIRS})

# IrukakunOthello
add_executable(IrukakunOthello
                Main.cpp)

target_link_libraries(IrukakunOthello
                        PRIVATE OthelloGameMod)

target_include_directories(IrukakunOthello
                            PRIVATE ${IRUKAKUN_OTHELLO_INCLUDE_DIRS})

# compile options
# Releaseビルド時 cmake -DCMAKE_BUILD_TYPE=Release ..
# テストビルド時 cmake -DCMAKE_BUILD_TYPE=Debug ..
set(COMPILE_OPTIONS /EHa /MD /utf-8)
target_compile_options(ConsoleMod PUBLIC ${COMPILE_OPTIONS})
target_compile_options(DisplayMod PUBLIC ${COMPILE_OPTIONS})
target_compile_options(OthelloGameMod PUBLIC ${COMPILE_OPTIONS})
target_compile_options(IrukakunOthello PUBLIC ${COMPILE_OPTIONS})

# compile definitions
if(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    message("---------------------- Release Build")
else()
    message("---------------------- Not Release Build")
    set(COMPILE_DEFINITIONS NDEBUG)
endif()

target_compile_definitions(ConsoleMod PUBLIC ${COMPILE_DEFINITIONS})
target_compile_definitions(DisplayMod PUBLIC ${COMPILE_DEFINITIONS})
target_compile_definitions(OthelloGameMod PUBLIC ${COMPILE_DEFINITIONS})
target_compile_definitions(IrukakunOthello PUBLIC ${COMPILE_DEFINITIONS})
