/***********************************************

��������Ϸ���˵���ҳ�棬
��Ҫ���ܰ�����������ҳ�����ת����Ч�Ĺ���

***********************************************/

#pragma once
#include "cocos2d.h"
USING_NS_CC;

//��ѡ���ö��
enum Option
{
	start = 0,
	hero,
	success
};

class MenuScene :public Layer
{
public:
	CREATE_FUNC(MenuScene);
	virtual bool init();

private:
	Sprite *gear;
	Sprite *background;
	int option;

	void onExit();//�����л�����
	void onEnterTransitionDidFinish();//�����л�����
	void update(float dt);
};
