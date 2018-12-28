#include "pch.h"
#include "HuffToken.h"

HuffToken::HuffToken(char symbol, size_t freq, std::string code) :
	symbol(symbol), freq(freq), code(code)
{}
