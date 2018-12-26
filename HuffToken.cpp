#include "pch.h"
#include "HuffToken.h"

HuffToken::HuffToken(unsigned char symbol, size_t freq, std::string code) :
	symbol(symbol), freq(freq), code(code)
{}