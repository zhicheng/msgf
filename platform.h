#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#if defined(__GLIBC__)

#include <endian.h>
#include <byteswap.h>
#define msgf_bswap16(x) bswap_16(x)
#define msgf_bswap32(x) bswap_32(x)
#define msgf_bswap64(x) bswap_64(x)

#define MSGF_BYTE_ORDER    __BYTE_ORDER
#define MSGF_LITTLE_ENDIAN __LITTLE_ENDIAN
#define MSGF_BIG_ENDIAN    __BIG_ENDIAN

#elif defined(__APPLE__)
#include <machine/endian.h>
#include <libkern/OSByteOrder.h>
#define msgf_bswap16(x) OSSwapInt16(x)
#define msgf_bswap32(x) OSSwapInt32(x)
#define msgf_bswap64(x) OSSwapInt64(x)

#define MSGF_BYTE_ORDER    BYTE_ORDER
#define MSGF_LITTLE_ENDIAN LITTLE_ENDIAN
#define MSGF_BIG_ENDIAN    BIG_ENDIAN

#elif defined(__FreeBSD__) || defined(__DragonFlyBSD__) || defined(__NetBSD__)

#include <sys/endian.h>
#define msgf_bswap16(x) bswap16(x)
#define msgf_bswap32(x) bswap32(x)
#define msgf_bswap64(x) bswap64(x)

#define MSGF_BYTE_ORDER    _BYTE_ORDER
#define MSGF_LITTLE_ENDIAN _LITTLE_ENDIAN
#define MSGF_BIG_ENDIAN    _BIG_ENDIAN

#else 
#error Unsupported Platform
#endif

#endif /* __PLATFORM_H__ */
