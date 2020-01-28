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

	virtual bool connect(const char *ip, int port, const char *dbName, const char *id, const char *password) = 0;
	virtual bool disconnect() = 0;
	virtual bool isConnected() = 0;

	virtual void run() = 0;
	DBState getState() const { return state; }
};
#endif