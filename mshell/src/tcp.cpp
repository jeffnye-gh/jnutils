// --------------------------------------------------------------------
// Jeff Nye (c) 2023, see jnutils/LICENSE and jnutils/README.md
// --------------------------------------------------------------------
#include "mshell.h"
extern Mshell* MSH;
// --------------------------------------------------------
// --------------------------------------------------------
#if MSHELL_CLIENT == 1
#include <signal.h>
TcpClient client;
#endif

#if MSHELL_SERVER == 1
TcpServer server;
server_observer_t observer;
#endif

using namespace std;
// --------------------------------------------------------
// --------------------------------------------------------
#if MSHELL_CLIENT == 1
void sig_exit(int s)
{
  std::cout << "Closing client..." << std::endl;
  pipe_ret_t finishRet = client.finish();
  if (finishRet.success) {
    std::cout << "Client closed." << std::endl;
  } else {
    std::cout << "Failed to close client." << std::endl;
  }
  exit(0);
}
#endif
// --------------------------------------------------------
// --------------------------------------------------------
#if MSHELL_CLIENT == 1
void onIncomingMsg(const char * msg, size_t size) {
  std::cout << "Got msg from server: " << msg << std::endl;
}
#endif
// -----------------------------------------------------------------------------
// observer callback. will be called when server disconnects
// -----------------------------------------------------------------------------
#if MSHELL_CLIENT == 1
void onDisconnection(const pipe_ret_t & ret) {
  std::cout << "Server disconnected: " << ret.msg << std::endl;
  std::cout << "Closing client..." << std::endl;
    pipe_ret_t finishRet = client.finish();
  if (finishRet.success) {
    std::cout << "Client closed." << std::endl;
  } else {
    std::cout << "Failed to close client: " << finishRet.msg << std::endl;
  }
}
#endif
// ==============================================================================
// COMBINED
// ==============================================================================
bool Mshell::shellTcp(vector<string> &v)
{
  if(v.size() < 2) {
    emsg("tcp command requires at least 2 arguments");
    return false;
  }

#if MSHELL_SERVER == 1
  if(v[1] == "status")      { return tcpStatus(); }
  if(v[1] == "stop")        { return tcpStop(); }
  if(v[1] == "start")       { return tcpStart(); }
  if(v[1] == "properties")  { return tcpProperties(); }
  if(v[1] == "connections") { return tcpConnections(); }
  if(v[1] == "clients")     { return tcpClients(); }
  emsg("server: TCP command fall through");
#endif

#if MSHELL_CLIENT == 1
  if(v[1] == "clientstatus") { return tcpClientStatus(); }
  if(v[1] == "connect")      { return tcpConnect(); }
  if(v[1] == "send")         { return tcpSend(); }
  emsg("client: TCP command fall through");
#endif

  return false;
}
// --------------------------------------------------------
// --------------------------------------------------------
#if MSHELL_CLIENT == 1
bool Mshell::tcpConnect()
{
  signal(SIGINT, sig_exit);
  client_observer_t observer;
  observer.wantedIp = "127.0.0.1";
  observer.incoming_packet_func = onIncomingMsg;
  observer.disconnected_func = onDisconnection;
  client.subscribe(observer);
  pipe_ret_t connectRet = client.connectTo("127.0.0.1", 65123);
  if (connectRet.success) {
    std::cout << "Client connected successfully" << std::endl;
  } else {
    std::cout << "Client failed to connect: " << connectRet.msg << std::endl;
    return EXIT_FAILURE;
  }

  imsg("tcp connection complete");
  return true;
}
#endif
// --------------------------------------------------------
// --------------------------------------------------------
#if MSHELL_CLIENT == 1
bool Mshell::tcpClientStatus()
{
  imsg("info tcpClientStatus()");
  return true;
}
#endif
// --------------------------------------------------------
// --------------------------------------------------------
#if MSHELL_CLIENT == 1
bool Mshell::tcpSend()
{
  std::string msg = "info context all\n";
//  std::string msg = "hello server\n";
  pipe_ret_t sendRet = client.sendMsg(msg.c_str(), msg.size());
  if (!sendRet.success) {
    std::cout << "Failed to send msg: " << sendRet.msg << std::endl;
    return false;
  }

  imsg("tcpSend()");
  return true;
}
#endif
// =============================================================================
// SERVER:
// =============================================================================
#if MSHELL_SERVER == 1
void tcpPacketFromClient(const Client& client,const char* msg,size_t size)
{
  string msgStr = msg;
  // print the message content
  cout << "server: Observer1 got client msg: " << msgStr << endl;
  // if client sent the string "quit", close server
  // else if client sent "print" print the server clients
  // else just print the client message
  if (msgStr.find("quit") != string::npos) {
    cout << "server: Closing server..." << endl;
    pipe_ret_t finishRet = server.finish();
    if (finishRet.success) {
      cout << "server: Server closed." << endl;
      return;
    } else {
      cout << "server: Failed closing server: " << finishRet.msg << endl;
      return;
    }
  } else if (msgStr.find("print") != string::npos){
    server.printClients();
    return;
  } else {
    string replyMsg = "server: reply message "+ msgStr;
    server.sendToAllClients(replyMsg.c_str(), replyMsg.length());
    MSH->runMshCommand(server,msgStr);
//    runCommand(server,msgStr);
    return;
  }

  MSH->runMshCommand(msgStr);
//  runCommand(msgStr);
}
#endif
// --------------------------------------------------------
// --------------------------------------------------------
#if MSHELL_SERVER == 1
void tcpClientDisconnect(const Client & client) {
  cout << "server: Client: " << client.getIp()
       << " disconnected: " << client.getInfoMessage() << endl;
}
#endif
// --------------------------------------------------------
// --------------------------------------------------------
#if MSHELL_SERVER == 1
bool Mshell::tcpStatus()
{
  if(!tcpInitialized ) {
    emsg("server: tcp connection has not been initialized");
    return true; //this is not an error with this usage
  }

  if(!tcpProperties())  return false;
  if(!tcpConnections()) return false;
  if(!tcpClients())     return false;
  return true;
}
#endif
// --------------------------------------------------------
// --------------------------------------------------------
#if MSHELL_SERVER == 1
bool Mshell::tcpStop()
{
  server.finish();
  imsg("server: tcp stop complete\n");
  return true;
}
#endif
// --------------------------------------------------------
// --------------------------------------------------------
#if MSHELL_SERVER == 1
bool Mshell::tcpStart()
{
    pipe_ret_t startPipe = server.start(tcpMshellPort);

  if(!startPipe.success) {
    emsg("server: tcp start up failed with '"+startPipe.msg+"'");
    return false;
  }

  observer.incoming_packet_func = tcpPacketFromClient;
  observer.disconnected_func    = tcpClientDisconnect;
  observer.wantedIp             = "127.0.0.1";
  server.subscribe(observer);

  tcpInitialized = true;

  tcpWaitForClient();
  imsg("server: tcp start complete\n");
  return true;
}
#endif
// --------------------------------------------------------
// --------------------------------------------------------
#if MSHELL_SERVER == 1
void Mshell::tcpWaitForClient()
{
  imsg("server: tcp waiting for client");

  while(1) {
    Client client = server.acceptClient(0);

    if (client.isConnected()) {
      cout << "server: Got client with IP: " << client.getIp() << endl;
      server.printClients();
      return;
    } else {
      cout << "server: Accepting client failed: " << client.getInfoMessage() << endl;
    }

    sleep(1);
  }
}
#endif
// --------------------------------------------------------
// --------------------------------------------------------
#if MSHELL_SERVER == 1
bool Mshell::tcpProperties()
{
  imsg("server: info tcpProperties\n");
  return true;
}
#endif
// --------------------------------------------------------
// --------------------------------------------------------
#if MSHELL_SERVER == 1
bool Mshell::tcpConnections()
{
  imsg("server: info tcpConnections\n");
  return true;
}
#endif
// --------------------------------------------------------
// --------------------------------------------------------
#if MSHELL_SERVER == 1
bool Mshell::tcpClients()
{
  imsg("server: info tcpClients\n");
  return true;
}
#endif
