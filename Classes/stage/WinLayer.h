#pragma once
#include "cocos2d.h"

USING_NS_CC;

enum WinOption
{
	nextLevel = 0,
	winBack
};

class WinLayer :public Layer
{
public:
	CREATE_FUNC(WinLayer);
	virtual bool init();
	// ʤ��ѡ��
	CC_SYNTHESIZE(int, winOption, WinOption);
	// ��ȡ����
	int getScore() { return score; };
private:
	int score;  //���շ���
};
