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
	return (0 <= key && key <= 255 && huffTokens[key].freq) ? huffTokens + key : 0;
}

HuffToken * HuffDict::operator()(char symbol)
{
	unsigned char i = *reinterpret_cast<unsigned char *>(&symbol);
	return keysBySymbols[i] == -1 ? 0 : huffTokens + keysBySymbols[i];
}

void HuffDict::addHuffToken(char symbol)
{
	unsigned char i = *reinterpret_cast<unsigned char *>(&symbol);
	keysBySymbols[i] = size;
	huffTokens[size++] = HuffToken(symbol, 1);
}

void HuffDict::modifyHuffToken(HuffToken * token)
{
	token->freq++;
	HuffToken * prevToken;
	while (token != huffTokens && (prevToken = token - 1)->freq < token->freq)
	{
		swapHuffTokens(token, prevToken);
	}
}

void HuffDict::swapHuffTokens(HuffToken * a, HuffToken * b)
{
	unsigned char i = *reinterpret_cast<unsigned char *>(&a->symbol);
	unsigned char j = *reinterpret_cast<unsigned char *>(&b->symbol);
	keysBySymbols[i] ^= keysBySymbols[j]
		^= keysBySymbols[i] ^= keysBySymbols[j];
	HuffToken t = *a;
	*a = *b;
	*b = t;
}

void HuffDict::addSymbol(char symbol)
{
	HuffToken * token = (*this)(symbol);
	if (token) modifyHuffToken(token);
	else addHuffToken(symbol);
}
