#include "pch.h"
#include "HuffDict.h"


HuffDict::HuffDict() :
	keysBySymbols(new short[256]), huffTokens(new HuffToken[256]), size(0)
{
	for (size_t i = 0; i < 256; i++) keysBySymbols[i] = -1;
}


HuffDict::~HuffDict()
{
	if (keysBySymbols) delete[] keysBySymbols;
	if (huffTokens) delete[] huffTokens;
}

HuffToken * HuffDict::operator[](short key)
{
	return 0 <= key && key <= 255 && huffTokens[key].freq ? huffTokens + key : 0;
}

HuffToken * HuffDict::operator()(char symbol)
{
	return keysBySymbols[uchar(symbol)] == -1 ? 0 : huffTokens + keysBySymbols[uchar(symbol)];
}

void HuffDict::addHuffToken(char symbol)
{
	keysBySymbols[uchar(symbol)] = size;
	huffTokens[size++] = HuffToken(symbol, 1);
}

void HuffDict::modifyHuffToken(HuffToken * token)
{
	token->freq++;
	HuffToken * prevToken;
	while (token != huffTokens && (prevToken = token - 1)->freq < token->freq)
	{
		swapHuffTokens(*token, *prevToken);
	}
}

void HuffDict::swapHuffTokens(HuffToken & a, HuffToken & b)
{
	keysBySymbols[uchar(a.symbol)] ^= keysBySymbols[uchar(b.symbol)]
		^= keysBySymbols[uchar(a.symbol)] ^= keysBySymbols[uchar(b.symbol)];
	HuffToken t = a;
	a = b;
	b = t;
}

void HuffDict::addSymbol(char symbol)
{
	HuffToken * token = (*this)(symbol);
	if (token) modifyHuffToken(token);
	else addHuffToken(symbol);
}

unsigned char HuffDict::uchar(char & a)
{
	return *reinterpret_cast<unsigned char *>(&a);
}

HuffDict::HuffDict(const HuffDict & that)
{
	copy(that);
}

HuffDict & HuffDict::operator=(const HuffDict & that)
{
	if (keysBySymbols) delete[] keysBySymbols;
	if (huffTokens) delete[] huffTokens;
	copy(that);
	return *this;
}

void HuffDict::copy(const HuffDict & source)
{
	this->size = source.size;
	for (size_t i = 0; i < 256; i++)
	{
		this->keysBySymbols[i] = source.keysBySymbols[i];
		this->huffTokens[i] = source.huffTokens[i];
	}
}