#include "stdafx.h"

Lock::Lock(const wchar_t* name) : 
	name(name), 
	id(LockManager::Instance().generateId()), 
	lockingThread(nullptr), 
	lockingFuncName(L""), 
	lockingLineNo(-1) { 
	// Nothing
}

Lock::~Lock() {
	// Nothing
}

void Lock::lock(LPCWSTR funcName, int lineNo) {
	lockingFuncName = funcName;
	lockingLineNo = lineNo;

	auto thread = ThreadManager::Instance().at(Thread::GetCurrentThreadId());
	if (thread == nullptr) return;

	lockingThread = thread->getPtr();
	thread->setLock(this);
}

void Lock::unlock() {
	lockingFuncName.clear();
	lockingLineNo = -1;

	if (lockingThread != nullptr) {
		lockingThread->setLock(nullptr);
		lockingThread = nullptr;
	}
}

CriticalSection::CriticalSection(const wchar_t* name) : Lock(name) {
	InitializeCriticalSection(&lockObj);
}

CriticalSection::~CriticalSection() {
	DeleteCriticalSection(&lockObj);
}

void CriticalSection::lock(LPCWSTR funcName, int lineNo) {
	EnterCriticalSection(&lockObj);
	Lock::lock(funcName, lineNo);
}

void CriticalSection::unlock() {
	Lock::unlock();
	LeaveCriticalSection(&lockObj);
}

Mutex::Mutex(const wchar_t* name) : Lock(name) {
	//Nothing
}

Mutex::~Mutex() {
	//Nothing
}

void Mutex::lock(LPCWSTR funcName, int lineNo) {
	Lock::lock(funcName, lineNo);
	lockObj.lock();
}

void Mutex::unlock() {
	Lock::unlock();
	lockObj.unlock();
}