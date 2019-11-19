#ifndef THREAD_JOB_QUEUE_H
#define THREAD_JOB_QUEUE_H

template<typename T>
class ThreadJobQueue {
private:
	enum {
		Read,
		Write
	};

private:
	std::queue<T> queue[2];	
	std::queue<T> *readQueue;
	std::queue<T> *writeQueue;

	std::mutex lock;

public:
	ThreadJobQueue() {
		readQueue = &queue[Read];
		writeQueue = &queue[Write];
	}

	~ThreadJobQueue() {

	}

	bool empty() { return size() == 0; }

	size_t size() {
		const std::lock_guard<std::mutex> guard(lock);
		return readQueue->size() + writeQueue->size();
	}

	void swap() {
		const std::lock_guard<std::mutex> guard(lock);

		if (writeQueue == &queue[Write]) {
			writeQueue = &queue[Read];
			readQueue = &queue[Write];
		}
		else {
			writeQueue = &queue[Write];
			readQueue = &queue[Read];
		}
	}

	void push(const T& value) {
		std::lock_guard<std::mutex> guard(lock);
		writeQueue->push(value);
	}

	void pop(T& t) {
		if (readQueue->empty()) {
			this->swap();
		}
		
		std::lock_guard<std::mutex> guard(lock);
		t = readQueue->front();
		readQueue->pop();
	}
};
#endif