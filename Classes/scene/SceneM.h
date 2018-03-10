#pragma once
#include "cocos2d.h"
USING_NS_CC;

enum SceneType			// �������� 
{
	kLoadingScene,		// ���س��� 
	kMenuScene,			// �˵����� 
	kLevelScene,		// �ؿ����ɳ�����ѡ�� 
	kGameScene,			// ��Ϸ���� 
	kGameOverScene,		// ��Ϸ��������
	kSelectHeroScene,	// ѡ��Ӣ�۽���
	kHeroScene,			// Ӣ��ҳ��
	kSuccessScene,		// �ɾ�ҳ��
	kSkillScene,		// ���ܺ�Ƥ��ҳ��
	kCustomScene,		// �Զ���ҳ��
	kEditorScene,		// �Զ���ҳ��2
};

enum TransitionType
{
	kTransitionNone,
	kTransitionSplitRows,
	kTransitionFade,
	kTransitionCrossFade,
	kTransitionPageTurn_false,
	kTransitionPageTurn_true,
	kTransitionZoomFlipAngular_RIGHT_OVER,
	kTransitionZoomFlipAngular_LEFT_OVER,
	kTransitionProgressRadialCCW
};

class SceneM :public Ref
{
public:
	static SceneM *getInstance();
	virtual bool init();
	/* �л����� */
	void changeScene(SceneType sceneType,TransitionType kTransitionType = kTransitionNone);
	/* ��ȡ��ǰ������ͼ�� */
	Layer *getCurScene();

private:
	Layer *_layer;
};
