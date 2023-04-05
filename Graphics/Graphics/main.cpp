
#include "Game.h"

int main(void)
{
	int result = CGame::Get()->Initialize();
	if (!result)
	{
		result = CGame::Get()->Run();
	}

	CGame::Get()->Finalize();

	return result;
}