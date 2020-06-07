#include "stdafx.h"

LockManager::LockManager() {

}

LockManager::~LockManager() {

}

Lock* LockManager::checkDeadLock(Lock* newLock) {	
	auto currentThread = ThreadManager::Instance().at(Thread::GetCurrentThreadId());
	if (currentThread == nullptr) return nullptr;

	auto threadLock = currentThread->getLock();
	if (threadLock == nullptr) return nullptr;

	Lock* deadLock = nullptr;
	if (newLock->getId() == threadLock->getId()) {
		deadLock = newLock;
	}

	return nullptr;
}