cmake_minimum_required(VERSION 3.16)
project(xym_infer LANGUAGES C CXX CUDA)
set(CMAKE_CUDA_ARCHITECTURES 89)

# build our xym shared library
add_subdirectory(src)
message(STATUS ${XYM_INFER_SRCS})
add_library(xym_infer SHARED ${XYM_INFER_SRCS})
set(CUDA_DIR /usr/local/cuda)

target_include_directories(
  xym_infer PRIVATE 
  ${CUDA_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_directories(
  xym_infer PRIVATE
  ${CUDA_DIR}/lib64
)

target_link_libraries(
  xym_infer PRIVATE
  cuda
  cudart
)

# build samples
add_subdirectory(samples)
foreach(SAMPLE_SRC ${SAMPLE_SRCS})
  get_filename_component(SAMPLE_NAME ${SAMPLE_SRC} NAME_WE)
  add_executable(${SAMPLE_NAME} ${SAMPLE_SRC})
  target_include_directories(
    ${SAMPLE_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
  )
  target_link_libraries(
    ${SAMPLE_NAME} PRIVATE
    xym_infer
  )
endforeach()

# build tests
add_subdirectory(tests)

find_package(GTest CONFIG REQUIRED)
add_executable(xym_infer_ut ${TEST_SRCS})
target_link_libraries(
  xym_infer_ut PRIVATE 
  gtest
)
