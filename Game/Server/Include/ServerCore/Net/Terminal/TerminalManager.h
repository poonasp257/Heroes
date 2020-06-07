#ifndef TERMINALMANAGER_H
#define TERMINALMANAGER_H

class Server;
class Terminal;

class TerminalManager {
private:
	std::vector<std::pair<std::wstring, std::unique_ptr<Terminal>>> terminalPool;

private:
	TerminalManager();
	TerminalManager(TerminalManager&&) = delete;
	TerminalManager(const TerminalManager&) = delete;
	~TerminalManager();

	TerminalManager& operator=(TerminalManager&&) = delete;
	TerminalManager& operator=(const TerminalManager&) = delete;

public:
	bool initialize(std::shared_ptr<Server> server);
	bool run();

	void stopAll();

	Terminal* getTerminal(const std::wstring& name);
	Terminal* getTerminal(int index);

	size_t getTerminalCount() const { terminalPool.size(); }
	size_t getConnectedTerminalCount() const;

	static auto& Instance() {
		static TerminalManager instance;
		return instance;
	}
};
#endif