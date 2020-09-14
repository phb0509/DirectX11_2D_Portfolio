#pragma once

class GameManager
{
private:
	static GameManager* instance;

public:

	GameManager();
	~GameManager();

	
	Gunner* GetGunner() { return gunner; }
 	//vector<Bullet*> GetGunnerBullets() { return gunner_bullets; }

	static GameManager* Get() { return instance; }
	static void Create() { instance = new GameManager(); }
	static void Delete() { delete instance; }

	//Get
	vector<Monster*> GetMirkwoodMonsters() { return monsters_MirkwoodScene;  }


	void SetMirkWoodScene();


private:
	Gunner* gunner;
	Bullet* bullet;
	Gnoll_Mirkwood* gnoll;
	vector<Monster*> monsters_MirkwoodScene;

};