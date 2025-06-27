/*==============================================================================

   Player [Player.cpp]

==============================================================================*/
#include "Player.h"
#include <DirectXMath.h>
using namespace DirectX;
#include "Texture.h"
#include "Sprite.h"

static XMFLOAT2 PlayerPosition{};
static int TexID;

void Player_Initialize(const XMFLOAT2& Position)
{
	PlayerPosition = Position;
}

void Player_Finalize()
{
}

void Player_Update(double elapsed_time)
{

}

void Player_Draw()
{

}