#pragma once
#include <stdint.h>
#include <stddef.h>
#include <memory>
#include <include/base/types.h>

namespace xym_infer {

class Allocator {
 public:
  explicit Allocator(DeviceType device_type)
      : device_type_(device_type) {}

  virtual DeviceType getDeviceType() {
    return device_type_;
  }

  virtual void release(void* ptr) const = 0;
  
  virtual void* allocate(size_t nb_bytes) const = 0;

  virtual void memcpy(void* dst, const void* src, size_t nb_bytes,
                      MemcpyType memcpy_type, 
                      void* stream = nullptr,
                      bool sync = false) const; 
 private:
  DeviceType device_type_ = DeviceType::kDeviceUnknown;
};

std::shared_ptr<Allocator> getAllocator(DeviceType device_type);

}  // namespace xym_infer
