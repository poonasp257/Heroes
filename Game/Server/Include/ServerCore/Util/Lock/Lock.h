#ifndef LOCK_H
#define LOCK_H

class Thread;

class Lock {
private:
	std::wstring				name;
	objectId_t					id;

	std::shared_ptr<Thread>		lockingThread;
	std::wstring				lockingFuncName;
	int							lockingLineNo;

protected:
	Lock(const wchar_t* name);
	virtual ~Lock();

public:
	virtual void lock(LPCWSTR funcName, int lineNo);
	virtual void unlock();

	const wchar_t* getName() const { return name.c_str(); }
	objectId_t getId() const { return id; }
		
	Thread* getLockingThread() { return lockingThread.get(); }
	const wchar_t* getLockedFuncName() const { return lockingFuncName.c_str(); }
	int getLockedLineNo() const { return lockingLineNo; }
};

class CriticalSection : public Lock {
private:
	CRITICAL_SECTION lockObj;

public:
	CriticalSection(const wchar_t* name);
	~CriticalSection();

	virtual void lock(LPCWSTR funcName, int lineNo);
	virtual void unlock();
};

class Mutex : public Lock {
private:
	std::mutex lockObj;

public:
	Mutex(const wchar_t* name);
	~Mutex();

	virtual void lock(LPCWSTR funcName, int lineNo);
	virtual void unlock();
};
#endif