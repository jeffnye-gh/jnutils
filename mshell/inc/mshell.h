#pragma once
#include "msg.h"

#if MSHELL_SERVER==1
#include "tcp_server.h"
#include "pipe_ret_t.h"
#endif

#if MSHELL_CLIENT==1
#include "tcp_client.h"
#endif

#include <boost/tokenizer.hpp>
#include <boost/function.hpp>

#include <cstdint>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <ostream>
// =======================================================================
// TODO: 
//    History : should not store bad commands
//    History : should merge identical commands into one entry 
//    
//    - add code to handle application errors from this class (for
//      logging purposes)
// =======================================================================
struct Mshell
{
  typedef boost::tokenizer<boost::char_separator<char> > MsTokenizer;
  typedef boost::function<bool(std::vector<std::string>&)> Cmd;
  typedef std::map<uint32_t,Cmd> CmdMap;
 
  Mshell(std::ostream &o=std::cout);

  ~Mshell(void) {}

  //run the shell, different return types, name changes, etc
  bool run()   { return mshLoop(); }
  int  shell() { if(!run()) return 1; return 0; }

  //run one command
  bool runMshCommand(std::string &);

#if MSHELL_SERVER == 1
  bool runMshCommand(TcpServer&,std::string &);
#endif

  void setCmdMap(CmdMap &m)        { cmdMap    = m; }
  void setShellName(std::string s) { shellName = s; }
  void setPrompt(std::string s)    { prompt    = s; }
  void setMsgVerbose(uint32_t i)   { msg->verbose = i; }
  void setMshEcho(bool b)          { _mshEcho = b; }
  void setMshShowRet(bool b)       { _mshShowRet = b; }

  bool isExit(void);
  bool isScript(void);
  void isScript(bool);
  void bufferReplace(uint32_t,std::string);
  bool reportRet(bool);

  void _msg(std::string m) { msg->msg(m); }
  void dmsg(std::string m) { msg->dmsg(m); }
  void emsg(std::string m) { msg->emsg(m); }
  void emsg(uint32_t);
  void imsg(std::string m) { msg->imsg(m); }
  void wmsg(std::string m) { msg->wmsg(m); }

  enum CMDS
  {
    NO_CMD,                             // 0
    S_EXIT,                             // 1
    S_BANG_EVENT,                       // 2
    S_HISTORY,                          // 3
    S_HELP,                             // 4
    S_SHORT_HELP,                       // 5
    S_VERSION,                          // 6
    S_OS_CMD,                           // 7
    S_UP_ARROW,                         // 8
    S_DWN_ARROW,                        // 9
    S_ECHO,                             //10
    S_RELEASE_NOTES,                    //11
    S_TCP,                              //12

    USER_TYPE
  };

  enum ERRS
  {
    NO_ERR,
    SYNTAX_ERROR,
    EVENT_NOT_FOUND
  };
  
  // Shell commands
  bool shellShowHelp(bool);
  bool shellShowHistory(void);
  bool shellShowReleaseNotes(void);
  bool mshShowVersion(void);
  bool shellTcp(std::vector<std::string>&);

  // Support/helpers
  void echoLB(std::string);
  void tokenize(std::string&,std::vector<std::string>&);
  bool detectAndRunCmd(std::vector<std::string>&);
  bool runBangEvent(std::vector<std::string>&);
  bool isBangEvent(std::string&);

  bool mshLoop();
  bool mshCommand(uint32_t,std::vector<std::string>&);
  void mshExit(void);
  bool mshEcho(std::string);
  void mshIsExiting(void);
  void mshBreakToPrompt(bool b) { _mshBreakToPrompt = b; }

  bool appCommand(uint32_t,std::vector<std::string>&);

  //Server-only functions
#if MSHELL_SERVER==1
  bool tcpStatus();
  bool tcpProperties();
  bool tcpConnections();
  bool tcpClients();
  bool tcpStart();
  bool tcpStop();
  void tcpWaitForClient();

#endif

  //Client-only functions
#if MSHELL_CLIENT==1
  bool tcpClientStatus();
  bool tcpConnect();
  bool tcpSend();
#endif

  void showPrompt(bool newLine=false);

  bool revHistory(void);
  bool fwdHistory(void);
  bool addHistory(std::string);
  bool addHistory(void);

//  void exitRequest();
  bool isFileAccess(void);

  // -----------------------------------------------------------------
  // ctor init
  // -----------------------------------------------------------------
  std::ostream &out;
  std::vector<std::string> history;
  std::vector<std::string> cmdArgs;
  CmdMap cmdMap;

  int ac{0};
  char** av{0};
  // -----------------------------------------------------------------
//  Msg* msg;
  // -----------------------------------------------------------------

  std::string prompt{"m> "};
  std::string cmd{""};
  std::string shellName{"msh"};

  bool _mshBreakToPrompt{false};
  bool _mshEcho{true};
  bool _mshShowRet{true};
  bool _isExit{false};
  bool _isScript{false};

  int  errCode{NO_ERR};
  std::string  errText{""};

  uint32_t historyIndex{0};
  std::string lineBuffer{""};
  uint32_t bufferPos{0};
  bool ncursesEnable{false};

  //TCP vars
  bool tcpInitialized{false};
  uint32_t tcpMshellPort{65123};
  pid_t    tcpListenPid{-1};

#if MSHELL_SERVER == 1
  std::vector<uint32_t> clients;
//  pipe_ret_t startPipe;
#endif

  static const std::string MSHELL_VERSION;
  static std::vector<std::string> helpVec;
  static std::vector<std::string> relNotesVec;
  static std::vector<std::string> versionVec;
};
