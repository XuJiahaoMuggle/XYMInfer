#include <assert.h>
#include <memory>
#include <src/tensor/buffer.h>

namespace xym_infer {

Buffer::Buffer(size_t nb_bytes, 
               std::shared_ptr<Allocator> allocator,
               void* ptr) 
    : nb_bytes_(nb_bytes),
      allocator_(allocator),
      ptr_(ptr),
      is_owner(false) {
  if (!ptr_ && allocator_) {
    device_type_ = allocator_->getDeviceType();
    is_owner = true;
    ptr_ = allocator_->allocate(nb_bytes_);
  }
}

Buffer::~Buffer() {
  if (is_owner && allocator_ && ptr_) {
    allocator_->release(ptr_);
    ptr_ = nullptr;
  }
}

void* Buffer::data() { return ptr_; }

const void* Buffer::data() const { return ptr_; }

size_t Buffer::nbBytes() const { return nb_bytes_; }

void Buffer::allocate() {
  if (!is_owner && allocator_ && nb_bytes_ != 0) {
    is_owner = true;
    ptr_ = allocator_->allocate(nb_bytes_);
  }
}

std::shared_ptr<Allocator> Buffer::allocator() const {
  return allocator_;
}

void Buffer::copyFrom(const Buffer& buffer, void* stream, bool sync) const {
  assert(allocator_ != nullptr);
  assert(buffer.ptr_ != nullptr);
  DeviceType src_type = buffer.device_type_;
  DeviceType dst_type = device_type_;
  assert(src_type != DeviceType::kDeviceUnknown && 
         dst_type != DeviceType::kDeviceUnknown);
  size_t nb_bytes = std::min(nb_bytes_, buffer.nb_bytes_);
  void* dst = ptr_;
  void* src = buffer.ptr_;
  MemcpyType memcpy_type = 
      (MemcpyType)((int8_t)src_type << 4 | (int8_t)dst_type);
  allocator_->memcpy(dst, src, nb_bytes, memcpy_type, stream, sync);
}

void Buffer::copyFrom(const Buffer* buffer, void* stream, bool sync) const {
  assert(allocator_ != nullptr);
  assert(buffer->ptr_ != nullptr);
  DeviceType src_type = buffer->device_type_;
  DeviceType dst_type = device_type_;
  assert(src_type != DeviceType::kDeviceUnknown && 
         dst_type != DeviceType::kDeviceUnknown);
  size_t nb_bytes = std::min(nb_bytes_, buffer->nb_bytes_);
  void* dst = ptr_;
  void* src = buffer->ptr_;
  MemcpyType memcpy_type = 
      (MemcpyType)((int8_t)src_type << 4 | (int8_t)dst_type);
  allocator_->memcpy(dst, src, nb_bytes, memcpy_type, stream, sync);
}

DeviceType Buffer::deviceType() const {
  return device_type_;
}

std::shared_ptr<Buffer> Buffer::getSharedFromThis() {
  return shared_from_this();
}

bool Buffer::isOwner() {
  return is_owner;
}

}  // namespace xym_infer
