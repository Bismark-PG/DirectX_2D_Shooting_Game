/*==============================================================================

   Game [Game.cpp]

==============================================================================*/
#include "Game.h"
#include "Player.h"
#include "Bullet.h"

void Game_Initialize()
{
	Player_Initialize({ 0.f, 0.f });
	Bullet_Initialize();
}

void Game_Finalize()
{

}

void Game_Update(double elapsed_time)
{
	Player_Update(elapsed_time, 100.f);
	Bullet_Update(elapsed_time);
}

void Game_Draw()
{
	Bullet_Draw();
	Player_Draw();
}