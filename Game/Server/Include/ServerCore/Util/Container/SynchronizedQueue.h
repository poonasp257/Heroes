#ifndef SYNCHRONIZED_QUEUE_H
#define SYNCHRONIZED_QUEUE_H

template<typename T>
class SynchronizedQueue {
private:
	enum {
		Read,
		Write
	};

private:
	std::queue<T>	queue[2];	
	std::queue<T>*	readQueue;
	std::queue<T>*	writeQueue;
	CriticalSection	lock;

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
	SynchronizedQueue(const wchar_t* name) : 
		lock(name) {
		readQueue = &queue[Read];
		writeQueue = &queue[Write];
	}

	~SynchronizedQueue() {

	}

	void push(T& value) {
		SAFE_LOCK(lock);
		writeQueue->push(std::move(value));
	}

	void pop(T& t) {
		SAFE_LOCK(lock);
		if (this->size() == 0) {
			return;
		}

		if (readQueue->empty()) {
			this->swap();
		}
		
		t = std::move(readQueue->front());
		readQueue->pop();
	}
	 
	bool isEmpty() {
		SAFE_LOCK(lock);
		return size() == 0;
	}
};
#endif