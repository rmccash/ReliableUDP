
#pragma once

#ifndef FILETRANSFER_H
#define FILETRANSFER_H

#include <winsock2.h>
#pragma comment( lib, "wsock32.lib" )

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <list>
#include <algorithm>
#include <functional>

class FileTransfer
{
private:

	string filename;

	static const int PacketSizeHack = 256 + 128;

public:

	void SendFile(const char* filename, const char* address, int port);

	void ReceiveFile(const char* filename, int port);
};

#endif