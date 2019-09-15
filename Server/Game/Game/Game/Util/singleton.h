#ifndef SIGLETON_H
#define SIGLETON_H

#include "pch.h"

template <class T>
class Singleton {
protected:
	Singleton() {}
	~Singleton() {}
public:
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;

	static T& getInstance() {
		static T instance;
		return instance;
	}
};

#endif