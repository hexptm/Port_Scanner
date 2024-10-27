#include <winsock2.h>
#include <iostream>

#pragma comment(lib, "ws2_32.lib") 

int initializeWinsock() {
    WSADATA wsaData;
    return WSAStartup(MAKEWORD(2, 2), &wsaData);
}

 bool isPortOpen(const char* ip, int port) {
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) return false;

    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(ip);
    server.sin_port = htons(port);

    bool isOpen = connect(sock, (struct sockaddr*)&server, sizeof(server)) == 0;
    closesocket(sock);
    return isOpen;
}

 void scanPorts(const char* ip, int startPort, int endPort) {
    std::cout << "Scanning ports on " << ip << "...\n";
    for (int port = startPort; port <= endPort; ++port) {
        if (isPortOpen(ip, port)) {
            std::cout << "Port " << port << " is open.\n";
        } else {
            std::cout << "Port " << port << " is closed.\n";
        }
    }
}

 int main() {
    if (initializeWinsock() != 0) {
        std::cerr << "Failed to initialize Winsock.\n";
        return 1;
    }

    const char* ip = "127.0.0.1"; // IP yang ingin dipindai
    int startPort = 1, endPort = 1024; // Rentang port untuk dipindai
    scanPorts(ip, startPort, endPort);

    WSACleanup(); 
    return 0;
}
