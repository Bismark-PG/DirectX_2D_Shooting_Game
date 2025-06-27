/*==============================================================================

   Player [Player.h]

==============================================================================*/
#ifndef PLAYER_H
#define PLAYER_H

#include <DirectXMath.h>

void Player_Initialize(const DirectX::XMFLOAT2& Position);
void Player_Finalize();

void Player_Update(double elapsed_time, float Speed);
void Player_Draw();

#endif // PLAYER_H
