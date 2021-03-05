cmake_minimum_required(VERSION 3.19.6)
project(irukakun_othello CXX)

#add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
#add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
#add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/Zc:__cplusplus>")
#add_compile_options(/source-charset:utf-8)
#set(CMAKE_CXX_FLAGS "/source-charset:utf-8")
set(CMAKE_CXX_FLAGS "/EHsc /MT /utf-8")

# サブディレクトリを登録
add_subdirectory(src)
