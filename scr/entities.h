#pragma once
#include "main.h"
#include "render.h"
#include "game_resources.h"

struct EntityEnemy {
	collisionbox Collision;
	point Pos;
	point MovementDir;
	double Rotation = 0;
	double Speed;
	double Height;
	double Width;
	std::string Word;
	std::string ArithmeticAnswer;
	int TextureIndex = GIMG_MISSING;	
};
struct EntityPlayer {
	collisionbox Collision;
	point Pos;
	point MovementDir;
	double Rotation;
	double Speed;
	double Width;	
	double Height;
	int Score = 0;
	bool IsDamaged = false;	
};
struct EntityCosmeticParticle {
	point Pos;
	int Size;
	int Type;
};
struct EntityBonus {
	point Pos;	
	double Rotation;
	std::string Word;
	std::string ArithmeticAnswer;
	int ID;
	int Size;
	int FullSize;
	int Lifetime;	
	int TextureIndex = GIMG_MISSING;
	bool RotationClockwise;
};
enum CosmeticParticleTypes {
	PRTCL_HEART,
	PRTCL_STAR
};
enum BonusesIDs
{
	BNS_RANDOM,
	BNS_HEART,
	BNS_X2,	
	BNS_SLOWDOWN,
	BNS_LAST,
};

extern std::vector<EntityEnemy> GameEnemies;
extern std::vector<point> GamePlayerHearts;
extern std::vector<EntityCosmeticParticle> GameCosmetics;
extern std::vector<EntityBonus> GameBonuses;

void UpdateEntities();
void AddHearts(int Count);
void RemoveHearts(int Count);
void SpawnBonus(DifficultyCode Difficulty, bool ArithmeticMode);
void SpawnEnemy(DifficultyCode Difficulty, bool ArithmeticMode);