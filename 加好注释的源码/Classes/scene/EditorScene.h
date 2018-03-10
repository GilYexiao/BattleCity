/***********************************************

�������������Զ����ͼ�����Զ����ͼ��ҳ�Ĺ����ࡣ
�����Զ����ͼ��ҳ�ĳ����֡������ƶ�����̨����

***********************************************/

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
	void bgInit();//��ʼ������
	Vec2 getButtonPos(int x, int y);//���ݰ�ť�����λ�ã��õ�����λ��
	String getSpriteName(int type);//��ͼԪ�ص�ѡ����
	char getAChar();//�ļ��洢������װ��
	void saveName();//�����ļ�

	void  readName();//��ȡ�ļ�

	LayerColor *_bg;//����
	Scale9Sprite *selector;//�˵����Ĺ��
	Sprite* selector2;//�����ڵĹ��
	mapType type;//��ͼԪ�صķ���
	Vector<Sprite *> cell;//��ͼԪ�ص�UI����
	Vector<Scale9Sprite*> cell9;//�˵�Ԫ�ص�UI����
	Sprite*  map[MAP_ROW][MAP_COL];//������ԪUI
	int  intMap[MAP_ROW][MAP_COL] = { 0 };//�ļ��洢�ĵ�ͼ
	/* ���ֲ˵��Լ����Ƿ񱻼����ָʾ��*/
	Sprite* backMenu;//
	Sprite* saveMenu;
	Sprite* nameMenu;
	int backMenuNum=0;
	int saveMenuNum=0;
	int nameMenuNum=0;
	Label* inputLabel;
	Sprite* indentifier;

	/*������صĲ���*/
	Vec2 pos;
	Vec2 oldpos=getPos(0,0);
	int _x = 0;
	int _y = 0;
	/*���뷨��ز���*/
	bool isInputing = false;
	char name[31] = { '\0' };
	int index = 0;
	/*��ͼ��ز���*/
	int mapNumMax;
	std::vector<std::string> mapNames;
};