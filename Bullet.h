/*==============================================================================

   Make Bullet [Bullet.h]

==============================================================================*/
#ifndef BULLET_H
#define BULLET_H

#include <DirectXMath.h>
#include "Collision.h"

static constexpr unsigned int BULLET_MAX = 2048;

static constexpr float BULLET_WIDTH = 32.0f;
static constexpr float BULLET_HEIGHT = 32.0f;
static constexpr float BULLET_SPEED = 600.0f;

static constexpr float BULLET_DAMAGE = 25.0f;


void Bullet_Initialize();
void Bullet_Finalize();

void Bullet_Update(double elapsed_time);
void Bullet_Draw();

void Bullet_Create(const DirectX::XMFLOAT2& position);

bool Bullet_IsEnable(int Index);
Circle Bullet_GetCollision(int Index);

void Bullet_Destroy(int Index);

#endif  //BULLET_H