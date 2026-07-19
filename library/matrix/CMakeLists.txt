add_library(matrix_lib STATIC
    include/parser.h
    parser.cpp
)

target_link_libraries(matrix_lib INTERFACE compiler_flags)

target_include_directories(matrix_lib INTERFACE
   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
   $<INSTALL_INTERFACE:include>
)
