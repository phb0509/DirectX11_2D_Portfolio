#pragma once

class GameManager
{
private:
	static GameManager* instance;

public:

	GameManager();
	~GameManager();

	
	Gunner* GetGunner() { return gunner; }
 	vector<Bullet*> GetGunnerBullets() { return gunner_bullets; }

	static GameManager* Get() { return instance; }
	static void Create() { instance = new GameManager(); }
	static void Delete() { delete instance; }



private:
	Gunner* gunner;
	Bullet* bullet;


	vector<Bullet*> gunner_bullets;

};