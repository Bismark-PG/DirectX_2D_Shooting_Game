/*==============================================================================

   Make Enemy Pattern [Enemy_Spawner.h]

==============================================================================*/
#include "Enemy_Spawner.h"
#include <DirectXMath.h>
using namespace DirectX;

struct EnemySpawn
{
	EnemyTypeID ID;
	XMFLOAT2 Position;
	double Triger_Time;
	double Rate;
	int CountMAX;
	bool IsEnded;
	int SpawnCount;
	double SpawnTime;
};

static constexpr unsigned int Enemy_SPAWNER_MAX = 100;
static EnemySpawn Enemy_Spawners[Enemy_SPAWNER_MAX]{};

static int Spawner_Count = 0;
static double Time = 0.0;

void Enemy_Spawner_Initialize()
{
	Spawner_Count = 0;
	Time = 0.0;
}

void Enemy_Spawner_Finalize()
{

}

void Enemy_Spawner_Update(double elapsed_time)
{
	Time += elapsed_time;

	for (int i = 0; i < Spawner_Count; i++)
	{
		if (Enemy_Spawners[i].IsEnded) continue;

		if (Enemy_Spawners[i].Triger_Time > Time) break;

		if (Enemy_Spawners[i].SpawnCount == 0)
			Enemy_Spawners[i].SpawnTime = Time - Enemy_Spawners[i].Rate - 0.00001;

		if (Time - Enemy_Spawners[i].SpawnTime >= Enemy_Spawners[i].Rate)
		{
			Enemy_Create(Enemy_Spawners[i].ID, Enemy_Spawners[i].Position);
			Enemy_Spawners[i].SpawnCount++;
			if (Enemy_Spawners[i].SpawnCount >= Enemy_Spawners[i].CountMAX)
				Enemy_Spawners[i].IsEnded = true;
			Enemy_Spawners[i].SpawnTime = Time;
		}
	}
}

void Enemy_Spawner_Create(EnemyTypeID ID, const XMFLOAT2& Position,
	double Spawn_Triger, double Spawn_Rate, int Spawn_Count)
{
	if (Spawner_Count >= Enemy_SPAWNER_MAX) return;

	EnemySpawn* P_ES = &Enemy_Spawners[Spawner_Count];
	P_ES->ID = ID;
	P_ES->Position = Position;
	P_ES->Triger_Time = Spawn_Triger;
	P_ES->Rate = Spawn_Rate;
	P_ES->CountMAX = Spawn_Count;
	P_ES->IsEnded = false;
	P_ES->SpawnCount = 0;
	P_ES->SpawnTime = 0.0;
	Spawner_Count++;
}