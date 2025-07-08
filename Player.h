/*==============================================================================

   Player [Player.h]

==============================================================================*/
#ifndef PLAYER_H
#define PLAYER_H

#include <DirectXMath.h>
#include "Collision.h"

static constexpr float PLAYER_WIDTH = 64.0f;
static constexpr float PLAYER_HEIGHT = 96.0f;
static constexpr float PLAYER_SPECAIL_RADIUS = (((PLAYER_WIDTH + PLAYER_HEIGHT) * 0.5f) * 0.1f);

static constexpr float PLAYER_SPEED = 150.f;

static constexpr float PLAYER_ANGLE = 90 * (DirectX::XM_PI / 180);

void Player_Initialize(const DirectX::XMFLOAT2& Position);
void Player_Finalize();

void Player_Update(double elapsed_time);
void Player_Draw();

bool Player_IsEnable();
Circle Player_GetCollision();

void Player_Destroy();

#endif // PLAYER_H
