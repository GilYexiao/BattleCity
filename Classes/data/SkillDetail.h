#pragma once
#include "cocos2d.h"
#include "DataM.h"
USING_NS_CC;

class SkillDetail :public Ref
{
public:
	static SkillDetail *getInstance();
	bool init();
	//�õ��������ƣ�����char*
	char *getSkillName(int row, int col);
	//�õ���������������char*
	char *getSkillDescribe(int row, int col);
	//�õ�Ƥ������
	char *getSkinName();
private:
	int (*SP)[5];
};
