#pragma once
#include "cocos2d.h"
#include "data\SkillDetail.h"
#include "data\DataM.h"
#include "ui\UIScale9Sprite.h"

using namespace ui;
USING_NS_CC;

class SkillScene :public Layer
{
public:
	CREATE_FUNC(SkillScene);
	virtual bool init();

private:
	//�Ϸ����
	Scale9Sprite *upSelectedRect;
	//�·����
	Sprite *downSelectedRect;
	//����ҳ���·���ɫ���
	Sprite *rectBG;
	//����������ǩ
	Label *starAllNumLabel;
	//���������ǩ
	Label *starNeedNumLabel;
	//������������
	Sprite *starAll;
	//�������辫��
	Sprite *starNeed;
	//��������,ê����0
	Label *skillDiscribeLabel;  
	//�������ƣ�ê����0
	Label *skillNameLabel;
	//��������
	int starAllNum;
	//��������
	int starNeedNum;
	//�Ϸ�ѡ��
	int option;
	//�������
	int row;
	//�������
	int col;
	//SP����
	int(*SP)[5];
	//SPMax����
	int(*SPMax)[5];
	//SPNeed����
	int(*SPNeed)[5];
	//SP��������
	int(*SPDepend)[5];

	// �Ƿ����·�ҳ��
	bool detailLayer;
	//��ǰ��̹������
	HeroType heroType;

	//Ƥ��ѡ��
	int skinId;
	//Ƥ������
	int skinNum;
	//Ƥ������
	int skinMax;

	DataM *dataM;
	SkillDetail *skillDetail;

	void onExit();
	void onEnterTransitionDidFinish();
	void update(float dt);
};
