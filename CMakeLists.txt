cmake_minimum_required(VERSION 3.0.0)
project(hardware_market_server VERSION 0.1.0)

include(CTest)
enable_testing()

file(GLOB files CONFIGURE_DEPENDS
     "*.h"
     "*.cpp"
     "hpp/*.hpp"
     "src/*.cpp"
     "hpp/json/*.hpp"
     "hpp/query/*.hpp"
     "src/query/*.cpp"
)

add_executable(hardware_market_server ${files})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
