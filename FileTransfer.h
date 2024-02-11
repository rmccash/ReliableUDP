//Filename:		FileTransfer.h
//Assignment:	A-01
//Author:		Rhys McCash & Andrew Babos
//Student #:	8825169 & 8822549
//Date:			2/7/2024
//Description:	Contains the function prototypes for the functions in FileTransfer.cpp

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
#include <chrono>

#include "Net.h"
using namespace std;

class FileTransfer : protected net::ReliableConnection
{
private:

	string filename;

	static const int PacketSizeHack = 256 + 128;
	const int protocolId = 0x11223344;
	const float timeout = 10.0f;

	chrono::high_resolution_clock::time_point startTime;
	chrono::high_resolution_clock::time_point endTime;
	size_t totalBytesTransferred;

public:

	FileTransfer(const char* filename);
	~FileTransfer();

	//void SetFileName(string filename);
	void SendFile(const char* filename);
	void ReceiveFile(const char* filename);

	void DisplayTransferSpeed();
};

#endif