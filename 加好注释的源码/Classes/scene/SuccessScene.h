/***********************************************

�����ά���ɾ�ҳ����������ڣ���Ҫ�����ɾ�ҳ���ǰ����Ϣ��
��SuccessData�л�õ�ǰ�ɾ͵Ľ�������

***********************************************/

#pragma once
#include<iostream>
#include"cocos2d.h"
USING_NS_CC;

/*�ɾͳ���*/
class SuccessScene : public Layer {
public:
	CREATE_FUNC(SuccessScene);
	virtual bool init();
private:
	void onExit();
	void onEnterTransitionDidFinish();
	void update(float dt);
};
