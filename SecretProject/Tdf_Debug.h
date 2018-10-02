#pragma once

#include "Player.h"

class Engine;

class Tdf_Debug
{
public:
	Tdf_Debug(Engine* ipEngine);
	~Tdf_Debug();

	void AddUnitInArea();

	void AddOrderInArea();

	Player** GetPlayers();

private:
	Engine* _pEngine;
};

