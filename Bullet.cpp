/*==============================================================================

   Make Bullet [Bullet.cpp]

==============================================================================*/
#include "Bullet.h"
#include <DirectXMath.h>
using namespace DirectX;
#include "direct3d.h"
#include "texture.h"
#include "sprite.h"

static constexpr unsigned int BULLET_MAX = 512;
static constexpr float BULLET_SPEED = 600.0f;

struct Bullet
{
	XMFLOAT2 position;
	XMFLOAT2 size;
	XMFLOAT2 velocity;
	double lifeTime;
	bool isEnable;
};

static Bullet Bullets[BULLET_MAX]{};
static int Bullet_TexID{};

void Bullet_Initialize()
{
	for (Bullet& bull : Bullets)
	{
		bull.isEnable = false;
	}
	Bullet_TexID = Texture_Load(L"resource/texture/Bullet.png");
}

void Bullet_Finalize()
{
}

void Bullet_Update(double elapsed_time)
{
	for (Bullet& bull : Bullets)
	{
		// �e�̕\�����Ԃ��v��
		bull.lifeTime += elapsed_time;
		// �e�̎g�p�t���O��܂�
		if (bull.lifeTime >= 5.0)
		{
			bull.isEnable = false;
		}
		if (bull.position.x > Direct3D_GetBackBufferWidth())
		{
			bull.isEnable = false;
		}

		// �g���ĂȂ��e�̏����͂��Ȃ�
		if (!bull.isEnable)	continue;

		// ���Z�p�̕ϐ��Ɋi�[
		XMVECTOR pos = XMLoadFloat2(&bull.position);
		XMVECTOR vel = XMLoadFloat2(&bull.velocity);

		// �|�W�V���������炷
		pos += vel * elapsed_time;

		// ���̕ϐ��ɕԂ�
		XMStoreFloat2(&bull.position, pos);
		XMStoreFloat2(&bull.velocity, vel);
	}
}

void Bullet_Draw()
{
	for (Bullet& bull : Bullets)
	{
		if (!bull.isEnable)	continue;

		Sprite_Draw(Bullet_TexID, bull.position.x, bull.position.y, bull.size.x, bull.size.y);
	}
}

void Bullet_Create(const XMFLOAT2& position)
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		// �g���Ă���Bullet�Ǘ��ԍ��̎��͏������Ȃ��Ŏ���
		if (Bullets[i].isEnable) continue;

		Bullets[i].isEnable = true;
		Bullets[i].lifeTime = 0.0f;
		Bullets[i].position = position;
		Bullets[i].size = { 32.0f, 32.0f };
		Bullets[i].velocity = { BULLET_SPEED, 0.0 };
		break;
	}
}