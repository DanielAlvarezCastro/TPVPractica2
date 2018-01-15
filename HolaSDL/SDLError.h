#pragma once
#include "PacManError.h"
class SDLError: public PacManError
{
public:
	SDLError(const string& m, const string& e) : PacManError(m+e){};
	~SDLError(){};
};