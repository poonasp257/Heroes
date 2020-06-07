#ifndef USER_MANAGER_H
#define USER_MANAGER_H

struct User {
	objectId_t sessionId;
	objectId_t accountId;

	User(objectId_t sessionId, objectId_t accountId) 
		: sessionId(sessionId), accountId(accountId) {}
};

class UserManager {
private:
	std::unordered_map<std::wstring, std::unique_ptr<User>> userTable;

private:
	UserManager();
	~UserManager();

	UserManager(UserManager&&) = delete;
	UserManager(const UserManager&) = delete;
	UserManager& operator=(UserManager&&) = delete;
	UserManager& operator=(const UserManager&) = delete;

public:
	User* find(const std::wstring& accessKey);
	User* find(objectId_t sessionId);

	void registerUser(const std::wstring& accessKey, std::unique_ptr<User> user);
	void unregisterUser(const std::wstring& accessKey);
	void unregisterUser(objectId_t sessionId);	

	static auto& Instance() {
		static UserManager instance;
		return instance;
	}
};
#endif