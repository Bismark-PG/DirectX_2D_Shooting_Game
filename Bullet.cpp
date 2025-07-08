/*==============================================================================

   Make Bullet [Bullet.cpp]

==============================================================================*/
#include "Bullet.h"
#include <DirectXMath.h>
using namespace DirectX;
#include "direct3d.h"
#include "texture.h"
#include "sprite.h"
#include "Collision.h"



struct Bullet
{
	XMFLOAT2 position;
	XMFLOAT2 size;
	XMFLOAT2 velocity;
	double lifeTime;
	bool isEnable;
	Circle Collision;
};

static Bullet Bullets[BULLET_MAX]{};
static int Bullet_TexID{};

void Bullet_Initialize()
{
	for (Bullet& Bullet : Bullets)
	{
		Bullet.isEnable = false;
	}
	Bullet_TexID = Texture_Load(L"resource/texture/Bullet.png");
}

void Bullet_Finalize()
{
}

void Bullet_Update(double elapsed_time)
{
	for (Bullet& Bullet : Bullets)
	{
		// 弾の表示時間を計測
		Bullet.lifeTime += elapsed_time;
		// 弾の使用フラグを折る
		if (Bullet.lifeTime >= 5.0)
		{
			Bullet.isEnable = false;
		}
		if (Bullet.position.x > Direct3D_GetBackBufferWidth())
		{
			Bullet.isEnable = false;
		}

		// 使われてない弾の処理はしない
		if (!Bullet.isEnable)	continue;

		// 演算用の変数に格納
		XMVECTOR pos = XMLoadFloat2(&Bullet.position);
		XMVECTOR vel = XMLoadFloat2(&Bullet.velocity);

		// ポジションをずらす
		pos += vel * elapsed_time;

		// 元の変数に返す
		XMStoreFloat2(&Bullet.position, pos);
		XMStoreFloat2(&Bullet.velocity, vel);
	}
}

void Bullet_Draw()
{
	for (Bullet& Bullet : Bullets)
	{
		if (!Bullet.isEnable)	continue;

		Sprite_Draw(Bullet_TexID, Bullet.position.x, Bullet.position.y, Bullet.size.x, Bullet.size.y, 0.f);
	}
}

void Bullet_Create(const XMFLOAT2& position)
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (Bullets[i].isEnable) continue;

		Bullets[i].isEnable = true;
		Bullets[i].lifeTime = 0.0;
		Bullets[i].position = position;
		Bullets[i].size = { BULLET_WIDTH, BULLET_HEIGHT };
		Bullets[i].velocity = { BULLET_SPEED, 0.0 };
		Bullets[i].Collision = { { 16.0f, 16.0f }, 16.0f };
		break;
	}
}

bool Bullet_IsEnable(int Index)
{
	return Bullets[Index].isEnable;
}

Circle Bullet_GetCollision(int Index)
{
	float Cx = Bullets[Index].Collision.Center.x
		+ Bullets[Index].position.x;
	float Cy = Bullets[Index].Collision.Center.y
		+ Bullets[Index].position.y;

	return { { Cx, Cy }, Bullets[Index].Collision.Radius};
}

void Bullet_Destroy(int Index)
{
	Bullets[Index].isEnable = false;
}
