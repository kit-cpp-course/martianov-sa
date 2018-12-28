#include "pch.h"
#include "HuffCompressor.h"

HuffCompressor::HuffCompressor() : huffTree(HuffTree(huffDict)) {}

void HuffCompressor::createHuffDict(File & source)
{
	char symbol;
	while (source.readNextBytes(&symbol))
	{
		huffDict.addSymbol(symbol);
	}
}

void HuffCompressor::writeHuffDict(File & dest)
{
	unsigned char buff = huffDict.size - 1;
	dest.writeNextBytes(reinterpret_cast<char *>(&buff));

	for (size_t i = 0; i < huffDict.size; i++)
	{
		dest.writeNextBytes(&huffDict[i]->symbol);
		dest.writeNextBytes(reinterpret_cast<char *>(&huffDict[i]->freq),
			sizeof(&huffDict[i]->freq));
	}
}

bool HuffCompressor::writeOneSymbol(char symbol, char & lastByte, File & dest)
{
	bool isAllWrited = true;
	for (size_t i = 0; i < huffDict(symbol)->code.length(); i++)
	{
		isAllWrited = dest.writeNextBit(huffDict(symbol)->code[i] - '0', lastByte);
	}
	return isAllWrited;
}

void HuffCompressor::writeCompressedData(File & source, File & dest)
{
	source.rewindToStart();

	char symbol;
	char lastByte = 0;
	bool isAllWrited = true;

	while (source.readNextBytes(reinterpret_cast<char *>(&symbol)))
	{
		isAllWrited = writeOneSymbol(symbol, lastByte, dest);
	}

	dest.finishWriteBits();

	if (!isAllWrited) dest.writeNextBytes(&lastByte);
}

void HuffCompressor::compress(File & source, File & dest)
{
	source.rewindToStart();
	dest.clearData();
	createHuffDict(source);
	huffTree = HuffTree(huffDict);
	writeHuffDict(dest);
	writeCompressedData(source, dest);
}