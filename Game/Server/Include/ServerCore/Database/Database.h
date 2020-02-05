#ifndef DATABASE_H
#define DATABASE_H

enum class DBState {
	Stop, StandBy, Running
};

class Database {
protected:
	DBState state;

public:
	Database() : state(DBState::Stop) {}
	virtual ~Database() {}

	virtual bool connect(const wchar_t *ip, int port, const wchar_t *dbName, const wchar_t *id, const wchar_t *password) = 0;
	virtual bool disconnect() = 0;
	virtual bool isConnected() = 0;

	virtual void run() = 0;
	DBState getState() const { return state; }
};
#endif