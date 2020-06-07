#include "stdafx.h"
#include "UserManager.h"

UserManager::UserManager() {

}

UserManager::~UserManager() {

}

User* UserManager::find(const std::wstring& accessKey) {
	const auto& itr = userTable.find(accessKey);
	if (itr == userTable.end()) return nullptr;
	
	return (itr->second).get();
}

User* UserManager::find(objectId_t sessionId) {
	for (const auto& itr : userTable) {
		User* user = itr.second.get();
		if (user->sessionId == sessionId) return user;
	}

	return nullptr;
}

void UserManager::registerUser(const std::wstring& accessKey, std::unique_ptr<User> user) {
	userTable.insert(std::make_pair(accessKey, std::move(user)));
}

void UserManager::unregisterUser(const std::wstring& accessKey) {
	const auto& itr = userTable.find(accessKey);
	if (itr == userTable.end()) return;

	userTable.erase(itr);
}

void UserManager::unregisterUser(objectId_t sessionId) {
	auto itr = std::find_if(userTable.begin(), userTable.end(),
		[&sessionId](const auto& pair) { 
			const auto& user = pair.second;
			return user->sessionId == sessionId; 
		});
	if (itr == userTable.end()) return;

	userTable.erase(itr);
}