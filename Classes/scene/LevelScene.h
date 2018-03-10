#pragma once
#include "cocos2d.h"

USING_NS_CC;

/* �ؿ����ɳ�����ÿ����֮����ʾ�ڼ��صģ��� */
class LevelScene : public Layer
{
public:
	/*LevelScene();
	~LevelScene();*/
	CREATE_FUNC(LevelScene);
	virtual bool init();

private:
	void onExit() override;
	void onEnterTransitionDidFinish();
	void update(float dt);
	/* ������ʾ�Ĺؿ�id */
	void updateLevel();
	void setOption();
	Sprite *selectedRect;

	int _id;			// �ؿ�id ,-1Ϊ�Զ���
	bool isCanCustom;
	bool isCustom;
};
