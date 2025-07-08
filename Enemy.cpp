/*==============================================================================

   Make Enemy [Enemy.cpp]

==============================================================================*/
#include "Enemy.h"
#include <DirectXMath.h>
using namespace DirectX;
#include "direct3d.h"
#include "texture.h"
#include "sprite.h"
#include "Collision.h"
#include "Effect.h"

struct Enemy_Type
{
	float HP;

	int TexID;
	int Cut_X, Cut_Y, Texture_W, Texture_H;

	XMFLOAT2 Velocity;
	Circle Collision;
};

struct Enemy
{
	int Type_ID;

	XMFLOAT2 position;
	XMFLOAT2 size;
	float OffsetY;
	XMFLOAT2 velocity; // Input In Enemy_Type, Can Make Speed which Enemy

	double Lifetime;
	float HP;

	bool isEnable;
	bool isDamage;
};

static Enemy Enemy_s[ENEMY_MAX]{};
static int Enemy_TexID = -1;
static Enemy_Type EnemyType[Enemy_Type_MAX]
{
	// HP, TexID, X, Y, W, H
	// {{ Velocity.x, y }, { Collision.x, y}, Radius }
	{ ENEMY_HP, -1, 0, 0, 0, 0, { -ENEMY_SPEED, 0.0f },
	{ { ENEMY_WIDTH * 0.5f, ENEMY_HEIGHT * 0.5f }, ENEMY_RADIUS } },

	{ ENEMY_SABER_HP,  -1, 0, 0, 0, 0, { -ENEMY_SPEED, 0.0f },
	{ { ENEMY_WIDTH * 0.5f, ENEMY_HEIGHT * 0.5f }, ENEMY_RADIUS } },

	{ ENEMY_BLOCK_HP, -1, 0, 0, 0, 0, { -ENEMY_SPEED, 0.0f },
	{ { ENEMY_WIDTH * 0.5f, ENEMY_HEIGHT * 0.5f }, ENEMY_RADIUS } },

	{ ENEMY_SPECAIL_HP, -1, 0, 0, 0, 0, { -ENEMY_SPECAIL_SPEED, 0.0f },
	{ { ENEMY_SPECAIL_WIDTH * 0.5f, ENEMY_SPECAIL_HEIGHT * 0.5f }, ENEMY_SPECAIL_RADIUS } },

	{ ENEMY_MIDDLE_BOSS_HP, -1, 0, 0, 0, 0, { -ENEMY_MIDDLE_BOSS_SPEED, 0.0f},
	{ { ENEMY_MIDDLE_BOSS_WIDTH * 0.5f, ENEMY_MIDDLE_BOSS_HEIGHT * 0.5f}, ENEMY_MIDDLE_BOSS_RADIUS } }
};

void Enemy_Initialize()
{
	for (Enemy& Enemy : Enemy_s)
		Enemy.isEnable = false;
	EnemyType[Enemy_Type_Origin].TexID = Texture_Load(L"Resource/Texture/Enemy_Original_Fixed.png");
	EnemyType[Enemy_Type_Saber].TexID = Texture_Load(L"Resource/Texture/Enemy_Saber_Fixed.png");
	EnemyType[Enemy_Type_Block].TexID = Texture_Load(L"Resource/Texture/Enemy_Block_Fixed.png");
	EnemyType[Enemy_Type_Spider].TexID = Texture_Load(L"Resource/Texture/Enemy_Spider_Fixed.png");
	EnemyType[Enemy_Type_Middle_Boss].TexID = Texture_Load(L"Resource/Texture/Enemy_Middle_Boss_Fixed.png");
}

void Enemy_Finalize()
{

}

void Enemy_Update(double elapsed_time)
{
	for (Enemy& Enemy : Enemy_s)
	{
		if (!Enemy.isEnable)	continue;

		switch (Enemy.Type_ID)
		{
		case Enemy_Type_Origin:
			XMVECTOR Position = XMLoadFloat2(&Enemy.position);
			XMVECTOR Velocity = XMLoadFloat2(&Enemy.velocity);

			Position += Velocity * elapsed_time;

			XMStoreFloat2(&Enemy.position, Position);
			XMStoreFloat2(&Enemy.velocity, Velocity);
			break;

		case Enemy_Type_Saber:
			Enemy.position.x += Enemy.velocity.x * elapsed_time;
			Enemy.position.y = Enemy.OffsetY + sin(Enemy.Lifetime) * 120;
			break;

		case Enemy_Type_Block:
			Enemy.position.x += Enemy.velocity.x * elapsed_time;
			Enemy.position.y = Enemy.OffsetY + cos(Enemy.Lifetime * 2) * 150;
			break;

		case Enemy_Type_Spider:
			Enemy.position.x += Enemy.velocity.x * elapsed_time;
			break;

		case Enemy_Type_Middle_Boss:
			Enemy.position.x += Enemy.velocity.x * elapsed_time;
			break;
		}

		Enemy.Lifetime += elapsed_time;

		if (Enemy.position.x + ENEMY_WIDTH < 0.f)
			Enemy.isEnable = false;
	}
}

void Enemy_Draw()
{
	for (Enemy& Enemy : Enemy_s)
	{
		if (!Enemy.isEnable)	continue;

		Sprite_Draw(EnemyType[Enemy.Type_ID].TexID,
							  Enemy.position.x, Enemy.position.y,
							  Enemy.size.x, Enemy.size.y,
							  ENEMY_ANGLE,
		Enemy.isDamage ? XMFLOAT4{ 1.0f, 0.0f, 0.0f, 1.0f } : XMFLOAT4{ 1.0f, 1.0f, 1.0f, 1.0f });

		Enemy.isDamage = false;
	}
}

void Enemy_Create(EnemyTypeID ID, const DirectX::XMFLOAT2& position)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (Enemy_s[i].isEnable) continue;

		Enemy_s[i].isEnable = true;
		Enemy_s[i].Type_ID = ID;
		Enemy_s[i].position = position;
		switch (Enemy_s[i].Type_ID)
		{
		case Enemy_Type_Spider:
			Enemy_s[i].size = { ENEMY_SPECAIL_WIDTH, ENEMY_SPECAIL_HEIGHT };
			break;
			
		case Enemy_Type_Middle_Boss:
			Enemy_s[i].size = { ENEMY_MIDDLE_BOSS_WIDTH, ENEMY_MIDDLE_BOSS_HEIGHT };
			break;

		default:
			Enemy_s[i].size = { ENEMY_WIDTH, ENEMY_HEIGHT };
			break;
		}
		switch (Enemy_s[i].Type_ID)
		{
		case Enemy_Type_Spider:
			Enemy_s[i].velocity = { -ENEMY_SPECAIL_SPEED, 0.0 };
			break;

		case Enemy_Type_Middle_Boss:
			Enemy_s[i].velocity = { -ENEMY_MIDDLE_BOSS_SPEED, 0.0 };
			break;

		default:
			Enemy_s[i].velocity = { -ENEMY_SPEED, 0.0 };
			break;
		}
		Enemy_s[i].Lifetime = 0.0;
		Enemy_s[i].OffsetY = Enemy_s[i].position.y;
		switch (Enemy_s[i].Type_ID)
		{
		case Enemy_Type_Saber:
			Enemy_s[i].HP = ENEMY_SABER_HP;
			break;

		case Enemy_Type_Block:
			Enemy_s[i].HP = ENEMY_BLOCK_HP;
			break;

		case Enemy_Type_Spider:
			Enemy_s[i].HP = ENEMY_SPECAIL_HP;
			break;

		case Enemy_Type_Middle_Boss:
			Enemy_s[i].HP = ENEMY_MIDDLE_BOSS_HP;
			break;

		default:
			Enemy_s[i].HP = ENEMY_HP;
			break;
		}
		Enemy_s[i].isDamage = false;
		break;
	}
}

bool Enemy_IsEnable(int Index)
{
	return Enemy_s[Index].isEnable;
}

Circle Enemy_GetCollision(int Index)
{
	int ID = Enemy_s[Index].Type_ID;

	float Cx = Enemy_s[Index].position.x + EnemyType[ID].Collision.Center.x;
	float Cy = Enemy_s[Index].position.y + EnemyType[ID].Collision.Center.y;

	return { { Cx, Cy }, EnemyType[ID].Collision.Radius };
}

void Enemy_Damage(int Index)
{
	Enemy_s[Index].HP -= BULLET_DAMAGE;
	Enemy_s[Index].isDamage = true;

	if (Enemy_s[Index].HP <= 0.0f)
	{
		Effect_Create(Enemy_s[Index].position);
		Enemy_s[Index].isEnable = false;
	}
}

void Enemy_Destroy(int Index)
{
	Enemy_s[Index].isEnable = false;
}
