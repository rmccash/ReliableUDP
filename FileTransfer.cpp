
//Filename:		FileTransfer.cpp
//Assignment:	A-01
//Author:		Rhys McCash & Andrew Babos
//Student #:	8825169 & 8822549
//Date:			2/7/2024
//Description:	Contains the function prototypes for the functions in FileVerification.cpp


#include "FileTransfer.h"
#include "Net.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


/*
* FUNCTION : FileTransfer(const char* filename) : net::ReliableConnection(protocolId, timeout)
* DESCRIPTION: Constructor for FileTransfer class. Ability to access methods
*				that assist with file unpack to view or file transfer
* Parameters: const char* filename
* Returns: none
*/
FileTransfer::FileTransfer(const char* filename) : net::ReliableConnection(protocolId, timeout)
{
    //this->filename = filename;
    this->filename = filename;
	totalBytesTransferred = 0;
}

FileTransfer::~FileTransfer()
{
    cout << "FileTransfer destroyed" << endl;
}

//
//void FileTransfer::SetFileName(string filename)
//{
//	//this->filename = filename;
//}


/*
* FUNCTION : SendFile()
* DESCRIPTION: Server side method, when the client and server
*				connect, the server reads through the file adn sends the data
*				through packets
* Parameters: const char* filename
* Returns: none
*/
void FileTransfer::SendFile(const char* filename)
{
    // open binary file
    ifstream file(filename, ios::binary);

    // if no file was found
    if (!file)
    {
        cerr << "Error opening file" << endl;
        return;
    }

    char packet[PacketSizeHack]; // packet we're sending

	startTime = chrono::high_resolution_clock::now();

    // Read each byte and send it to the client
    while (!file.eof())
    {
        // Reads up to the packetsizehack from earlier labs, and then sends that
        file.read(packet, PacketSizeHack);
        int bytesRead = file.gcount();
        if (bytesRead > 0)
        {
            // Send the packet (data in binary)
            SendPacket((unsigned char*)packet, bytesRead);
        }

		totalBytesTransferred += bytesRead;
    }

	endTime = chrono::high_resolution_clock::now();

    file.close();
}


/*
* FUNCTION : ReceiveFile()
* DESCRIPTION: Client side method. This is used when the server and client connect
*				After reading to the PacketSizeHack limit, it then sends that
*				packet to the client for reassmble
* Parameters: const char* filename
* Returns: none
*/
void FileTransfer::ReceiveFile(const char* filename)
{
	// create holder
	ofstream file(filename, ios::binary);

	//// if no file was found
	//if (!file)
	//{
	//	cerr << "Error opening file" << endl;
	//	return;
	//}

	unsigned char packet[PacketSizeHack]; // temp holder

	startTime = chrono::high_resolution_clock::now();

	// Read each byte and send it to the client
	while (true)
	{
		// Receive the packet
		int bytesRead = ReceivePacket(packet, PacketSizeHack);
		if (bytesRead > 0)
		{
			// Write the packet to the file
			//file.write(packet, bytesRead);
			printf("%d", bytesRead);
		}
		else
		{
			break;
		}

		totalBytesTransferred += bytesRead;
	}

	//file.close();
	endTime = chrono::high_resolution_clock::now();

	file.close();
}


/*
* FUNCTION : DisplayTransferSpeed()
* DESCRIPTION: Calculates the transfer time as well as the
*				Megabits/second travel speed
* Parameters: none
* Returns: none
*/
void FileTransfer::DisplayTransferSpeed()
{
	chrono::duration<double> duration = endTime - startTime;

	double transferTimeSeconds = duration.count();

	double transferSpeedMbps = (totalBytesTransferred * 8) / (transferTimeSeconds * 1024 * 1024);

	cout << "Transfer Speed: " << transferSpeedMbps << " Mbps" << endl;
}
