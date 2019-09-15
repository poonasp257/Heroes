#ifndef RAMDOMMT_H
#define RAMDOMMT_H

#include "pch.h"

#define RAND(type, maxVal)	(type)	RandomMT::getInstance().rand(maxVal)

class RandomMT : public Singleton<RandomMT> {
public:
	uint64_t rand(int maxVal) {
		std::hash<std::thread::id> hasher;
		std::mt19937 engine((uint32_t)time(nullptr)
			+ (uint32_t)hasher(std::this_thread::get_id())); 

		std::uniform_int_distribution<uint64_t> distribution(0, UINT64_MAX);
		auto generator = bind(distribution, engine);

		return (uint64_t)(generator() % maxVal);
	}

};

#endif