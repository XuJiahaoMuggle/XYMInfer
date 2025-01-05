#pragma once
#include <cstddef>
           
namespace xym_infer {

enum class DeviceType : int8_t {
  kDeviceUnknown = -1,
  kDeviceCPU     = 0,
  kDeviceCUDA    = 1
};

enum class DataType : int8_t {
  kDataTypeUnknown = -1,
  kDataTypeFP32    = 0,
  kDataTypeInt8    = 1,
  kDataTypeInt32   = 2, 
};

inline size_t dataTypeSize(DataType dtype) {
  switch (dtype)
  {
  case DataType::kDataTypeInt8:
    return sizeof(int8_t);
  case DataType::kDataTypeInt32:
    return sizeof(int32_t);
  case DataType::kDataTypeFP32:
    return sizeof(float);
  default:
    return 0;
  }
}

// bitset: 0x[src][dst]
enum class MemcpyType : int8_t {
  kMemcpyUnknown   = -1,        
  kMemcpyCPU2CPU   = 0x00,   
  kMemcpyCPU2CUDA  = 0x01,      
  kMemcpyCUDA2CUDA = 0x10,     
  kMemcpyCUDA2CPU  = 0x11  
};

}  // namespace xym_infer