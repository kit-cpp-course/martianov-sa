#include "pch.h"
#include "file.h"

using namespace std;

File::File(string source, mode access) :
	fileName(source), access(access), writeBitPos(0), readBitPos(0)
{	
	f.open(source, access);
}

File::~File()
{
	f.close();
}

bool File::readNextBytes(char * bytes, size_t numOfBytes)
{
	return  f.read(bytes, numOfBytes) ? true : false;
}

bool File::writeNextBytes(char * bytes, size_t numOfBytes)
{
	return  f.write(bytes, numOfBytes) ? true : false;
}

bool File::readNextBit(char & bit)
{
	static char byte;

	if (readBitPos == 0)
	{
		if (!this->readNextBytes(&byte)) return false;
		readBitPos = 8;
	}
	
	bit = byte >> (8 - readBitPos--) & 1;

	return true;
}

bool File::writeNextBit(char bit, char & lastByte)
{
	lastByte |= bit << writeBitPos++;

	if (writeBitPos == 8)
	{
		if (!this->writeNextBytes(&lastByte)) return false;
		lastByte = writeBitPos = 0;
	}

	return !writeBitPos;
}

void File::finishReadBits()
{
	writeBitPos = 0;
}

void File::finishWriteBits()
{
	readBitPos = 0;
}

void File::rewindToStart()
{
	this->f.clear();
	this->f.seekg(0, ios::beg);
	writeBitPos = readBitPos = 0;
}

void File::clearData()
{
	f.close();
	f.open(fileName, access | ios::trunc);

	writeBitPos = readBitPos = 0;
}