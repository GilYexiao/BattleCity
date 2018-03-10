#pragma once
#include "input\keyboardInput.h"
#include "cocos2d.h"
#include "data\Global.h"
#include "ui\UIScale9Sprite.h"
#include "ui\CocosGUI.h"
#include "EditScene.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace ui;

USING_NS_CC;
enum mapType // ��ͼԪ������ 
{
	mLAND,	// ��       0
	mBRICK,	// ש		1
	mGRASS,  // ��		2
	mWATER,  // ˮ		3
	mGRID1,  // ��1 ����	4
	mGRID2,  // ��2 ����	5
	mGRID3,  // ��3 ����	6
	mGRID4,	// ��4 ����	7
};

class EditorScene :public Layer
{
public:
	CREATE_FUNC(EditorScene);
	virtual bool init();
	void moveSelector1();	//�ƶ��ڵ�ͼ�༭���ڵ�ѡ��
	void moveSelector2();	//�ƶ��ڲ˵����ڵ�ѡ��
	void update(float dt);

private:
	void bgInit();
	Vec2 getButtonPos(int x, int y);
	String getSpriteName(int type);
	char getAChar();
	void saveName();

	void  readName();

	LayerColor *_bg;
	Scale9Sprite *selector;
	Sprite* selector2;
	mapType type;
	Vector<Sprite *> cell;
	Vector<Scale9Sprite*> cell9;
	Sprite*  map[MAP_ROW][MAP_COL];
	int  intMap[MAP_ROW][MAP_COL] = { 0 };
	Sprite* backMenu;
	Sprite* saveMenu;
	Sprite* nameMenu;
	int backMenuNum=0;
	int saveMenuNum=0;
	int nameMenuNum=0;
	Label* inputLabel;
	Sprite* indentifier;

	Vec2 pos;
	Vec2 oldpos=getPos(0,0);
	int _x = 0;
	int _y = 0;
	bool isInputing = false;
	char name[31] = { '\0' };
	int index = 0;

	int mapNumMax;
	std::vector<std::string> mapNames;
};