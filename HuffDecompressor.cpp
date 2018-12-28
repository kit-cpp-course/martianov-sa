#include "pch.h"
#include "HuffDecompressor.h"

HuffDecompressor::HuffDecompressor() : huffTree(HuffTree(huffDict)) {}

void HuffDecompressor::createHuffDict(File & source)
{
	unsigned char buff;
	source.readNextBytes(reinterpret_cast<char *>(&buff));
	size_t n = buff + 1;

	char symbol;
	for (size_t i = 0; i < n; i++)
	{
		source.readNextBytes(&symbol);
		huffDict.addSymbol(symbol);
		source.readNextBytes(reinterpret_cast<char *>(&huffDict(symbol)->freq),
			sizeof(huffDict(symbol)->freq));
	}
}

void HuffDecompressor::writeOnlyFirstSymbol(File & dest)
{
	while (freqs[huffDict[0]->symbol]--)
	{
		dest.writeNextBytes(&huffDict[0]->symbol);
	}
}

void HuffDecompressor::writeOneSymbol(HuffTree & T, File & dest)
{
	unsigned char i = *reinterpret_cast<unsigned char *>(&T.value.symbol);
	if (!freqs[i]) return;
	dest.writeNextBytes(&T.value.symbol);
	freqs[i]--;
}

void HuffDecompressor::fillFreqs()
{
	unsigned char k;
	for (size_t i = 0; i < huffDict.size; i++)
	{
		k = *reinterpret_cast<unsigned char *>(&huffDict[i]->symbol);
		freqs[k] = huffDict[i]->freq;
	}
}

void HuffDecompressor::writeAllSymbols(File & source, File & dest)
{
	char bit;
	HuffTree * T = &huffTree;
	
	while (source.readNextBit(bit))
	{
		if (bit) T = static_cast<HuffTree *>(T->right);
		else T = static_cast<HuffTree *>(T->left);
		if (!T->left && !T->right)
		{
			writeOneSymbol(*T, dest);
			T = &huffTree;
		}
	}

	source.finishReadBits();
}

void HuffDecompressor::writeDecompressedData(File & source, File & dest)
{
	fillFreqs();
	if (huffDict.size == 1) writeOnlyFirstSymbol(dest);
	else writeAllSymbols(source, dest);
}

void HuffDecompressor::decompress(File & source, File & dest)
{
	source.rewindToStart();
	dest.clearData();
	createHuffDict(source);
	huffTree = HuffTree(huffDict);
	writeDecompressedData(source, dest);
}
