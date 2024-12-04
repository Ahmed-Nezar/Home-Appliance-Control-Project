#ifndef TYPES_H
#define TYPES_H

typedef unsigned char uint8;
typedef char int8;
typedef unsigned short uint16;
typedef short int16;
typedef unsigned int uint32;
typedef int int32;
typedef unsigned long long uint64;
typedef long long int64;
typedef float float32;
typedef double float64;

typedef unsigned char* uint8_ptr;
typedef char* int8_ptr;
typedef unsigned short* uint16_ptr;
typedef short* int16_ptr;
typedef unsigned int* uint32_ptr;
typedef int* int32_ptr;
typedef unsigned long long* uint64_ptr;
typedef long long* int64_ptr;
typedef float* float32_ptr;
typedef double* float64_ptr;

typedef volatile unsigned char vuint8;
typedef volatile char vint8;
typedef volatile unsigned short vuint16;
typedef volatile short vint16;
typedef volatile unsigned int vuint32;
typedef volatile int vint32;
typedef volatile unsigned long long vuint64;
typedef volatile long long vint64;
typedef volatile float vfloat32;
typedef volatile double vfloat64;

#endif