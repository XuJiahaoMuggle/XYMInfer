aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/cuda CUDA_OPS_SRCS)
# aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/avx AVX_OPS_SRCS)
# aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/cann CANN_OPS_SRCS)

set(OPS_SRCS ${CUDA_OPS_SRCS} PARENT_SCOPE)

