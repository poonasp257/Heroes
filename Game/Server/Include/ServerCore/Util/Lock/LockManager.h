#ifndef LOCK_MANAGER_H
#define LOCK_MANAGER_H

class Lock;

class LockManager {
private:
	LockManager();
	~LockManager();

	LockManager(LockManager&&) = delete;
	LockManager(const LockManager&) = delete;
	LockManager& operator=(LockManager&&) = delete;
	LockManager& operator=(const LockManager&) = delete;

public:
	objectId_t generateId() const {
		static objectId_t idSeed = 0;
		return ++idSeed;
	}

	Lock* checkDeadLock(Lock* newLock);

	static auto& Instance() {
		static LockManager instance;
		return instance;
	}
};
#endif