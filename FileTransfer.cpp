#include "FileTransfer.h"
#include "Net.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

FileTransfer::FileTransfer(string filename) : net::ReliableConnection(protocolId, timeout)
{
    this->filename = filename;
	totalBytesTransferred = 0;
}

FileTransfer::~FileTransfer()
{
    cout << "FileTransfer destroyed" << endl;
}

void FileTransfer::SendFile(const char* filename, const char* address, int port)
{
    // open binary file
    ifstream file(filename, ios::binary);

    // if no file was found
    if (!file)
    {
        cerr << "Error opening file" << endl;
        return;
    }

    char packet[PacketSizeHack]; // temp holder

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

void FileTransfer::ReceiveFile(const char* filename, int port)
{
	// create holder
	ofstream file(filename, ios::binary);

	// if no file was found
	if (!file)
	{
		cerr << "Error opening file" << endl;
		return;
	}

	char buffer[PacketSizeHack]; // temp holder

	startTime = chrono::high_resolution_clock::now();

	// Read each byte and send it to the client
	while (true)
	{
		// Receive the packet
		int bytesRead = ReceivePacket((unsigned char*)buffer, PacketSizeHack);
		if (bytesRead > 0)
		{
			// Write the packet to the file
			file.write(buffer, bytesRead);
		}
		else
		{
			break;
		}

		totalBytesTransferred += bytesRead;
	}

	endTime = chrono::high_resolution_clock::now();

	file.close();
}

void FileTransfer::DisplayTransferSpeed()
{
	chrono::duration<double> duration = endTime - startTime;

	double transferTimeSeconds = duration.count();

	double transferSpeedMbps = (totalBytesTransferred * 8) / (transferTimeSeconds * 1024 * 1024);

	cout << "Transfer Speed: " << transferSpeedMbps << " Mbps" << endl;
}
