#ifndef THREAD_H
#define THREAD_H

class Thread {
private:
	threadId						id;
	std::unique_ptr<std::thread>	thread;

public:
	Thread(std::thread *thread);
	~Thread();

	threadId getId() const { return id; }

	static threadId GetCurrentThreadId() { return std::this_thread::get_id(); }
};
#endif