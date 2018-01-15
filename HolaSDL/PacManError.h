#pragma once
using namespace std;

#include <stdexcept>
class PacManError : public logic_error
{
public:
	PacManError(const string& m) : logic_error("PacMan Error: " + m){};
	virtual ~PacManError(){};
};

