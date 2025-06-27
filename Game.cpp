/*==============================================================================

   Game [Game.cpp]

==============================================================================*/
#include "Game.h"
#include "Player.h"

void Game_Initialize()
{
	Player_Initialize({ 0.f, 0.f });
}

void Game_Finalize()
{

}

void Game_Update(double elapsed_time)
{
	Player_Update(elapsed_time, 100.f);
}

void Game_Draw()
{
	Player_Draw();
}