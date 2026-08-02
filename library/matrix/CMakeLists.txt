add_library(matrix_lib INTERFACE
    include/matrix.hpp
)

target_link_libraries(matrix_lib INTERFACE compiler_flags)

target_include_directories(matrix_lib INTERFACE
   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
   $<INSTALL_INTERFACE:include>
)
