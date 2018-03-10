/***********************************************

��Ҫ�洢ȫ�ֱ������������״̬���ؿ�������
ÿһ�صط�̹����������ͼ����ȵ�

***********************************************/

#pragma once

#include "cocos2d.h"
USING_NS_CC;


const auto SCREEN_WIDTH = 1024;                         // ��Ļ���
const auto SCREEN_HEIGHT = 768;							// ��Ļ�߶�
const auto SCREEN_CX = SCREEN_WIDTH / 2;				// ��Ļ�߶ȵ�һ��
const auto SCREEN_CY = SCREEN_HEIGHT / 2;				// ��Ļ��ȵ�һ��
const auto CELL_WIDTH = 32;								// ��ͼԪ�صĿ� 
const auto CELL_HEIGHT = 32;							// ��ͼԪ�صĸ�
const auto MAP_ROW = 18;								// ��ͼ���� 
const auto MAP_COL = 28;								// ��ͼ���� 
const auto MAP_WIDTH = MAP_COL*CELL_WIDTH;				// ��ͼ��� 
const auto MAP_HEIGHT = MAP_ROW*CELL_HEIGHT;			// ��ͼ�߶�
const Vec2 MAP_ORIGIN(64, 128);							// ��ͼ����ԭ������
const Vec2 MAP_RIGHTUP(960, 704);						// ��ͼ���ϽǶ�������
const auto FIRSTCOL = 0;								// ��һ����0
const auto FIRSTROW = 0;								// ��һ����0
const auto LEVEL_NUM = 15;								// �ؿ�����	��һ����1
const auto ENEMY_NUM = 30;								// �ؿ�̹������
const auto LEFT_EAGE = MAP_ORIGIN.x;					// ��߽�
const auto RIGHT_EAGE = MAP_RIGHTUP.x;					// �ұ߽�
const auto TOP_EAGE = MAP_RIGHTUP.y;					// �ϱ߽�
const auto BOTTOM_EAGE = MAP_ORIGIN.y;					// �±߽�

/**********

С��������������½�Ϊ׼

**************/

enum Direction	// ���� 
{
	UP = 1,		// �� 
	RIGHT,		// �� 
	DOWN,		// �� 
	LEFT		// �� 
};

// ���̰���
extern bool g_keyUp;
extern bool g_keyRight;
extern bool g_keyDown;
extern bool g_keyLeft;
extern bool g_keySelect;
extern bool g_keyStart;
extern bool g_keyB;
extern bool g_keyA;
extern bool g_keyQ;
extern bool g_keyE;
extern bool g_keyR;
extern bool g_keyT;
extern bool g_keyY;
extern bool g_keyU;
extern bool g_keyI;
extern bool g_keyO;
extern bool g_keyP;
extern bool g_keyF;
extern bool g_keyG;
extern bool g_keyH;
extern bool g_keyL;
extern bool g_keyZ;
extern bool g_keyX;
extern bool g_keyC;
extern bool g_keyV;
extern bool g_key_B;
extern bool g_keyN;
extern bool g_keyM;
extern bool g_keyBACK;
extern bool g_keyCAPSLOCK;
extern bool g_keySPACE;
extern bool g_key0;
extern bool g_key1;
extern bool g_key2;
extern bool g_key3;
extern bool g_key4;
extern bool g_key5;
extern bool g_key6;
extern bool g_key7;
extern bool g_key8;
extern bool g_key9;

/* ͨ����ͼ�����м�������� */
extern Vec2 getPos(int row, int col);
//ͨ����������������
//�ĸ����ĵ�������Ϸ���
extern int getColNumberFromPosition(float posX); 
//ͨ����������������
//�ĸ����ĵ�������Ϸ���
extern int getRowNumberFromPosition(float posY);  