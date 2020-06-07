#include "stdafx.h"

std::vector<GameObject*> GameObject::gameObjects;

GameObject::GameObject() : 
	instanceId(generateId()),
	name(L"GameObject"),
	activeSelf(true) {
	gameObjects.push_back(this);
}

GameObject::GameObject(const std::wstring& name) : 
	instanceId(generateId()), 
	name(name),
	activeSelf(true) {
	gameObjects.push_back(this);
}

GameObject::~GameObject() {
	auto itr = std::find(gameObjects.begin(), gameObjects.end(), this);
	if(itr != gameObjects.end()) gameObjects.erase(itr);
}

GameObject* GameObject::Find(objectId_t id) {
	for (auto object : gameObjects) {
		if (object->getId() == id) return object;
	}

	return nullptr;
}

GameObject* GameObject::Find(const std::wstring& name) {
	for (auto object : gameObjects) {
		if (object->getName() == name) return object;
	}

	return nullptr;
}