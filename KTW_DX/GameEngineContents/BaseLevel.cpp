#include "PreCompile.h"
#include "BaseLevel.h"

#include "OldFilm.h"

BaseLevel::BaseLevel()
{
}

BaseLevel::~BaseLevel()
{
}

void BaseLevel::Start()
{
	GetLevelRenderTarget()->CreateEffect<OldFilm>();
}