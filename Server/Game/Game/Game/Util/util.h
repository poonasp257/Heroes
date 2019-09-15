#ifndef UTIL_H
#define UTIL_H

#include "pch.h"

#define snprintf(dst, format, ...)	_snprintf_s(dst.data(), dst.size(), _TRUNCATE, format, __VA_ARGS__)
#define snwprintf(dst, format, ...)	_snprintf_s(dst.data(), dst.size(), _TRUNCATE, format, __VA_ARGS__)

#define fixInRange(minimum, x, maximum)	std::min(maximum, std::max(x, minimum))
#define isInRange(minimun, x, maximum)	(x == fixInRange(minimum, x, maximum)) ? true : false

inline bool isOverflow_uint(unsigned int original, unsigned int add) {
	unsigned int before = original;
	unsigned int after = original + add;

	return (before & 0x80000000) == (after & 0x80000000);
}

#define __W(x)	L##x
#define _W(x)	__W(x)

inline void StrConvA2T(CHAR *src, TCHAR *dest, size_t destLen) {
#ifdef UNICODE
	if (destLen < 1) return;

	MultiByteToWideChar(CP_ACP, 0, src, -1, dest, (int)(destLen - 1));
#endif
}

inline void StrConvT2A(TCHAR *src, CHAR *dest, size_t destLen) {
#ifdef UNICODE
	if (destLen < 1) return;

	WideCharToMultiByte(CP_ACP, 0, src, -1, dest, (int)(destLen - 1), NULL, FALSE);
#endif
}

inline void StrConvA2W(CHAR *src, WCHAR *dest, size_t destLen) {
	if (destLen < 1) return;

	MultiByteToWideChar(CP_ACP, 0, src, -1, dest, (int)(destLen - 1));
}

inline void StrConvW2A(WCHAR *src, CHAR *dest, size_t destLen) {
	if (destLen < 1) return;

	WideCharToMultiByte(CP_ACP, 0, src, -1, dest, (int)(destLen - 1), NULL, FALSE);
}

#undef	SAFE_DELETE
#define SAFE_DELETE(obj)						\
{												\
	if ((obj)) delete(obj);						\
	(obj) = 0L;									\
}

#undef	SAFE_DELETE_ARRAY						
#define SAFE_DELETE_ARRAY(arr)					\
{												\
	if ((arr)) delete[] (arr);					\
	(arr) = 0L;									\
}				

#define SAFE_FREE(obj)							\
{												\
	if ((obj)) obj->free();						\
	(obj) = 0L;									\
}

#define SAFE_RELEASE(obj)						\
{												\
	if ((obj)) obj.release();					\
}

#endif