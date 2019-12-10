#ifndef TERMINALMANAGER_H
#define TERMINALMANAGER_H

class TerminalManager : public Singleton<TerminalManager> {
private:
	Server *server;
	std::unordered_map<std::string, Terminal*> terminalPool;

public:
	TerminalManager();
	virtual ~TerminalManager();

	void initialize();
	void run(Server *server);

	Terminal* getTerminal(const std::string& name);
};
#endif