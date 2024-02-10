
#include "FileTransfer.h"
#include "Net.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

FileTransfer::FileTransfer(string filename) : net::ReliableConnection(protocolId, timeout)
{ 
    this->filename = filename;
}

FileTransfer::~FileTransfer()
{
    cout << "FileTransfer destroyed" << endl;
}

void FileTransfer::SendFile(const char* filename, const char* address, int port)
{
    // create holder
    ifstream file(filename, ios::binary);

    // if no file was found
    if (!file)
    {
        cerr << "Error opening file" << endl;
        return;
    }

    char buffer[PacketSizeHack]; // temp holder

    // Read each byte and send it to the client
    while (!file.eof())
    {
        // Reads up to the packetsizehack from earlier labs, and then sends that
        file.read(buffer, PacketSizeHack);
        int bytesRead = file.gcount();
        if (bytesRead > 0)
        {
            // Send the packet
            SendPacket((unsigned char*)buffer, bytesRead);
        }
    }

    file.close();
}

void FileTransfer::ReceiveFile(const char* filename, int port)
{

}