cmake_minimum_required(VERSION 3.19.6)
project(irukakun_othello CXX)

set(IRUKAKUN_OTHELLO_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include)
set(IRUKAKUN_OTHELLO_INCLUDE_PLATFORM_DIRS ${PROJECT_SOURCE_DIR}/include/platform)

# サブディレクトリを登録
add_subdirectory(src)
