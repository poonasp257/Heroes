#include "stdafx.h"
#include "server.h"

Server::Server() {
	status = ServerStatus::Stop;


	this->Initialize();
}

Server::~Server() {
}

void Server::Initialize() {

}