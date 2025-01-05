#include <stdlib.h>
#include <src/allocator/cpu_allocator.h>

namespace xym_infer {

std::shared_ptr<CPUAllocator> CPUAllocator::instance_ = nullptr;
std::mutex CPUAllocator::mtx_;

void* CPUAllocator::allocate(size_t nb_bytes) const {
  return nb_bytes ? malloc(nb_bytes) : nullptr;
}

void CPUAllocator::release(void* ptr) const {
  if (ptr) { free(ptr); }
}

}  // namespace xym_infer