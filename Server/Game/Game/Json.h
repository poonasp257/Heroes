#ifndef JSON_H
#define JSON_H

class Json {
public:
	Json();
	~Json();

	bool ReadFile(std::string);
	bool WriteFile(std::string);
};

#endif