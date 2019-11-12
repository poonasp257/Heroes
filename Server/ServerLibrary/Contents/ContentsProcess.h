#ifndef CONTENTS_PROCESS_H
#define CONTENTS_PROCESS_H

class ContentsProcess {
private:
    std::queue<Package*> packageQueue;
    HANDLE               processThreads[3]; // thread pool...
    //array<Thread, 10> threadPool;

private:
    void execute();

protected:
    virtual void run(Package *package) = 0; // hash map을 이용해서 PacketType과 함수를 pair로 묶기

public:
    ContentsProcess();
    ~ContentsProcess();
    
    static unsigned int WINAPI process(LPVOID lpParam); 

    void putPackage(Package *package);
};

#endif