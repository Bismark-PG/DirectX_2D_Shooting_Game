/*==============================================================================

   Player [Player.h]

==============================================================================*/
#ifndef PLAYER_H
#define PLAYER_H

void Player_Initialize(const XMFLOAT2& Position);
void Player_Finalize();

void Player_Update(double elapsed_time);
void Player_Draw();

#endif // PLAYER_H
