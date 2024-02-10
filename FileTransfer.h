
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

#include "Net.h"

class FileTransfer : protected net::ReliableConnection
{
private:

	string filename;

	static const int PacketSizeHack = 256 + 128;
	const int protocolId = 0x11223344;
	const float timeout = 10.0f;

public:

	FileTransfer(string filename);
	~FileTransfer();

	void SendFile(const char* filename, const char* address, int port);
	void ReceiveFile(const char* filename, int port);
};

#endif