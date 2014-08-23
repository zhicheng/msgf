#include "msgf.h"

#include "byteorder.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

/*
	=: native order, std. size & alignment
	<: little-endian, std. size & alignment
	>: big-endian, std. size & alignment
	!: same as >

	x: (no data);	do not change input or ignore from output
	b: signed   byte;
	B: unsigned byte;
	h: signed   short;
	H: unsigned short;
	i: signed   int;
	I: unsigned int;
	l: signed   long;
	L: unsigned long;
	q: signed   long long;
	Q: unsigned long long;
*/

enum {ENDIAN_NATIVE, ENDIAN_LE, ENDIAN_BE};


int
msgf_dump(void *msg, const char *restrict fmt, ...)
{
	int i;
	int c;
	int len;
	int endian;

	va_list ap;
	va_start(ap, fmt);

	i = len = 0;
	endian = ENDIAN_NATIVE;
	while ((c = fmt[i++]) != '\0') {
		if (c == '=') {
			endian = ENDIAN_NATIVE;
		} else if (c == '<') {
			endian = ENDIAN_LE;
		} else if (c == '>' || c == '!') {
			endian = ENDIAN_BE;
		} else if (c == 'x') {
			len++;
		} else if (c == 'b') {
			int8_t data = va_arg(ap, signed int);
			*(int8_t *)((uint8_t *)msg + len) = data;
			len += sizeof(data);
		} else if (c == 'B') {
			uint8_t data = va_arg(ap, unsigned int);
			*(uint8_t *)((uint8_t *)msg + len) = data;
			len += sizeof(data);
		} else if (c == 'h') {
			int16_t data = va_arg(ap, signed int);
			if (endian == ENDIAN_LE)
				data = htol16(data);
			else if (endian == ENDIAN_BE)
				data = htob16(data);
			*(int16_t *)((uint8_t *)msg + len) = data;
			len += sizeof(data);
		} else if (c == 'H') {
			uint16_t data = va_arg(ap, unsigned int);
			if (endian == ENDIAN_LE)
				data = htol16(data);
			else if (endian == ENDIAN_BE)
				data = htob16(data);
			*(uint16_t *)((uint8_t *)msg + len) = data;
			len += sizeof(data);
		} else if (c == 'i' || c == 'l') {
			int32_t data = va_arg(ap, int32_t);
			if (endian == ENDIAN_LE)
				data = htol32(data);
			else if (endian == ENDIAN_BE)
				data = htob32(data);
			*(int32_t *)((uint8_t *)msg + len) = data;
			len += sizeof(data);
		} else if (c == 'I' || c == 'L') {
			uint32_t data = va_arg(ap, uint32_t);
			if (endian == ENDIAN_LE)
				data = htol32(data);
			else if (endian == ENDIAN_BE)
				data = htob32(data);
			*(uint32_t *)((uint8_t *)msg + len) = data;
			len += sizeof(data);
		} else if (c == 'q') {
			int64_t data = va_arg(ap, int64_t);
			if (endian == ENDIAN_LE)
				data = htol64(data);
			else if (endian == ENDIAN_BE)
				data = htob64(data);
			*(int64_t *)((uint8_t *)msg + len) = data;
			len += sizeof(data);
		} else if (c == 'Q') {
			uint64_t data = va_arg(ap, uint64_t);
			if (endian == ENDIAN_LE)
				data = htol64(data);
			else if (endian == ENDIAN_BE)
				data = htob64(data);
			*(uint64_t *)((uint8_t *)msg + len) = data;
			len += sizeof(data);
		}
	}
	va_end(ap);

	return len;
}

int
msgf_load(const void *msg, const char *restrict fmt, ...)
{
	int i;
	int c;
	int len;
	int endian;

	va_list ap;
	va_start(ap, fmt);

	i = len = 0;
	endian = ENDIAN_NATIVE;
	while ((c = fmt[i++]) != '\0') {
		if (c == '=') {
			endian = ENDIAN_NATIVE;
		} else if (c == '<') {
			endian = ENDIAN_LE;
		} else if (c == '>' || c == '!') {
			endian = ENDIAN_BE;
		} else if (c == 'x') {
			len++;
		} else if (c == 'b') {
			int8_t *data = va_arg(ap, int8_t *);
			*data = *(int8_t *)((uint8_t *)msg + len);
			len += sizeof(*data);
		} else if (c == 'B') {
			uint8_t *data = va_arg(ap, uint8_t *);
			*data = *(uint8_t *)((uint8_t *)msg + len);
			len += sizeof(*data);
		} else if (c == 'h') {
			int16_t *data = va_arg(ap, int16_t *);
			*data = *(int16_t *)((uint8_t *)msg + len);
			if (endian == ENDIAN_LE)
				*data = ltoh16(*data);
			else if (endian == ENDIAN_BE)
				*data = btoh16(*data);
			len += sizeof(*data);
		} else if (c == 'H') {
			uint16_t *data = va_arg(ap, uint16_t *);
			*data = *(uint16_t *)((uint8_t *)msg + len);
			if (endian == ENDIAN_LE)
				*data = ltoh16(*data);
			else if (endian == ENDIAN_BE)
				*data = btoh16(*data);
			len += sizeof(*data);
		} else if (c == 'i' || c == 'l') {
			int32_t *data = va_arg(ap, int32_t *);
			*data = *(int32_t *)((uint8_t *)msg + len);
			if (endian == ENDIAN_LE)
				*data = ltoh32(*data);
			else if (endian == ENDIAN_BE)
				*data = btoh32(*data);
			len += sizeof(*data);
		} else if (c == 'I' || c == 'L') {
			uint32_t *data = va_arg(ap, uint32_t *);
			*data = *(uint32_t *)((uint8_t *)msg + len);
			if (endian == ENDIAN_LE)
				*data = ltoh32(*data);
			else if (endian == ENDIAN_BE)
				*data = btoh32(*data);
			len += sizeof(*data);
		} else if (c == 'q') {
			int64_t *data = va_arg(ap, int64_t *);
			*data = *(int64_t *)((uint8_t *)msg + len);
			if (endian == ENDIAN_LE)
				*data = ltoh64(*data);
			else if (endian == ENDIAN_BE)
				*data = btoh64(*data);
			len += sizeof(*data);
		} else if (c == 'Q') {
			uint64_t *data = va_arg(ap, uint64_t *);
			*data = *(uint64_t *)((uint8_t *)msg + len);
			if (endian == ENDIAN_LE)
				*data = ltoh64(*data);
			else if (endian == ENDIAN_BE)
				*data = btoh64(*data);
			len += sizeof(*data);
		}
	}
	va_end(ap);

	return len;
}
