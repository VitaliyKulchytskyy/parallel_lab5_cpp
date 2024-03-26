cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    test_lab5
    VERSION 0.1.0
    DESCRIPTION "Short description"
    HOMEPAGE_URL "https://example.com/"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

add_library(
    test_lab5_lib OBJECT
    source/matrix_utils.cpp
    source/matrix.cpp
)

target_include_directories(
    test_lab5_lib ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>"
)

target_compile_features(test_lab5_lib PUBLIC cxx_std_11)

# ---- Packages ----

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

# ---- Declare executable ----

add_executable(test_lab5_exe source/main.cpp)
add_executable(test_lab5::exe ALIAS test_lab5_exe)

set_property(TARGET test_lab5_exe PROPERTY OUTPUT_NAME test_lab5)

target_compile_features(test_lab5_exe PRIVATE cxx_std_11)

target_link_libraries(test_lab5_exe PRIVATE test_lab5_lib)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT test_lab5_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of test_lab5"
  )
endif()

include(cmake/dev-mode.cmake)
