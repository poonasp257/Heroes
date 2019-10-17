#ifndef SINGLETON_H
#define SINGLETON_H

template<class TYPE>
class Singleton {
protected:
	Singleton() {}
	virtual ~Singleton() {}

public:
	Singleton(const TYPE&) = delete;
	TYPE& operator=(const TYPE&) = delete;

	static TYPE& GetInstance() { 
		static TYPE instance;
		return instance; 
	}
};

#endif