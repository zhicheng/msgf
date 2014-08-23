#ifndef __MSGF_H__
#define __MSGF_H__

int
msgf_dump(void *msg, const char *restrict fmt, ...);

int
msgf_load(const void *msg, const char *restrict fmt, ...);

#endif /* __MSGF_H__ */
