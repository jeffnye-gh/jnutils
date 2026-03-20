#include <iostream>
#include <string>
#include <cstring>
#include <netdb.h>
#include <unistd.h>
#include <sstream>
#include <iomanip>

class GDBClient {
public:
    GDBClient(const std::string& host, int port)
        : server_fd(-1) {
        // Create socket
        server_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (server_fd == -1) {
            std::cerr << "Failed to create socket\n";
            exit(EXIT_FAILURE);
        }

        // Resolve the server address
        struct hostent* server = gethostbyname(host.c_str());
        if (server == nullptr) {
            std::cerr << "No such host: " << host << "\n";
            exit(EXIT_FAILURE);
        }

        // Set up the server address structure
        struct sockaddr_in server_addr {};
        server_addr.sin_family = AF_INET;
        std::memcpy(&server_addr.sin_addr.s_addr, server->h_addr, server->h_length);
        server_addr.sin_port = htons(port);

        // Connect to the server
        if (connect(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
            std::cerr << "Failed to connect to the server\n";
            exit(EXIT_FAILURE);
        }

        std::cout << "Connected to GDB RSP server at " << host << ":" << port << "\n";
    }

    ~GDBClient() {
        if (server_fd != -1) {
            close(server_fd);
        }
    }

    void sendCommand(const std::string& command) {
        // Format the command with $<command>#<checksum>
        std::string packet = "$" + command + "#" + calculateChecksum(command);
        // Send the packet
        if (write(server_fd, packet.c_str(), packet.size()) < 0) {
            std::cerr << "Failed to send command\n";
        }
        std::cout << "Sent command: " << packet << "\n";
    }

    std::string receiveResponse() {
        // Read the response
        char buffer[1024];
        std::memset(buffer, 0, sizeof(buffer));
        ssize_t len = read(server_fd, buffer, sizeof(buffer) - 1);
        if (len < 0) {
            std::cerr << "Failed to receive data from server\n";
            return "";
        }

        // Process the response
        std::string response(buffer, len);
        std::cout << "Received response: " << response << "\n";
        return response;
    }

private:
    int server_fd;

    // Calculate the checksum for the GDB RSP command
    std::string calculateChecksum(const std::string& data) {
        unsigned char checksum = 0;
        for (char c : data) {
            checksum += c;
        }
        std::stringstream ss;
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(checksum);
        return ss.str();
    }
};

