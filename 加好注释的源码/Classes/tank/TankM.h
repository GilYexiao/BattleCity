#pragma once
/*****************************************
�������̹�˹����࣬��Ҫ�Ĺ��ܾ����ṩ����̹�˵Ľӿڣ�������ͣ��Ϸ���Ƴ�̹�˵ĺ���
*****************************************/
#include "cocos2d.h"
#include "data\Global.h"
#include "PlayerTank.h"
#include "EnemyTank.h"
#include "Bonus.h"
class GameScene;
class Stage;
class Tank;
class PlayerTank;
class TankM;
class EnemyTank;
USING_NS_CC;

using namespace std;
class TankM : public Layer
{
public:
	TankM();
	~TankM();
	CREATE_FUNC(TankM);
	bool init();
	/* ��ȡ���̹�� */
	PlayerTank* getPlayerTank() { return _playerTank;}
	/* ��ȡ����̹�� */
	Vector<EnemyTank*>& getEnemyTanks() { return _enemyTanks; }
	/* ��ȡ����̹�� */
	Vector<Tank*>& getAllTanks() { return _tanks; }
	
	/*��������*/
	Bonus* bonus;
	void removeBonus();
	/* ɾ��̹�� */
	void removeTank(Tank* tank);
	/* ɱ�����е���̹�� */
	void killAllEnemy();

	/* ��ͣ��Ϸ */
	void pauseGame();
	/* ������Ϸ */
	void resumeGame();
	/* ����updateSlider ֵ��Ϊ0��100 */
	int remainedHP() { 
		if (_playerTank != nullptr)
		{
			return static_cast<int>(100 * ((float)_playerTank->getHP() / (float)TankData::getInstance()->getHP()));
		}
		else
			return 0;
	}
	/* ����updateSlider ֵ��Ϊ0��100 */
	int getProgress() { return static_cast<int>(100 * ((float)curEnemyId / (float)ENEMY_NUM));}

	int EnemyTankNum() { return _enemyTanks.size(); }

	/* ����_playerTank,��Ҫ���ǵ����HP�İ�ȫ��� */
	void set_playerTank(PlayerTank* playerTank) { _playerTank = playerTank; }


private:
	/* ��ʱ���ص��������µĵ���̹�ˣ� */
	void timer(float dt);
	/* �����µ����̹�� */
	void createNewPlayer();
	/* �����µĵ���̹�� */
	void createNewEnemy();

	int _pos=0;								// ����̹�˳��ֵ�λ�� 
	PlayerTank* _playerTank;				// ���̹�� 
	Vector<EnemyTank*> _enemyTanks;			// ����̹�� 
	Vector<Tank*> _tanks;					// ����̹�� 
	int curEnemyId;							// ����̹���Ƿ�ȫ������ 

};