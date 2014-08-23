#ifndef __BYTEORDER_H__
#define __BYTEORDER_H__

#include <stdint.h>
#include "platform.h"

typedef uint16_t le16_t;
typedef uint32_t le32_t;
typedef uint64_t le64_t;

typedef uint16_t be16_t;
typedef uint32_t be32_t;
typedef uint64_t be64_t;

#if MSGF_BYTE_ORDER == MSGF_LITTLE_ENDIAN

static uint16_t ltoh16(le16_t v) { return v; }
static uint16_t ltoh32(le32_t v) { return v; }
static uint16_t ltoh64(le64_t v) { return v; }

static le16_t htol16(uint16_t v) { return v; }
static le32_t htol32(uint32_t v) { return v; }
static le64_t htol64(uint64_t v) { return v; }

static uint16_t btoh16(be16_t v) { return msgf_bswap16(v); }
static uint32_t btoh32(be32_t v) { return msgf_bswap32(v); }
static uint64_t btoh64(be64_t v) { return msgf_bswap64(v); }

static be16_t  htob16(uint16_t v) { return msgf_bswap16(v); }
static be32_t  htob32(uint32_t v) { return msgf_bswap32(v); }
static be64_t  htob64(uint64_t v) { return msgf_bswap64(v); }

#elif MSGF_BYTE_ORDER == MSGF_BIG_ENDIAN

static uint16_t ltoh16(le16_t v) { return msgf_bswap16(v); }
static uint16_t ltoh32(le32_t v) { return msgf_bswap32(v); }
static uint16_t ltoh64(le64_t v) { return msgf_bswap64(v); }

static le16_t htol16(uint16_t v) { return msgf_bswap16(v); }
static le32_t htol32(uint32_t v) { return msgf_bswap32(v); }
static le64_t htol64(uint64_t v) { return msgf_bswap64(v); }

static uint16_t btoh16(be16_t v) { return v; }
static uint32_t btoh32(be32_t v) { return v; }
static uint64_t btoh64(be64_t v) { return v; }

static be16_t  htob16(uint16_t v) { return v; }
static be32_t  htob32(uint32_t v) { return v; }
static be64_t  htob64(uint64_t v) { return v; }

#else

#error Unsupported ByteOrder

#endif 

#endif /* __BYTEORDER_H__ */

