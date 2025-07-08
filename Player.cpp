/*==============================================================================

   Player [Player.cpp]

==============================================================================*/
#include "Player.h"
#include <DirectXMath.h>
using namespace DirectX;
#include "direct3d.h"
#include "Texture.h"
#include "Sprite.h"
#include "KeyLogger.h"
#include "Bullet.h"
#include "Collision.h"
#include "Effect.h"

static XMFLOAT2 PlayerPosition{};
static XMFLOAT2 PlayerVelocity{};
static XMFLOAT2 PlayerSize{};

static int TexID = -1;

static Circle PlayerCollision{ {PLAYER_WIDTH * 0.5f, PLAYER_HEIGHT * 0.5f}, PLAYER_SPECAIL_RADIUS };
static bool PlayerEnable = true;

void Player_Initialize(const XMFLOAT2& Position)
{
	TexID = Texture_Load(L"Resource/Texture/Player_Mk_2_Fixed.png");
	
	PlayerPosition = Position;
	PlayerSize = { PLAYER_WIDTH, PLAYER_HEIGHT };
	PlayerEnable = true;
	PlayerVelocity = { 0.0f, 0.0f };
}

void Player_Finalize()
{

}

void Player_Update(double elapsed_time)
{
	// IF Dead, Do Not Update
	if (!PlayerEnable) return;

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

	Velocity += Direction * PLAYER_SPEED * elapsed_time;

	Position += Velocity;

	Velocity *= 0.5f;

	XMStoreFloat2(&PlayerPosition, Position);
	XMStoreFloat2(&PlayerVelocity, Velocity);

	if (PlayerPosition.x <= 0)
	{
		PlayerPosition.x = 0;
	}
	if (PlayerPosition.x >= Direct3D_GetBackBufferWidth() - PlayerSize.x)
	{
		PlayerPosition.x = Direct3D_GetBackBufferWidth() - PlayerSize.x;
	}
	if (PlayerPosition.y <= 0)
	{
		PlayerPosition.y = 0;
	}
	if (PlayerPosition.y >= Direct3D_GetBackBufferHeight() - PlayerSize.y)
	{
		PlayerPosition.y = Direct3D_GetBackBufferHeight() - PlayerSize.y;
	}


	if (KeyLogger_IsTrigger(KK_SPACE))
	{
		Bullet_Create({ PlayerPosition.x + (PLAYER_WIDTH) * 0.8f,
						PlayerPosition.y + (PLAYER_HEIGHT - BULLET_HEIGHT) * 0.5f });
	}
}

void Player_Draw()
{
	// IF Dead, Do Not Draw
	if (!PlayerEnable) return;

	Sprite_Draw(TexID, PlayerPosition.x, PlayerPosition.y, PlayerSize.x, PlayerSize.y, PLAYER_ANGLE);
}

bool Player_IsEnable()
{
	return PlayerEnable;
}

Circle Player_GetCollision()
{
	float Cx = PlayerPosition.x + PlayerCollision.Center.x;	
	float Cy = PlayerPosition.y + PlayerCollision.Center.y;

	return { { Cx, Cy }, PlayerCollision.Radius };
}

void Player_Destroy()
{
	Effect_Create(PlayerPosition);
	PlayerEnable = false;
}
