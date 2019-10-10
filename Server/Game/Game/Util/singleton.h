#ifndef SINGLETON_H
#define SINGLETON_H

template<class TYPE>
class Singleton {
protected:
	Singleton() {}
	~Singleton() {}

public:
	Singleton(const TYPE& other) = delete;
	TYPE& operator=(const TYPE& other) = delete;

	static TYPE& GetInstance() { 
		static TYPE instance;
		return instance; 
	}
};

#endif