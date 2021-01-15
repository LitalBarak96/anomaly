
//g++ -pthread -std=c++11 Server.cpp
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include "Server.h"
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <thread>
#include <cstring>

static bool serverStop = false;

Server::Server(int port)throw (const char*) {
    fd = socket(AF_INET,SOCK_STREAM,0);
    if(fd<0)
        throw "socket failed";

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    if(bind(fd,(struct sockaddr*)&server,sizeof(server))<0)
        throw "bind failure";
    if(listen(fd,3)<0)
        throw "listen failure";
}

void Server::start(ClientHandler& ch)throw(const char*){
    serverStop = false;
    t = new thread([&ch,this](){
        while(!serverStop) {
            cout << "waiting for a client" << endl;
            socklen_t clientSize = sizeof(client);
            int aClient = accept(fd, (struct sockaddr *) &client, &clientSize);
            if (aClient < 0)
                throw "accept failure";
            cout << "client connected" << endl;
            ch.handle(aClient);
            close(aClient);
            this_thread::sleep_for (chrono::seconds(1));
        }
        close(fd);
    });
}

void Server::stop(){
    serverStop = true;
	t->join(); // do not delete this!
}

Server::~Server() {
}

