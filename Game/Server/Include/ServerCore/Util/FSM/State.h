#ifndef STATE_H
#define STATE_H

template<class object_type>
class State {
private:
	std::wstring name;

public:
	State(const std::wstring& name) :
		name(name) {}
	virtual ~State() {}

	const wchar_t* getName() const { return name.c_str(); }

	virtual void enter(const object_type& object) = 0;
	virtual void execute(const object_type& object) = 0;
	virtual void exit(const object_type& object) = 0;
};
#endif