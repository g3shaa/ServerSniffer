#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <sstream>
#include <fstream>
#include <regex>
#include <shellapi.h>

#pragma comment(lib, "ws2_32.lib")

bool IsValidIP(const std::string &ip)
{
    std::regex ipRegex("^(25[0-5]|2[0-4][0-9]|[0-1]?[0-9][0-9]?)\\."
                       "(25[0-5]|2[0-4][0-9]|[0-1]?[0-9][0-9]?)\\."
                       "(25[0-5]|2[0-4][0-9]|[0-1]?[0-9][0-9]?)\\."
                       "(25[0-5]|2[0-4][0-9]|[0-1]?[0-9][0-9]?)$");

    return std::regex_match(ip, ipRegex);
}

void DisplayAsciiArt()
{
    std::cout << R"(
  _____  ________      _______ _    _          _____  ______ 
 |  __ \|  ____\ \    / / ____| |  | |   /\   |  __ \|  ____|
 | |  | | |__   \ \  / / (___ | |__| |  /  \  | |__) | |__   
 | |  | |  __|   \ \/ / \___ \|  __  | / /\ \ |  _  /|  __|  
 | |__| | |____   \  /  ____) | |  | |/ ____ \| | \ \| |____ 
 |_____/|______|   \/  |_____/|_|  |_/_/    \_\_|  \_\______|      


)";
}

std::string GetServerInfo(const std::string &ipAddress, int port)
{
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET)
    {
        std::cerr << "Failed to create socket.\n";
        return "";
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(ipAddress.c_str());
    serverAddr.sin_port = htons(port);

    if (connect(sock, reinterpret_cast<struct sockaddr *>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR)
    {
        std::cerr << "Failed to connect to the server.\n";
        closesocket(sock);
        return "";
    }

    std::string httpRequest = "GET /info.json HTTP/1.1\r\nHost: " + ipAddress + "\r\nConnection: close\r\n\r\n";
    if (send(sock, httpRequest.c_str(), httpRequest.length(), 0) == SOCKET_ERROR)
    {
        std::cerr << "Failed to send HTTP request.\n";
        closesocket(sock);
        return "";
    }

    char buffer[4096];
    std::string serverResponse;

    int bytesRead;
    while ((bytesRead = recv(sock, buffer, sizeof(buffer) - 1, 0)) > 0)
    {
        buffer[bytesRead] = '\0';
        serverResponse += buffer;
    }

    closesocket(sock);
    return serverResponse;
}

void DisplayMenu()
{
    std::cout << "\n=== Menu ===\n";
    std::cout << "1. Display Server Info\n";
    std::cout << "2. Save Server Info to a Text File\n";
    std::cout << "3. Connect to Server\n";
    std::cout << "4. Exit\n";
}

int main()
{
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        std::cerr << "Failed to initialize Winsock.\n";
        return 1;
    }

    DisplayAsciiArt(); 
    std::string ipAddress;
    int port;

    std::cout << "Enter IP address: ";
    std::cin >> ipAddress;

    if (!IsValidIP(ipAddress))
    {
        std::cout << "Invalid IP address.\n";
        WSACleanup();
        return 1;
    }

    std::cout << "Enter port: ";
    std::cin >> port;

    while (true)
    {
        DisplayMenu();

        int choice;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
        {
            std::string serverInfo = GetServerInfo(ipAddress, port);
            if (!serverInfo.empty())
            {
                std::cout << "Server Info:\n"
                          << serverInfo << std::endl;
            }
            break;
        }
        case 2:
        {
            std::string serverInfo = GetServerInfo(ipAddress, port);
            if (!serverInfo.empty())
            {
                std::ofstream outputFile("ServerInfo.txt");
                if (outputFile.is_open())
                {
                    outputFile << "Server Info:\n"
                               << serverInfo << std::endl;
                    outputFile.close();
                    std::cout << "Server Info saved to ServerInfo.txt\n";
                }
                else
                {
                    std::cerr << "Failed to open output file.\n";
                }
            }
            break;
        }
        case 3:
        {
            std::wstringstream connectCommandW;
            connectCommandW << L"connect " << std::wstring(ipAddress.begin(), ipAddress.end()) << L":" << port;
            std::wstring commandString = connectCommandW.str();
            ShellExecuteW(NULL, L"open", L"fivem.exe", commandString.c_str(), NULL, SW_SHOWNORMAL);
            break;
        }
        case 4:
        {
            std::cout << "Exiting program.\n";
            WSACleanup();
            return 0;
        }
        default:
            std::cout << "Invalid choice. Try again.\n";
        }
    }
}