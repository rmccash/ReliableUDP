#include "FileTransfer.h"

FileTransfer::FileTransfer()
{ // <- error here
    // seems that intantiating a class for access to methods needs
    // to be done in the constructor, except anything i try it doesnt work
    filename = "";
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
        /* Reference:
        line 53: const int PacketSizeHack = 256 + 128; 
        */

        // Reads up to the packetsizehack from earlier labs, and then sends that
        file.read(buffer, PacketSizeHack);
        int bytesRead = file.gcount();
        if (bytesRead > 0) 
        {
            // Send the packet
            connection_.SendPacket((unsigned char*)buffer, bytesRead);
        }
    }

    file.close();
}

void FileTransfer::ReceiveFile(const char* filename, int port)
{

}
