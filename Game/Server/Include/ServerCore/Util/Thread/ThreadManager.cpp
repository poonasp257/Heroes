#include "stdafx.h"

ThreadManager::ThreadManager() {

}

ThreadManager::~ThreadManager() {
	threadPool.clear();
}

void ThreadManager::put(std::shared_ptr<Thread> thread) {
	threadPool.insert(std::make_pair(thread->getId(), std::move(thread)));
}

void ThreadManager::remove(threadId_t threadId) {
	auto thread = threadPool.find(threadId);
	if (thread == threadPool.end()) {
		ERROR_LOG(L"doesn't exist thread");
		return;
	}
	 
	threadPool.erase(thread);
}

Thread* ThreadManager::at(threadId_t threadId) const {
	auto thread = threadPool.find(threadId);
	if (thread == threadPool.end()) return nullptr;
	
	return thread->second.get();
}

void ThreadManager::joinAll() {
	for (auto& pair : threadPool) {
		pair.second->join();
	}
}