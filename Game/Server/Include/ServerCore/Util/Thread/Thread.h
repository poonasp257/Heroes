#ifndef THREAD_H
#define THREAD_H

#define MAKE_THREAD(className, process) \
	Thread::MakeThread(std::make_unique<std::thread>(&className##::##process, this), L#className)
	
class Lock;

class Thread : public std::enable_shared_from_this<Thread> {
private:
	threadId_t						id;
	std::wstring					name;
	std::unique_ptr<std::thread>	thread;
	Lock*							lock;

public:
	Thread(std::unique_ptr<std::thread> thread, const std::wstring& name);
	~Thread();

	std::shared_ptr<Thread> getPtr() { return shared_from_this(); }

	threadId_t getId() const { return id; }
	const wchar_t* getName() const { return name.c_str(); }

	void setLock(Lock* lock) { this->lock = lock; }
	Lock* getLock() const { return lock; }

	void join() { if(thread->joinable()) thread->join(); }

	static threadId_t GetCurrentThreadId() { return std::this_thread::get_id(); }
	static std::shared_ptr<Thread> MakeThread(std::unique_ptr<std::thread> thread, const std::wstring& name);
};
#endif