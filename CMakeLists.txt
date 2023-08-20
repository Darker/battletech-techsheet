cmake_minimum_required(VERSION 3.5)

project(battletech-techsheet VERSION 0.1 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

cmake_policy(SET CMP0074 NEW)

if(NOT DEFINED EMSCRIPTEN)
  find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)
endif()

file(GLOB sources_core_lib "src/lib/**.cpp")
file(GLOB sources_cli "src/CLI/**.cpp")
file(GLOB sources_mtfparser "src/MtfParser/**.cpp")

function(set_compile_flags target_name)
  if(MSVC)
    target_compile_options(${target_name} PRIVATE /W4)
  elseif(EMSCRIPTEN)
    target_compile_options(${target_name} PRIVATE -Wall -Wextra -Wpedantic -Wno-unknown-pragmas -O3 -g )
    target_link_options(${target_name} PRIVATE --bind -lembind -sEXPORTED_RUNTIME_METHODS=ccall,cwrap -sEXPORT_ES6=1 -sMODULARIZE=1 -sEXPORT_NAME=techsheet)
  else()
    target_compile_options(${target_name} PRIVATE -Wall -Wextra -Wpedantic -Wno-unknown-pragmas -Og -g)
  endif()
endfunction()

add_library( techsheet_lib STATIC
    ${sources_core_lib}
)
target_include_directories( techsheet_lib PRIVATE include/techsheet INTERFACE include )

set_compile_flags(techsheet_lib)

add_library( mtfparser_lib STATIC
    ${sources_mtfparser}
)
target_include_directories( mtfparser_lib PRIVATE include/mtfparser INTERFACE include )
target_link_libraries(mtfparser_lib PRIVATE techsheet_lib)

set_compile_flags(mtfparser_lib)

add_executable( techsheet_cli ${sources_cli} )
target_include_directories( techsheet_cli INTERFACE include )
target_link_libraries(techsheet_cli PRIVATE techsheet_lib)
target_link_libraries(techsheet_cli PRIVATE mtfparser_lib)
set_compile_flags(techsheet_cli)


## --------------------------------------------------------------
## |                            TESTS                           |
## --------------------------------------------------------------

if(NOT DEFINED EMSCRIPTEN)

  file(GLOB sources_core_tests "test/unit/test*.cpp")

  add_executable(techsheet_lib_unit_tests
    ${sources_core_tests}
    test/unit/test_main.cpp
  )
  target_include_directories(techsheet_lib_unit_tests INTERFACE include PRIVATE ${Boost_INCLUDE_DIR})
  target_link_libraries(techsheet_lib_unit_tests PRIVATE
    techsheet_lib
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
  )
endif()
