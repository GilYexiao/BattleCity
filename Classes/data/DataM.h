#pragma once
#include "ExternData.h"
#include "cocos2d.h"
#include "Global.h"
#include "TankData.h"

USING_NS_CC;

enum HeroType
{
	TypeATK = 0,
	TypeDEF,
	TypeSPE,
};

class ExternData;
class DataM :public Layer
{
	// �˴��ƻ���װ������������
	friend class ExternData;
	friend class TankData;
public:
	virtual bool init() override;
	static DataM *getInstance();
	CC_SYNTHESIZE(int, _id, _id); //�Զ���Ϊ-1
	CC_SYNTHESIZE(HeroType, hType, HType);
	//�Զ���з�̹���Ѷ� ��0��4
	CC_SYNTHESIZE(int, enemyDifficulty, EnemyDifficulty);
	CC_SYNTHESIZE(std::string, mapName, MapName);

	// �������ͨ�عؿ�
	bool updateMaxLevelCanPlayed();
	// ����ÿ�����SP,�ؿ���ʱΪDataM�е�_id
	void updateLevelMaxScoreArray(int currentLevelScore);
	// ���SP������Ϊ��
	void updateSP(int dSP);
	// ����Ƥ��ID,�����ĸ���hType����,�Զ�д��json
	void updateSkinId(int id);
	//�õ�Ƥ��ID
	int getSkinId(int id);
	// �˴�û�з�װ������������
	int maxLevelCanPlayed;
	// ÿһ�ص����SP  �˴�json��һ����ֵд����0����Ϊ��һ�ص�������1
	int levelMaxScoreArray[LEVEL_NUM + 1];
	// �Ӽ��ܺ������������ã�����SP�ļ�����
	int addSkill(int row, int col);
	// ��ȡ��ǰ���еļӵ����
	void getAllSPMatrix(int(*&SP)[5], int(*&SPMax)[5], int(*&SPNeed)[5], int(*&SPDepend)[5]);
	// ��ȡ��ǰ�ӵ����
	int(*getSPMartix())[5];
	// ��õ�ǰƤ��ID����õ�������hType����
	int getSkinId();
	// ��õ�ǰSP��������õ�������hType����
	int getSP();

private:
	ExternData *externData;
	int ATKSP[5][5];		//������̹�˼ӵ�
	int ATKSPMax[5][5];		//������̹�����ӵ�
	int ATKSPNeed[5][5];	//������̹�˼ӵ�����
	int ATKSPDepend[5][5];	//������̹��ǰ�þ�����λ����������������������Ϊ1111.

	int DEFSP[5][5];		//������̹�˼ӵ�
	int DEFSPMax[5][5];		//������̹�����ӵ�
	int DEFSPNeed[5][5];	//������̹�˼ӵ�����
	int DEFSPDepend[5][5];	//������̹��ǰ�þ�����λ����������������������Ϊ1111.

	int SPESP[5][5];		//�ٶ���̹�˼ӵ�
	int SPESPMax[5][5];		//�ٶ���̹�����ӵ�
	int SPESPNeed[5][5];	//�ٶ���̹�˼ӵ�����
	int SPESPDepend[5][5];	//������̹��ǰ�þ�����λ����������������������Ϊ1111.

	int ATKAddSkill(int row, int col);	//�����ͼӵ���ϸ
	int DEFAddSkill(int row, int col);	//�����ͼӵ���ϸ
	int SPEAddSkill(int row, int col);	//�ٶ��ͼӵ���ϸ


	int ATKSkinId;			//������Ƥ��ID
	int DEFSkinId;			//������Ƥ��ID
	int SPESkinId;			//�ٶ���Ƥ��ID

	// ��ǰATKSP
	int currentATKSP;
	// ��ǰDEFSP
	int currentDEFSP;
	// ��ǰSPESP
	int currentSPESP;
};