#pragma once
#include "GameObject.h"

class PlayState;
class PacManObject: public GameObject
{
protected:
	PlayState* pState;
public:
	PacManObject(Game* g, PlayState* pS);
	~PacManObject();
	virtual void saveToFile(ofstream& archivo) = 0;
	virtual void loadFromFile(ifstream& archivo) = 0;
};

