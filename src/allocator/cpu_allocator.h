#pragma once
#include <memory>
#include <mutex>
#include <include/allocator/allocator.h>
#include <include/base/types.h>

namespace xym_infer {

class CPUAllocator final : public Allocator {
 public:
  static std::shared_ptr<CPUAllocator> getInstance() {
    if (!instance_) {
      std::unique_lock<std::mutex> lock(mtx_);
      if (!instance_) {
        instance_ = std::shared_ptr<CPUAllocator>(new CPUAllocator());
      }
    }
    return instance_;
  }

  void release(void* ptr) const override;
  
  void* allocate(size_t nb_bytes) const override;

 private:
  CPUAllocator() : Allocator(xym_infer::DeviceType::kDeviceCPU) {};
  CPUAllocator(const CPUAllocator&) = delete;
  CPUAllocator(CPUAllocator&&) = delete;

  CPUAllocator& operator=(CPUAllocator&&) = delete;
  CPUAllocator& operator=(const CPUAllocator&) = delete;

 private:
  static std::mutex mtx_;
  static std::shared_ptr<CPUAllocator> instance_;
};

}  // namespace xym_infer

