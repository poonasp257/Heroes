#include "stdafx.h"

ContentsProcess::ContentsProcess() {
    for(int i = 0; i < 1; ++i) {
        processThreads[i] = (HANDLE)_beginthreadex(NULL, 0, process, this, 0, NULL);
    }
}

ContentsProcess::~ContentsProcess() {
    
}

unsigned int WINAPI ContentsProcess::process(LPVOID lpParam) {
    ContentsProcess *process = (ContentsProcess*)lpParam;

    while(true) {
        process->execute();
    }
}

void ContentsProcess::execute() {
    if(packageQueue.empty()) return;

    Package * package = packageQueue.front();
    packageQueue.pop();

    this->run(package);
}

void ContentsProcess::putPackage(Package *package) {
    packageQueue.push(package);
}    