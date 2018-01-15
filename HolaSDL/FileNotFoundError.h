#pragma once
#include "PacManError.h"
class FileNotFoundError: public PacManError
{
public:
	FileNotFoundError(const string& m) : PacManError("Archivo " + m + ".pac no encontrado"){};
	~FileNotFoundError(){};
};

