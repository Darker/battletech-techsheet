cmake_minimum_required(VERSION 3.5)

project(battletech-techsheet VERSION 0.1 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB sources_core_lib "src/lib/**.cpp")
file(GLOB sources_cli "src/CLI/**.cpp")

add_library( techsheet_lib STATIC
    ${sources_core_lib}
)
target_include_directories( techsheet_lib PRIVATE include/techsheet INTERFACE include )

if(MSVC)
  target_compile_options(techsheet_lib PRIVATE /W4)
else()
  target_compile_options(techsheet_lib PRIVATE -Wall -Wextra -Wpedantic -Wno-unknown-pragmas)
endif()

add_executable( techsheet_cli ${sources_cli} )
target_include_directories( techsheet_cli INTERFACE include )
target_link_libraries(techsheet_cli PRIVATE techsheet_lib)
