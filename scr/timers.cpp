
unsigned int TimerEnemySpawn = 0;
unsigned int TimerBonusSpawn = 0;
unsigned int TimerHeartRotate = 0;
unsigned int TimerHeartbeat = 0;
unsigned int TimerEnemyRotation = 0;
unsigned int TimerHeartDamaged = 0;
unsigned int TimerCosmeticHeartDecrease = 0;
unsigned int TimerSpawnRateIncrease = 0;
unsigned int TimerBonusUpdate = 0;

void UpdateTimers() {
	TimerEnemySpawn++;
	TimerBonusSpawn++;
	TimerHeartRotate++;
	TimerHeartbeat++;
	TimerEnemyRotation++;
	TimerHeartDamaged++;
	TimerCosmeticHeartDecrease++;
	TimerSpawnRateIncrease++;
	TimerBonusUpdate++;	
}