add_subdirectory(allocator)
add_subdirectory(device)
add_subdirectory(frame)
add_subdirectory(ir)
add_subdirectory(ops)
list(
  APPEND
  SRCS
  ${ALLOCATOR_SRCS}
  ${DEVICE_SRCS}
  ${IR_SRCS}
  ${OPS_SRCS}
  ${FRAME_SRCS}
)
set(XYM_INFER_SRCS ${SRCS} PARENT_SCOPE)
