#include "client.h"

#include <boost/asio.hpp>
#include <iostream>
#include <string>

using boost::asio::ip::tcp;

int main() {
  Client client;
  return client.connect();
}

