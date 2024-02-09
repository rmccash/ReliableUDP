
//Filename:		FileVerification.h
//Assignment:	A-01
//Author:		Rhys McCash & Andrew Babos
//Student #:	8825169 & 8822549
//Date:			2/7/2024
//Description:	Contains the function prototypes for the functions in FileVerification.cpp

#pragma once

#include <string>
#include <cstdint>

using namespace std;

namespace file_verification 
{
    uint32_t calculateCRC32(const char* buffer, size_t length);

    bool verifyFileIntegrity(const string& filePath);
} 
