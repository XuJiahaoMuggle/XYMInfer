#pragma once
#include <mutex>
#include <memory>
#include <include/allocator/allocator.h>
#include <include/base/types.h>

namespace xym_infer {

class CUDAAllocator final : public Allocator {
 public:
  static std::shared_ptr<CUDAAllocator> getInstance() {
    if (!instance_) {
      std::unique_lock<std::mutex> lock(mtx_);
      if (!instance_) {
        instance_ = std::shared_ptr<CUDAAllocator>(new CUDAAllocator());
      }
    }
    return instance_;
  }

  void release(void* ptr) const override;
  
  void* allocate(size_t nb_bytes) const override;

 private:
  CUDAAllocator() : Allocator(xym_infer::DeviceType::kDeviceCUDA) {}
  CUDAAllocator(const CUDAAllocator&) = delete;
  CUDAAllocator(CUDAAllocator&&) = delete;

  CUDAAllocator& operator=(CUDAAllocator&&) = delete;
  CUDAAllocator& operator=(const CUDAAllocator&) = delete;

 private:
  static std::mutex mtx_;
  static std::shared_ptr<CUDAAllocator> instance_;
  
};

}  // namespace xym_infer