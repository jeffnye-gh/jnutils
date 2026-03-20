

int main() {
    const std::string host = "localhost";
    const int port = 1234;

    try {
        GDBClient client(host, port);

        // Send a command to query the target status
        client.sendCommand("?");
        client.receiveResponse();  

        // Send a command to read the registers
        client.sendCommand("g");
        client.receiveResponse();

    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

