#include "stdafx.h"

ScopedLock::ScopedLock(Lock* lock, LPCWCHAR funcName, int lineNo) : 
	lock(nullptr) {
	if (lock == nullptr) return;

	this->lock = lock;
	Lock* deadLock = LockManager::Instance().checkDeadLock(lock);
	if (deadLock != nullptr) {
		wprintf(L"*Detecting dead lock: [%s], [%s]*\n", deadLock->getName(), lock->getName());
		wprintf(L"*try to lock...[%s in %d]*\n", lock->getLockedFuncName(), lock->getLockedLineNo());
		return;
	}

	lock->lock(funcName, lineNo);
}

ScopedLock::~ScopedLock() {
	if(lock != nullptr) lock->unlock();
}