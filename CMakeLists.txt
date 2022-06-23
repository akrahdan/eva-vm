cmake_minimum_required(VERSION 3.1)

project(CompilerDesign, CXX)


option(ENABLE_CPPCHECK "Enable static analysis with cppcheck" OFF)
option(ENABLE_CLANG_TIDY "Enable static analysis with clang-tidy" OFF)

if(ENABLE_CLANG_TIDY)
  find_program(CLANGTIDY clang-tidy-13)
  if(CLANGTIDY)
    set(CMAKE_C_CLANG_TIDY ${CLANGTIDY})
    set(CMAKE_CXX_CLANG_TIDY ${CLANGTIDY})
  else()
    message(SEND_ERROR "clang-tidy could not be located.")
  endif()
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(vm)
add_subdirectory(bytecode)