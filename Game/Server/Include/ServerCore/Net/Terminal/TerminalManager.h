#ifndef TERMINALMANAGER_H
#define TERMINALMANAGER_H

class TerminalManager : public Singleton<TerminalManager> {
private:
	Server *server;
	std::vector<std::pair<std::wstring, Terminal*>> terminalPool;

public:
	TerminalManager();
	virtual ~TerminalManager();

	void initialize();
	void run(Server *server);

	Terminal* getTerminal(const std::wstring& name);
	Terminal* getTerminal(int index);

	size_t getTerminalCount() const { return terminalPool.size(); }
};
#endif