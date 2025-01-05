
#include <include/xym_infer.h>

int main(int argc, char** argv) {
  auto cuda_allocator = 
      xym_infer::getAllocator(xym_infer::DeviceType::kDeviceCUDA);
  auto ptr = cuda_allocator->allocate(10);
  cuda_allocator->release(ptr);


  auto cpu_allocator = 
      xym_infer::getAllocator(xym_infer::DeviceType::kDeviceCPU);
  ptr = cpu_allocator->allocate(10);
  cpu_allocator->release(ptr);
  return 0;
}