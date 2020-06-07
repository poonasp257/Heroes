#ifndef THREAD_MANAGER_H
#define THREAD_MANAGER_H

class Thread;

class ThreadManager {
private:
	std::unordered_map<threadId_t, std::shared_ptr<Thread>> threadPool;

private:
	ThreadManager();
	~ThreadManager();

	ThreadManager(ThreadManager&&) = delete;
	ThreadManager(const ThreadManager&) = delete;
	ThreadManager& operator=(ThreadManager&&) = delete;
	ThreadManager& operator=(const ThreadManager&) = delete;

public:
	void put(std::shared_ptr<Thread> thread);
	void remove(threadId_t threadId);
	Thread* at(threadId_t threadId) const;

	size_t getSize() const { return threadPool.size(); }

	void joinAll();

	static auto& Instance() {
		static ThreadManager instance;
		return instance;
	}
};
#endif