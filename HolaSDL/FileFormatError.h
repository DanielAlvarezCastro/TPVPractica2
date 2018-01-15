#pragma once
#include "PacManError.h"
class FileFormatError : public PacManError
{
public:
	FileFormatError(const string& m) : PacManError("Error de cargado-> " + m){};
	~FileFormatError(){};
};

