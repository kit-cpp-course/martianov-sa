#include "pch.h"
#include "HuffDecompressor.h"

HuffDecompressor::HuffDecompressor() :
	huffDict(new HuffDict()), huffTree(0), freqs(new size_t[256]{ 0 })
{}

HuffDecompressor::~HuffDecompressor()
{
	if (huffDict) delete huffDict;
	if (huffDict) delete huffTree;
	if (freqs) delete[] freqs;
}

void HuffDecompressor::createHuffDict(File * source)
{
	unsigned char buff;
	source->readNextBytes(reinterpret_cast<char *>(&buff));
	size_t n = buff + 1;

	char symbol;
	for (size_t i = 0; i < n; i++)
	{
		source->readNextBytes(&symbol);
		huffDict->addSymbol(symbol);
		source->readNextBytes(reinterpret_cast<char *>(&(*huffDict)(symbol)->freq),
			sizeof((*huffDict)(symbol)->freq));
	}
}

void HuffDecompressor::writeOnlyFirstSymbol(File * dest)
{
	while (freqs[(*huffDict)[0]->symbol]--)
	{
		dest->writeNextBytes(&(*huffDict)[0]->symbol);
	}
}

void HuffDecompressor::writeOneSymbol(HuffTree * T, File * dest)
{
	if (!freqs[T->value->symbol]) return;
	dest->writeNextBytes(&T->value->symbol);
	freqs[(*huffDict)[0]->symbol]--;
}

void HuffDecompressor::fillFreqs()
{
	unsigned char k;
	for (size_t i = 0; i < huffDict->size; i++)
	{
		k = *reinterpret_cast<unsigned char *>(&(*huffDict)[i]->symbol);
		freqs[k] = (*huffDict)[i]->freq;
	}
}

void HuffDecompressor::writeAllSymbols(File * source, File * dest)
{
	char bit;
	HuffTree * T = huffTree;
	
	while (source->readNextBit(bit))
	{
		if (bit) T = static_cast<HuffTree *>(T->right);
		else T = static_cast<HuffTree *>(T->left);
		if (!T->left && !T->right)
		{
			writeOneSymbol(T, dest);
			T = huffTree;
		}
	}

	source->finishReadBits();
}

void HuffDecompressor::writeDecompressedData(File * source, File * dest)
{
	fillFreqs();

	if (huffDict->size == 1) writeOnlyFirstSymbol(dest);
	else writeAllSymbols(source, dest);
}

void HuffDecompressor::decompress(File * source, File * dest)
{
	source->rewindToStart();
	dest->clearData();
	createHuffDict(source);
	huffTree = new HuffTree(*huffDict);
	writeDecompressedData(source, dest);
}
