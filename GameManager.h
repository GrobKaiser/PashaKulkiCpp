#pragma once

class GameManager
{

public:
	virtual ~GameManager() = default;

	virtual void Play() = 0;
};

