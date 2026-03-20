#include "gdb-server/GdbServer.hpp"
#include "gdb-server/Utils.hpp"
#include "simcontrol.h"

#include <iostream>

int main() {
    int port = 1234;

    // Create a mock simulation control object
    SimControl simControl;

    // Instantiate the GdbServer with the mock simulation 
    // control and port number
    GdbServer server(&simControl, port);

    // Start the server thread (this would typically run indefinitely 
    // in a real implementation)
    server.serverThread();  // Adjust based on actual usage in the library

    return 0;
}

