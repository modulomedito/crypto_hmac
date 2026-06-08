//==================================================================================================
/// @file       rustlike_types.h
/// @author     modulomedito (chcchc1995@outlook.com)
/// @brief      Define rust-like types for C language
/// @copyright  Copyright (C) 2026. MIT License.
/// @details    This is a header for defining types like rust. C99 compatible.
///
/// See https://github.com/modulomedito/rustlike_types
//==================================================================================================
//==================================================================================================
// GUARD START
//==================================================================================================
#ifndef RUSTLIKE_TYPES_H
#define RUSTLIKE_TYPES_H
#ifdef __cplusplus
extern "C" {
#endif

//==================================================================================================
// INCLUDE
//==================================================================================================
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

//==================================================================================================
// PUBLIC TYPEDEF
//==================================================================================================
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef float f32;
typedef double f64;
typedef uintptr_t uptr;
typedef intptr_t iptr;
typedef ptrdiff_t isize;
typedef size_t usize;
typedef char ichar;
typedef unsigned char uchar;

//==================================================================================================
// PUBLIC DEFINE
//==================================================================================================
#define RUSTLIKE_TYPES__MAJOR_VERSION (0)
#define RUSTLIKE_TYPES__MINOR_VERSION (2)
#define RUSTLIKE_TYPES__PATCH_VERSION (0)

#ifndef bool
#define bool bool_t
#endif

#ifndef true
#define true (1)
#endif

#ifndef false
#define false (0)
#endif

//==================================================================================================
// PUBLIC ENUM
//==================================================================================================

//==================================================================================================
// PUBLIC STRUCT
//==================================================================================================
typedef struct {
    u8* ptr;
    usize len;
} Slice_u8;

typedef struct {
    u16* ptr;
    usize len;
} Slice_u16;

typedef struct {
    u32* ptr;
    usize len;
} Slice_u32;

typedef struct {
    u64* ptr;
    usize len;
} Slice_u64;

typedef struct {
    i8* ptr;
    usize len;
} Slice_i8;

typedef struct {
    i16* ptr;
    usize len;
} Slice_i16;

typedef struct {
    i32* ptr;
    usize len;
} Slice_i32;

typedef struct {
    i64* ptr;
    usize len;
} Slice_i64;

typedef struct {
    f32* ptr;
    usize len;
} Slice_f32;

typedef struct {
    f64* ptr;
    usize len;
} Slice_f64;

typedef struct {
    uptr* ptr;
    usize len;
} Slice_uptr;

typedef struct {
    iptr* ptr;
    usize len;
} Slice_iptr;

typedef struct {
    isize* ptr;
    usize len;
} Slice_isize;

typedef struct {
    usize* ptr;
    usize len;
} Slice_usize;

typedef struct {
    ichar* ptr;
    usize len;
} Slice_ichar;

typedef struct {
    uchar* ptr;
    usize len;
} Slice_uchar;

//==================================================================================================
// PUBLIC UNION
//==================================================================================================

//==================================================================================================
// PUBLIC VARIABLE DECLARATION
//==================================================================================================

//==================================================================================================
// PUBLIC FUNCTION DECLARATION
//==================================================================================================

//==================================================================================================
// GUARD END
//==================================================================================================
#ifdef __cplusplus
}
#endif
#endif // #ifndef RUSTLIKE_TYPES_H
