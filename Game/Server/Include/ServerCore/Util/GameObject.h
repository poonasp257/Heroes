#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

class GameObject {
private:
	static std::vector<GameObject*> gameObjects;

private:
	objectId_t generateId() const {
		static objectId_t idSeed = 0;
		return idSeed++;
	}
	
protected:
	objectId_t		instanceId;
	std::wstring	name;

public:
	GameObject(const std::wstring& name);
	virtual ~GameObject();

	virtual void start() = 0;
	virtual void update() = 0;

	objectId_t getId() const { return instanceId; }
	
	const wchar_t* getName() const { return name.c_str(); }
	void setName(const std::wstring& name) { this->name = name; }

	static GameObject* Find(objectId_t id);
	static GameObject* Find(const std::wstring& name);
};
#endif