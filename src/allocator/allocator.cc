#include <string.h>
#include <cuda_runtime.h>
#include <include/allocator/allocator.h>
#include <src/allocator/cuda_allocator.h>
#include <src/allocator/cpu_allocator.h>

namespace xym_infer {
using xym_infer::MemcpyType;

void Allocator::memcpy(void* dst, const void* src, size_t nb_bytes,
                       MemcpyType memcpy_type, void* stream,
                       bool sync) const {
  cudaStream_t cuda_stream = reinterpret_cast<cudaStream_t>(stream);
  switch (memcpy_type)
  {
  case MemcpyType::kMemcpyCPU2CPU:
    ::memcpy(dst, src, nb_bytes);
    break;
  case MemcpyType::kMemcpyCPU2CUDA:
    if (stream) {
      cudaMemcpyAsync(dst, src, nb_bytes, cudaMemcpyHostToDevice, cuda_stream);  
    } else {
      cudaMemcpy(dst, src, nb_bytes, cudaMemcpyHostToDevice);
    }
    break;
  case MemcpyType::kMemcpyCUDA2CPU:
    if (stream) {
      cudaMemcpyAsync(dst, src, nb_bytes, cudaMemcpyDeviceToHost, cuda_stream);
    } else {
      cudaMemcpy(dst, src, nb_bytes, cudaMemcpyDeviceToHost);
    }
    break;
  case MemcpyType::kMemcpyCUDA2CUDA:
    if (stream) {
      cudaMemcpyAsync(dst, src, nb_bytes, cudaMemcpyDeviceToDevice, cuda_stream);
    } else {
      cudaMemcpy(dst, src, nb_bytes, cudaMemcpyDeviceToDevice);
    }
    break;
  default:
    break;
  }
  sync &= memcpy_type == MemcpyType::kMemcpyCUDA2CPU || 
      memcpy_type == MemcpyType::kMemcpyCUDA2CUDA;
  if (sync) {
    cudaStreamSynchronize(cuda_stream);
  }
} 

std::shared_ptr<Allocator> getAllocator(DeviceType device_type) {
  switch (device_type)
  {
  case DeviceType::kDeviceCPU:
    return CPUAllocator::getInstance();
  case DeviceType::kDeviceCUDA:
    return CUDAAllocator::getInstance();
  default:
    return nullptr;
  }
}

}  // namespace xym_infer
