/***********************************************

�������������Զ����ͼѡ��ҳ��
�����Զ����ͼѡ��ҳ�水ť���֡�������ת����������Ч����

***********************************************/

#pragma once
#include"cocos2d.h"
#include<iostream>
#include "ui\UIScale9Sprite.h"//cocos2d�ľŹ�������
#include <vector>//����������
#include <fstream>//c++���ļ���д��

USING_NS_CC;
using namespace ui;


class EditScene :public Layer {
public:
	CREATE_FUNC(EditScene);
	virtual bool init();
	Vec2 getPosition(int x, int y);//����ҳ�水ť��������꣬�������ڸ��ڵ�ľ���λ��
private:
	void update(float dt);//֡ˢ��
	void moveArrow();//����ƶ�
	void readName();//�ļ���ȡ
	void saveName();//�ļ�����
	void initMapChoice();//��ʼ���ļ������UIϵͳ
	void updateMapChoice();//�ļ������UIϵͳ�ĸ���

	int mapNumMax = 0;//��ǰ����ĵ�ͼ��
	Scale9Sprite*_arrow;//���
	/* ָʾ��ť���������Ĳ���*/
	int option1;//���߰�ť�����λ��
	int option2;//�Ұ�߰�ť�����λ��
	int option3;//�Ѷ�ѡ��ť
	int option4;
	Sprite* difficulty[5];//�Ѷ�UI�Ĵ洢��
	
	std::vector<Sprite*> mapChoice;//�ļ������UIϵͳ
	int enemyDifficulty=0;//��Ϸ�Ѷ�
	std::vector<std::string> mapNames;//��ͼ����
	int mapNumber=-1;//��ͼѡ��
};
