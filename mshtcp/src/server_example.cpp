// Server test top level
#include "tcp_server.h"
#include <iostream>
#include <signal.h>
using namespace std;
// -------------------------------------------------------------------------
// declare the server
// -------------------------------------------------------------------------
TcpServer server;

// -------------------------------------------------------------------------
// declare a server observer which will receive incoming messages.
// the server supports multiple observers
// -------------------------------------------------------------------------
server_observer_t observer1, observer2;

// -------------------------------------------------------------------------
// observer callback. will be called for every new message received by clients
// with the requested IP address
// -------------------------------------------------------------------------
void onIncomingMsg1(const Client & client, const char * msg, size_t size) {
    string msgStr = msg;
    // print the message content
    cout << "Observer1 got client msg: " << msgStr << endl;
    // if client sent the string "quit", close server
    // else if client sent "print" print the server clients
    // else just print the client message
    if (msgStr.find("quit") != string::npos) {
        cout << "Closing server..." << endl;
        pipe_ret_t finishRet = server.finish();
        if (finishRet.success) {
            cout << "Server closed." << endl;
        } else {
            cout << "Failed closing server: " << finishRet.msg << endl;
        }
    } else if (msgStr.find("print") != string::npos){
        server.printClients();
    } else {
        string replyMsg = "server got this msg: "+ msgStr;
        server.sendToAllClients(replyMsg.c_str(), replyMsg.length());
    }
}

// -------------------------------------------------------------------------
// observer callback. will be called for every new message received by clients
// with the requested IP address
// -------------------------------------------------------------------------
void onIncomingMsg2(const Client & client, const char * msg, size_t size) {
    string msgStr = msg;
    // print client message
    cout << "Observer2 got client msg: " << msgStr << endl;

    // reply back to client
    string replyMsg = "server got this msg: "+ msgStr;
    server.sendToClient(client, msg, size);
}

// -------------------------------------------------------------------------
// observer callback. will be called when client disconnects
// -------------------------------------------------------------------------
void onClientDisconnected(const Client & client) {
  cout << "Client: " << client.getIp()
       << " disconnected: " << client.getInfoMessage() << endl;
}
// --------------------------------------------------------------------------
// --------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  // start server on port 65123
  pipe_ret_t startRet = server.start(65123);
  if (startRet.success) {
        cout << "Server setup succeeded" << endl;
  } else {
        cout << "Server setup failed: " << startRet.msg << endl;
        return EXIT_FAILURE;
  }

  // configure and register observer1
  observer1.incoming_packet_func = onIncomingMsg1;
  observer1.disconnected_func = onClientDisconnected;
  observer1.wantedIp = "127.0.0.1";
  server.subscribe(observer1);

  // configure and register observer2
  observer2.incoming_packet_func = onIncomingMsg2;
  //don't care about disconnection
  observer1.disconnected_func = nullptr;
  // use empty string instead to receive messages from any IP address
  observer2.wantedIp = "10.88.0.11"; 
  server.subscribe(observer2);

  // receive clients
  while(1) {
    Client client = server.acceptClient(0);

    if (client.isConnected()) {
      cout << "Got client with IP: " << client.getIp() << endl;
      server.printClients();
    } else {
      cout << "Accepting client failed: " << client.getInfoMessage() << endl;
    }

    sleep(1);

  }

  return 0;
}
