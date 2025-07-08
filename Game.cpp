/*==============================================================================

   Game [Game.cpp]

==============================================================================*/
#include "Game.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Enemy_Spawner.h"
#include "Effect.h"

double elapsed_time_copy;

void Game_Initialize()
{
	Player_Initialize({ (SCREEN_WIDTH * 0.1f) - (PLAYER_WIDTH * 0.5), (SCREEN_HEIGHT * 0.5f) - (PLAYER_HEIGHT * 0.5f) });
	Bullet_Initialize();
	Enemy_Initialize();
	Enemy_Spawner_Initialize();
	Effect_Initialize();

	Enemy_Spawner_Create(Enemy_Type_Saber,		 { SCREEN_WIDTH, (SCREEN_HEIGHT * 0.2f) - (ENEMY_HEIGHT * 0.5f) },				0.5, 0.2, 5);
	Enemy_Spawner_Create(Enemy_Type_Saber,		 { SCREEN_WIDTH, (SCREEN_HEIGHT * 0.8f) - (ENEMY_HEIGHT * 0.5f) },				0.5, 0.2, 5);
	Enemy_Spawner_Create(Enemy_Type_Origin,		 { SCREEN_WIDTH, (SCREEN_HEIGHT * 0.5f) - (ENEMY_HEIGHT * 0.5f) },				1.0, 0.3, 3);
	Enemy_Spawner_Create(Enemy_Type_Block,		 { SCREEN_WIDTH, (SCREEN_HEIGHT * 0.4f) - (ENEMY_HEIGHT * 0.5f) },				2.0, 0.5, 2);
	Enemy_Spawner_Create(Enemy_Type_Spider,		 { SCREEN_WIDTH, (SCREEN_HEIGHT * 0.5f) - (ENEMY_SPECAIL_HEIGHT * 0.5f) },		2.5, 3.0, 2);
	Enemy_Spawner_Create(Enemy_Type_Middle_Boss, { SCREEN_WIDTH, (SCREEN_HEIGHT * 0.5f) - (ENEMY_MIDDLE_BOSS_HEIGHT * 0.5f) },  5.0, 1.0, 1);
}

void Game_Finalize()
{
	Effect_Finalize();
	Enemy_Spawner_Finalize();
	Enemy_Finalize();
	Bullet_Finalize();
	Player_Finalize();
}

void Game_Update(double elapsed_time)
{
	Enemy_Spawner_Update(elapsed_time);
	Player_Update(elapsed_time);
	Bullet_Update(elapsed_time);
	Enemy_Update(elapsed_time);

	AABB_Bullet_VS_Enemy();
	AABB_Player_VS_Enemy();

	Effect_Update(elapsed_time);
}

void Game_Draw()
{
	Enemy_Draw();
	Bullet_Draw();
	Player_Draw();

	Effect_Draw();
}

void AABB_Bullet_VS_Enemy()
{
	for (int B_Index = 0; B_Index < BULLET_MAX; B_Index++)
	{
		// AABB For Bullet
		if (!Bullet_IsEnable(B_Index)) continue;

		for (int E_Index = 0; E_Index < ENEMY_MAX; E_Index++)
		{
			// AABB For Enemy
			if (!Enemy_IsEnable(E_Index)) continue;

			// IF AABB Success (True)
			if (Collision_IsOverlapCircle
			(Bullet_GetCollision(B_Index), Enemy_GetCollision(E_Index)))
			{
				Bullet_Destroy(B_Index);
				Enemy_Damage(E_Index);
			}
		}
	}
}

void AABB_Player_VS_Enemy()
{
	if (!Player_IsEnable()) return;

	for (int E_Index = 0; E_Index < ENEMY_MAX; E_Index++)
	{
		// AABB For Enemy
		if (!Enemy_IsEnable(E_Index)) continue;

		// AABB To Enemy
		if (Collision_IsOverlapCircle
		(Player_GetCollision(), Enemy_GetCollision(E_Index)))
		{
			// IF AABB Success, Player Dead
			Player_Destroy();
			//Enemy_Destroy(E_Index);
		}
	}
}
