#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

template<class object_type>
class StateMachine {
private:
	object_type& owner;
	State<object_type>* currentState;
	State<object_type>* previousState;

public:
	StateMachine(object_type* owner) :
		currentState(nullptr),
		previousState(nullptr),
		owner(*owner) {}
	~StateMachine() {}

	bool isInState(State<object_type>& state) const { return currentState == &state; }

	void setCurrentState(State<object_type>& state) { currentState = &state; }
	void setPreviousState(State<object_type>& state) { previousState = &state; }
	State<object_type>* getCurrentState() const { return currentState; }
	State<object_type>* getPreviousState() const { return previousState; }

	void revertPreviousState() {
		this->changeState(*previousState);
	}

	void changeState(State<object_type>& state) {
		previousState = currentState;
		if (currentState != nullptr) currentState->exit(owner);

		currentState = &state;
		currentState->enter(owner);
	}

	void update() const {
		if (currentState) currentState->execute(owner);
	}
};
#endif