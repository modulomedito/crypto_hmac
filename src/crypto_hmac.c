//==================================================================================================
/// @file       crypto_hmac.c
/// @author     modulomedito (chcchc1995@outlook.com)
/// @brief
/// @copyright  Copyright (C) 2026. MIT License.
/// @details
//==================================================================================================
//==================================================================================================
// INCLUDE
//==================================================================================================
#include "crypto_hmac.h"
#include "crypto_sha1.h"

//==================================================================================================
// IMPORTED SWITCH CHECK
//==================================================================================================
#if !defined(CRYPTO_SHA1__MAJOR_VERSION) || (CRYPTO_SHA1__MAJOR_VERSION != 0)
#error CRYPTO_SHA1__MAJOR_VERSION is NOT defined or NOT matched!!!
#endif
#if !defined(CRYPTO_SHA1__MINOR_VERSION) || (CRYPTO_SHA1__MINOR_VERSION != 1)
#error CRYPTO_SHA1__MINOR_VERSION is NOT defined or NOT matched!!!
#endif

//==================================================================================================
// PRIVATE DEFINE
//==================================================================================================

//==================================================================================================
// PRIVATE TYPEDEF
//==================================================================================================

//==================================================================================================
// PRIVATE ENUM
//==================================================================================================

//==================================================================================================
// PRIVATE STRUCT
//==================================================================================================

//==================================================================================================
// PRIVATE UNION
//==================================================================================================

//==================================================================================================
// PRIVATE FUNCTION DECLARATION
//==================================================================================================
static crypto_hmac__Ret crypto_hmac__sha1_compute(
    const u8 *key_ref,
    u32 key_len,
    const u8 *msg_ref,
    u32 msg_len,
    u8 *hmac_mut
);

//==================================================================================================
// PRIVATE VARIABLE DEFINITION
//==================================================================================================

//==================================================================================================
// PUBLIC VARIABLE DEFINITION
//==================================================================================================

//==================================================================================================
// PUBLIC FUNCTION DEFINITION
//==================================================================================================
crypto_hmac__Ret crypto_hmac__compute(
    crypto_hmac__HashType hash_type,
    const u8 *key_ref,
    u32 key_len,
    const u8 *msg_ref,
    u32 msg_len,
    u8 *hmac_mut,
    u32 hmac_buf_size
) {
    // Only HMAC-SHA1 support yet
    if (hash_type != crypto_hmac__HashType_Sha1) {
        return crypto_hmac__Ret_Error;
    }

    return crypto_hmac__sha1_compute(key_ref, key_len, msg_ref, msg_len, hmac_mut, hmac_buf_size);
}

//==================================================================================================
// PRIVATE FUNCTION DEFINITION
//==================================================================================================
static crypto_hmac__Ret crypto_hmac__sha1_compute(
    const u8 *key_ref,
    u32 key_len,
    const u8 *msg_ref,
    u32 msg_len,
    u8 *hmac_mut,
    u32 hmac_buf_size
) {
    if ((key_ref == NULL) || //
        (key_len == 0) || //
        (msg_ref == NULL) || //
        (hmac_mut == NULL)) {
        return crypto_hmac__Ret_InvalidArg;
    }

    crypto_sha1__Ctx outer;
    crypto_sha1__Ctx inner;
    u8 tmp;

    crypto_sha1__Ctx_init(&outer);
    crypto_sha1__Ctx_init(&inner);

    u32 i;

    for (i = 0; i < key_len; i++) {
        tmp = key_ref[i] ^ 0x5c;
        crypto_sha1__Ctx_update(&outer, &tmp, 1);
        tmp = key_ref[i] ^ 0x36;
        crypto_sha1__Ctx_update(&inner, &tmp, 1);
    }

    for (i = key_len; i < 64; i++) {
        tmp = 0x5c;
        crypto_sha1__Ctx_update(&outer, &tmp, 1);
        tmp = 0x36;
        crypto_sha1__Ctx_update(&inner, &tmp, 1);
    }

    crypto_sha1__Ctx_update(&inner, msg_ref, msg_len);
    crypto_sha1__Ctx_finalize(&inner, hmac_mut, hmac_buf_size);

    crypto_sha1__Ctx_update(&outer, hmac_mut, CRYPTO_HMAC__SHA1_HASH_SIZE);
    crypto_sha1__Ctx_finalize(&outer, hmac_mut, hmac_buf_size);

    return crypto_hmac__Ret_Ok;
}

//==================================================================================================
// TEST
//==================================================================================================
#include <string.h>

#define ENABLE_DEBUG_PRINT (0)

#if defined(ENABLE_DEBUG_PRINT) && (ENABLE_DEBUG_PRINT > 0)
#include <stdio.h>
#endif // ENABLE_DEBUG_PRINT

static i32 crypto_hmac__test_tc1(void) {
    const u8 key_buf[] = {0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b,
                          0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b};
    const u8 msg_buf[] = "Hi There";
    const u8 expected_buf[] = {0xb6, 0x17, 0x31, 0x86, 0x55, 0x05, 0x72, 0x64, 0xe2, 0x8b,
                               0xc0, 0xb6, 0xfb, 0x37, 0x8c, 0x8e, 0xf1, 0x46, 0xbe, 0x00};
    u8 digest_buf[20];

    crypto_hmac__compute(
        crypto_hmac__HashType_Sha1,
        key_buf,
        sizeof(key_buf),
        msg_buf,
        strlen(msg_buf),
        digest_buf,
        sizeof(digest_buf)
    );

    i32 cmp = memcmp(expected_buf, digest_buf, sizeof(expected_buf));
    if (cmp != 0) {
#if defined(ENABLE_DEBUG_PRINT) && (ENABLE_DEBUG_PRINT > 0)
        for (u32 i = 0; i < sizeof(digest_buf); i++) {
            printf("digest[%d] = 0x%02x\n", i, digest_buf[i]);
        }
#endif // ENABLE_DEBUG_PRINT
        return __LINE__;
    }

    return 0;
}

static i32 crypto_hmac__test_tc2(void) {
    const u8 key_buf[] = "Jefe";
    const u8 msg_buf[] = "what do ya want for nothing?";
    const u8 expected_buf[] = {0xef, 0xfc, 0xdf, 0x6a, 0xe5, 0xeb, 0x2f, 0xa2, 0xd2, 0x74,
                               0x16, 0xd5, 0xf1, 0x84, 0xdf, 0x9c, 0x25, 0x9a, 0x7c, 0x79};
    u8 digest_buf[20];

    crypto_hmac__compute(
        crypto_hmac__HashType_Sha1,
        key_buf,
        strlen(key_buf),
        msg_buf,
        strlen(msg_buf),
        digest_buf,
        sizeof(digest_buf)
    );

    i32 cmp = memcmp(expected_buf, digest_buf, sizeof(expected_buf));
    if (cmp != 0) {
#if defined(ENABLE_DEBUG_PRINT) && (ENABLE_DEBUG_PRINT > 0)
        for (u32 i = 0; i < sizeof(digest_buf); i++) {
            printf("digest[%d] = 0x%02x\n", i, digest_buf[i]);
        }
#endif // ENABLE_DEBUG_PRINT
        return __LINE__;
    }

    return 0;
}

static i32 crypto_hmac__test_tc3(void) {
    const u8 key_buf[] = {0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
                          0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa};
    const u8 msg_buf[] = {0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd,
                          0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd,
                          0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd,
                          0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd,
                          0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd};
    const u8 expected_buf[] = {0x12, 0x5d, 0x73, 0x42, 0xb9, 0xac, 0x11, 0xcd, 0x91, 0xa3,
                               0x9a, 0xf4, 0x8a, 0xa1, 0x7b, 0x4f, 0x63, 0xf1, 0x75, 0xd3};
    u8 digest_buf[20];

    crypto_hmac__compute(
        crypto_hmac__HashType_Sha1,
        key_buf,
        sizeof(key_buf),
        msg_buf,
        sizeof(msg_buf),
        digest_buf,
        sizeof(digest_buf)
    );

    i32 cmp = memcmp(expected_buf, digest_buf, sizeof(expected_buf));
    if (cmp != 0) {
#if defined(ENABLE_DEBUG_PRINT) && (ENABLE_DEBUG_PRINT > 0)
        for (u32 i = 0; i < sizeof(digest_buf); i++) {
            printf("digest[%d] = 0x%02x\n", i, digest_buf[i]);
        }
#endif // ENABLE_DEBUG_PRINT
        return __LINE__;
    }

    return 0;
}

i32 crypto_hmac__test(void) {
    i32 result;

    result = crypto_hmac__test_tc1();
    if (result != 0) {
        return result;
    }
    result = crypto_hmac__test_tc2();
    if (result != 0) {
        return result;
    }
    result = crypto_hmac__test_tc3();
    if (result != 0) {
        return result;
    }

    return 0;
}
