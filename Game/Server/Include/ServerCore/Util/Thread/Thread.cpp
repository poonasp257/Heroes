#include "stdafx.h"

Thread::Thread(std::unique_ptr<std::thread> thread, const std::wstring& name) : 
	thread(std::move(thread)), 
	lock(nullptr) {
	this->id = this->thread->get_id();
	this->name = name;
	INFO_LOG(L"create thread : id[0x%X] name[%s]", id, name.c_str());
}

Thread::~Thread() {
	INFO_LOG(L"destroyed thread : id[0x%X] name[%s]", id, name.c_str());
	if(thread->joinable()) thread->join();
}

std::shared_ptr<Thread> Thread::MakeThread(std::unique_ptr<std::thread> thread, const std::wstring& name) {
	auto newThread = std::make_shared<Thread>(std::move(thread), name);
	ThreadManager::Instance().put(newThread);
	return std::move(newThread);
}