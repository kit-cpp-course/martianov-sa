#pragma once
#include "File.h"

// ����������� ����� ����������� �������� ������.
class Decompressor
{
public:
	// �����, ������������ �������� ������ �� ����� source � ������������ ������ ������ � ���� dest.
	virtual void decompress(File & source, File & dest) = 0;
};
