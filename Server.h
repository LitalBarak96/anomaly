///*
// * Server.h
// *
// *  Created on: Dec 13, 2020
// *      Author: Eli
// */
//
//#ifndef SERVER_H_
//#define SERVER_H_
//
//
//#include <thread>
//#include "CLI.h"
//
//using namespace std;
//
//// edit your ClientHandler interface here:
//class ClientHandler{
//    public:
//    virtual void handle(int clientID)=0;
//};
//
//
//// you can add helper classes here and implement on the cpp file
//
//
//// edit your AnomalyDetectionHandler class here
//class AnomalyDetectionHandler:public ClientHandler{
//	public:
//    virtual void handle(int clientID){
//        SocketIO sio(clientID);
//        CLI cli(&sio);
//        cli.start();
//    }
//};
//
//
//// implement on Server.cpp
//class Server {
//	thread* t; // the thread to run the start() method in
//    int m_socket_fd, m_client_socket_fd;
//    sockaddr_in server;
//    sockaddr_in client;
//    int fd;
//	// you may add data members
//
//public:
//	Server(int port) throw (const char*);
//	virtual ~Server();
//	void start(ClientHandler& ch)throw(const char*);
//	void stop();
//};
//
//#endif /* SERVER_H_ */


/*
 * Server.h
 *
 *  Created on: Dec 13, 2020
 *      Author: Eli
 */

#ifndef SERVER_H_
#define SERVER_H_
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <unistd.h>
#include "CLI.h"

using namespace std;


class ClientHandler{
public:
    virtual void handle(int clientID)=0;
};


class AnomalyDetectionHandler:public ClientHandler{

public:
    virtual void handle(int clientID){
        SocketIO socketIO(clientID);
        CLI cli(&socketIO);
        cli.start();
    }
};

// implement on Server.cpp
class Server {
    thread* t; // the thread to run the start() method in
    int fd;
    struct sockaddr_in server;
    struct sockaddr_in client;

    // you may add data members

public:
    Server(int port) throw (const char*);
    virtual ~Server();
    void start(ClientHandler& ch)throw(const char*);
    void stop();
};

#endif /* SERVER_H_ */
