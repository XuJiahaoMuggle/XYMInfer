#pragma once
#include <memory>
#include <include/base/types.h>
#include <include/allocator/allocator.h>

namespace xym_infer {

class Buffer final : public std::enable_shared_from_this<Buffer> {
 public:
  explicit Buffer() = default;

  ~Buffer();

  explicit Buffer(size_t nb_bytes, 
                  std::shared_ptr<Allocator> allocator = nullptr,
                  void* ptr = nullptr);
  
  void allocate();

  void copyFrom(const Buffer& buffer, void* stream = nullptr, 
                bool sync = false) const;

  void copyFrom(const Buffer* buffer, void* stream = nullptr, 
                bool sync = false) const;

  void* data();

  const void* data() const;

  size_t nbBytes() const;

  std::shared_ptr<Allocator> allocator() const;

  DeviceType deviceType() const;

  std::shared_ptr<Buffer> getSharedFromThis();

  bool isOwner();

 private:
  size_t nb_bytes_ = 0;
  void* ptr_ = nullptr;
  bool is_owner = false;
  DeviceType device_type_ = DeviceType::kDeviceUnknown;
  std::shared_ptr<Allocator> allocator_;
};

}