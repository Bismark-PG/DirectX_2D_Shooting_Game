#pragma once
/*==============================================================================

   Make Enemy [Enemy.h]

==============================================================================*/
#ifndef ENEMY_H
#define ENEMY_H

#include <DirectXMath.h>
#include "Collision.h"
#include "Bullet.h"

static constexpr unsigned int ENEMY_MAX = 512;

static constexpr float ENEMY_ANGLE = 270.0f * (DirectX::XM_PI / 180.0f);

static constexpr float ENEMY_HP	= 100.0f;
static constexpr float ENEMY_SABER_HP = 50.f;
static constexpr float ENEMY_BLOCK_HP = 200.0f;
static constexpr float ENEMY_WIDTH	= 64.0f;
static constexpr float ENEMY_HEIGHT = 64.0f;
static constexpr float ENEMY_SPEED = 200.0f;
static constexpr float ENEMY_RADIUS = 32.0f;

static constexpr float ENEMY_SPECAIL_HP = 250.0f;
static constexpr float ENEMY_SPECAIL_WIDTH = 160.0f;
static constexpr float ENEMY_SPECAIL_HEIGHT = 160.0f;
static constexpr float ENEMY_SPECAIL_SPEED = 150.0f;
static constexpr float ENEMY_SPECAIL_RADIUS = 80.0f;

static constexpr float ENEMY_MIDDLE_BOSS_HP = 500.f;
static constexpr float ENEMY_MIDDLE_BOSS_WIDTH	= 256.0f;
static constexpr float ENEMY_MIDDLE_BOSS_HEIGHT = 256.0f;
static constexpr float ENEMY_MIDDLE_BOSS_SPEED = 100.0f;
static constexpr float ENEMY_MIDDLE_BOSS_RADIUS = 128.0f

;

enum EnemyTypeID : int
{
	Enemy_Type_Origin = 0,
	Enemy_Type_Saber,
	Enemy_Type_Block,
	Enemy_Type_Spider,
	Enemy_Type_Middle_Boss,
	Enemy_Type_MAX
};

void Enemy_Initialize();
void Enemy_Finalize();
	
void Enemy_Update(double elapsed_time);
void Enemy_Draw();

void Enemy_Create(EnemyTypeID ID, const DirectX::XMFLOAT2& position);

bool Enemy_IsEnable(int Index);
Circle Enemy_GetCollision(int Index);

// Make Damage
void Enemy_Damage(int Index);

void Enemy_Destroy(int Index);

#endif  //ENEMY_H