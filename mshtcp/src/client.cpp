// ---------------------------------------------------------------------------
// Derived from the original code ceated by erauper on 4/7/19.
// See https://github.com/elhayra/tcp_server_client
// Subsequently modified for my use
// --------------------------------------------------------------------
// Modifications: Jeff Nye (c) 2023, see jnutils/LICENSE and jnutils/README.md
// ---------------------------------------------------------------------------
#include "client.h"
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
Client::~Client() {
  if (m_threadHandler != nullptr) {
    m_threadHandler->detach();
    delete m_threadHandler;
    m_threadHandler = nullptr;
  }
}
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
bool Client::operator ==(const Client & other)
{
  if ( (this->m_sockfd == other.m_sockfd) && (this->m_ip == other.m_ip) ) {
    return true;
  }

  return false;
}
