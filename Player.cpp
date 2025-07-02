/*==============================================================================

   Player [Player.cpp]

==============================================================================*/
#include "Player.h"
#include <DirectXMath.h>
using namespace DirectX;
#include "Texture.h"
#include "Sprite.h"
#include "KeyLogger.h"
#include "Bullet.h"

static XMFLOAT2 PlayerPosition{};
static XMFLOAT2 PlayerVelocity{};

static int TexID = -1;

void Player_Initialize(const XMFLOAT2& Position)
{
	PlayerPosition = Position;
	PlayerVelocity = { 0.0f, 0.0f };

	TexID = Texture_Load(L"Resource/Texture/Player_Fixed.png");
}

void Player_Finalize()
{

}

void Player_Update(double elapsed_time, float Speed)
{
	XMVECTOR Position = XMLoadFloat2(&PlayerPosition);
	XMVECTOR Velocity = XMLoadFloat2(&PlayerVelocity);

	XMVECTOR Direction{};

	if (KeyLogger_IsPressed(KK_W))
	{
		Direction += { 0.f, -1.f };
	}
	if (KeyLogger_IsPressed(KK_S))
	{
		Direction += { 0.f, 1.f };
	}
	if (KeyLogger_IsPressed(KK_A))
	{
		Direction += { -1.f, 0.f };
	}
	if (KeyLogger_IsPressed(KK_D))
	{
		Direction += { 1.f, 0.f };
	}

	Direction = XMVector2Normalize(Direction);

	Velocity += Direction * Speed * elapsed_time;

	Position += Velocity;

	Velocity *= 0.5f;

	XMStoreFloat2(&PlayerPosition, Position);
	XMStoreFloat2(&PlayerVelocity, Velocity);

	if (KeyLogger_IsTrigger(KK_SPACE))
	{
		Bullet_Create({ PlayerPosition.x + 16, PlayerPosition.y + (64.0f - 16) * 0.5f });
	}
}

void Player_Draw()
{
	Sprite_Draw(TexID, PlayerPosition.x, PlayerPosition.y, 64, 64);
}