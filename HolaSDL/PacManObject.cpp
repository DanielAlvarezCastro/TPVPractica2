#include "PacManObject.h"
#include "PlayState.h"

PacManObject::PacManObject(Game* g, PlayState* pS) : GameObject(g)
{
	pState = pS;
}


PacManObject::~PacManObject()
{
}
