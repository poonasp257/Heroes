#ifndef LOCK_MANAGER_H
#define LOCK_MANAGER_H

class Lock;

class LockManager {
private:
	LockManager();
	~LockManager();

public:
	LockManager(const LockManager&) = delete;
	LockManager(LockManager&&) = delete;
	LockManager& operator=(const LockManager&) = delete;
	LockManager& operator=(LockManager&&) = delete;

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