#pragma once
#include "cocos2d.h"
#include "data\Global.h"
#include <iostream>
#include "PauseLayer.h"
#include "scene\GameScene.h"
#include "ui\CocosGUI.h"

using namespace ui;
USING_NS_CC;
using namespace std;

enum        // ��ͼԪ������ 
{
	LAND,	// ��       0
	BRICK,	// ש		1
	GRASS,  // ��		2
	WATER,  // ˮ		3
	GRID1,  // ��1 ����	4
	GRID2,  // ��2 ����	5
	GRID3,  // ��3 ����	6
	GRID4,	// ��4 ����	7
	HOME4,  // ��Ӫ����ã����Ͻ�	8
	HOME3,  // ��Ӫ����ã���������	9
	HOME2,  // ��Ӫ���𻵣����Ͻ� 
	HOME1   // ��Ӫ���𻵣��������� 


};

class Stage :public LayerColor
{
public:
	CREATE_FUNC(Stage);
	virtual bool init();
	// ��ȡ��ͼ����
	LayerColor * getBG() { return _bg; };
	/* �Ƿ�ɴ� */
	bool isCanHit(int row, int col);
	/* �Ƿ������ */
	bool isCanWalk(int row, int col);
	/* ��ȡ��ǰ���ֵĵ���̹�˵����� */
	int getEnemyType() { return _type[_enemyID++]; }
	/* ��ȡ��ǰ���ֵĵ���̹�˵�id */
	int getCurEnemyId() { return _enemyID; }
	/* ��ȡ��ͼԪ�صĶ�ά���� */
	void getMap(int(*&map)[MAP_COL]) { map = _map; }
	/* �ؿ�ʤ�� */
	void win();
	/* �ؿ�ʧ�� */
	void fail();
	/* ��ͣ��Ϸ */
	void pauseGame();
	/* ������Ϸ */
	void resumeGame();
	/* ��ʼ������������ */
	void initInfo();
	/* ���µ�ͼԪ�� */
	void updateMapCell(int row, int col);
	/* GameScene */
	CC_SYNTHESIZE(GameScene *, gameScene, GameScene);
	//��ͣ��
	CC_SYNTHESIZE(PauseLayer *, pauseLayer, PauseLayer);
	/* getHP������ */
	Slider *getHPSlider() { return hpSlider; }
	/* get��Ϸ������ */
	Slider *getProgressSlider() { return progressSlider; }
	/* �ܷ�Ŵ��� */
	bool changeIsKReady();
	/* ���½�����,������MP */
	void sliderUpdate(float dt);
	/* ����MP������*/
	void MPUpdate(float dt);

private:
	void onExit();
	/* ��ʼ����ͼ */
	void initMap();
	/* ������ͼԪ�� */
	void createMapCell(int row, int col, int type);
	/* ��ȡ��ͼԪ����������Ӧ�ľ���ͼƬ������ */
	string getSpriteName(int type);


	int _id;						// ��ͼid(��һ��Ϊ1)
	int _map[MAP_ROW][MAP_COL];		// ��ͼ���� 
	int _type[ENEMY_NUM];			// ����̹������
	int _enemyID;					// ����̹��id����һ�����ֵĵ���̹��idΪ0�� 
	LayerColor *_bg;				// ��ͼ����
	Slider *hpSlider;				// HP������
	Slider *mpSlider;				// MP������
	Slider *progressSlider;			// ����
	Sprite *cursor;					// �α�
	float readyInterval;			// ��ȴʱ��
	bool isReady;					// �����Ƿ�׼����
	HeroType heroType;				// Ӣ������
	Animate *bigSkillAnimate;		//���ж���

};


//void Stage::setHomeWall(int newType)
//{
//	for (auto row = 23; row <= 25; row++)
//	{
//		for (auto col = 11; col <= 14; col++)
//		{
//			auto &type = _map[row][col];
//			if ((type & 0x0f) < HOME1) // �ж��Ƿ�Ϊ��Ӫ��Χ��ǽ��Ϊ�˰Ѵ�Ӫ�ų����� 
//			{
//				type = newType;
//				updateMapCell(row, col);
//			}
//		}
//	}
//}