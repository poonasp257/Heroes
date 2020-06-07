#ifndef ASSERT_H
#define ASSERT_H

#undef ASSERT
#define ASSERT(x)	Assert(x, _T(__FILE__), __LINE__)

void Assert(bool condition, LPCWSTR fileName, int lineNo);

#endif