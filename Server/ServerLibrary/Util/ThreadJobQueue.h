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

private:
	void swap() {
		if (writeQueue == &queue[Write]) {
			writeQueue = &queue[Read];
			readQueue = &queue[Write];
		}
		else {
			writeQueue = &queue[Write];
			readQueue = &queue[Read];
		}
	}

	size_t size() const {
		return readQueue->size() + writeQueue->size();
	}

public:
	ThreadJobQueue() {
		readQueue = &queue[Read];
		writeQueue = &queue[Write];
	}

	~ThreadJobQueue() {

	}

	void push(const T& value) {
		std::lock_guard<std::mutex> guard(lock);
		writeQueue->push(value);
	}

	void pop(T& t) {
		std::lock_guard<std::mutex> guard(lock);
		if (this->size() == 0) {
			return;
		}

		if (readQueue->empty()) {
			this->swap();
		}
		
		t = readQueue->front();
		readQueue->pop();
	}
	 
	bool isEmpty() const { 
		const std::lock_guard<std::mutex> guard(lock);
		return size() == 0;
	}
};
#endif