/*==============================================================================

   Make Enemy Pattern [Enemy_Spawner.h]

==============================================================================*/
#ifndef ENEMY_SPAWNER_H
#define ENEMY_SPAWNER_H

#include <DirectXMath.h>
#include "Enemy.h"


void Enemy_Spawner_Initialize();
void Enemy_Spawner_Finalize();

void Enemy_Spawner_Update(double elapsed_time);

void Enemy_Spawner_Create(EnemyTypeID ID, const DirectX::XMFLOAT2& position,
						double Spawn_Triger, double Spawn_Rate, int Spawn_Count);

#endif  //ENEMY_SPAWNER_H