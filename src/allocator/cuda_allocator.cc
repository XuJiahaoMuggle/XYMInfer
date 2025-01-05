#include <src/allocator/cuda_allocator.h>
#include <cuda_runtime.h>

namespace xym_infer {

std::shared_ptr<CUDAAllocator> CUDAAllocator::instance_ = nullptr;
std::mutex CUDAAllocator::mtx_;

void* CUDAAllocator::allocate(size_t nb_bytes) const {
  if (!nb_bytes) { return nullptr; }
  void *ptr = nullptr;
  cudaMalloc(&ptr, nb_bytes);
  return ptr;
}

void CUDAAllocator::release(void* ptr) const {
  if (ptr) { cudaFree(ptr); }
}

}  // namespace xym_infer
