/***********************************************

�����ǽ�����Ϸ�ĳ�������������ǰ��Ϸ������״̬��
����̹���ࡢ�ӵ��ࡢ��ը�����������

***********************************************/

#pragma once
#include "cocos2d.h"
#include "tank\TankM.h"
#include "stage\Stage.h"
#include "stage\WinLayer.h"
#include "stage\FailLayer.h"
#include "tank\BulletM.h"
#include "media\AudioM.h"
#include "media\BombM.h"

USING_NS_CC;
class GameScene;
class Stage;
class Tank;
class PlayerTank;
class TankM;
class EnemyTank;
enum GameState
{
	kRuning,  // ������
	kPause,   //��ͣ
	kWin,     //ʤ��
	kFail,   //ʧ��
	kNone,
};

class GameScene :public Layer
{
public:
	GameScene();
	~GameScene();
	CREATE_FUNC(GameScene);
	virtual bool init();
	/* ��ȡ̹�˹�������� */
	static TankM *getTankM() { return _tankM; }
	static Stage *getStage() { return _stage; }
	static BulletM *getBulletM() { return _bulletM; }
	static BombM* getBombM() { return _bombM; }
	static GameState getGameState() { return _gameState; }
	static bool isKReady();
private:
	void onExit();
	void onEnterTransitionDidFinish();
	static TankM *_tankM;  //GameScene��̹�˹����൥��
	static Stage *_stage;	//GameScene��Stage����
	static BulletM *_bulletM;  //GameScene��bullet�����൥��
	static BombM *_bombM;  //GameScene��bombM�����൥��
	static GameState _gameState;  //��Ϸ����״̬
	WinLayer *winLayer;				//ʤ����
	FailLayer *failLayer;			//ʧ�ܲ�

	void showFinishedSuccess();

	/* �ؿ�ʤ�� */
	void win(Ref* pSender);
	/* �ؿ�ʧ�� */
	void fail(Ref* pSender);
	/* Update */
	void update(float dt);
	/* ��ͣ��Ϸ */
	void pauseGame();
	/* ������Ϸ */
	void resumeGame();
	/* �ɾ� */
	std::vector<char *> currentFinished;

};