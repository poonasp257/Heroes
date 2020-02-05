#include "stdafx.h"

Thread::Thread(std::thread *thread) : thread(thread) {
	id = thread->get_id();

	SystemLogger::Log(Logger::Info, L"create thread : id[0x%X]", id);
}

Thread::~Thread() {
	thread->join();
}