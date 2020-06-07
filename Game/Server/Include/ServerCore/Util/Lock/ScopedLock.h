#ifndef SCOPED_LOCK_H
#define SCOPED_LOCK_H

#define SAFE_LOCK(lock) ScopedLock __lockSafe(&lock, _T(__FUNCTION__), __LINE__)

class Lock;

class ScopedLock {
private:
	Lock* lock;

public:
	ScopedLock(Lock* lock, LPCWCHAR funcName, int lineNo);
	~ScopedLock();
};
#endif