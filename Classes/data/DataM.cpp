/***********************************************

��Ҫ��ȡSP���ؿ���Ϣ��Ƥ��ID��Ӣ�����ͣ�
�Ǻ�̨���ݹ���ĳ�������Ϸǰ�����ݺ��ⲿ���ݵ����ӵ�����

***********************************************/


#include "dataM.h"

static DataM* s_dataM = nullptr;

DataM *DataM::getInstance()
{
	if (!s_dataM)
	{
		s_dataM = new (std::nothrow) DataM();
		CCASSERT(s_dataM, "FATAL: Not enough memory");
		s_dataM->init();
	}
	return s_dataM;
}

bool DataM::init()
{
	// ��һ��ִ��ʱ�����ݻᱻ��ʼ�� ��ExternData::init()��
	externData = ExternData::getInstance();
	return true;
}
//�������ؿ�
bool DataM::updateMaxLevelCanPlayed()
{
	if (maxLevelCanPlayed == _id)
	{
		maxLevelCanPlayed++;
		externData->writeMaxLevelCanPlayed();
		return true;
	}
	return false;
}
//����������
void DataM::updateLevelMaxScoreArray(int currentLevelScore)
{
	if (currentLevelScore > levelMaxScoreArray[_id])
	{
		updateSP(currentLevelScore - levelMaxScoreArray[_id]);
		levelMaxScoreArray[_id] = currentLevelScore;
		externData->writeLevelMaxScoreArray();
	}
}
//����SP
void DataM::updateSP(int dSP)
{
	currentATKSP += dSP;
	currentDEFSP += dSP;
	currentSPESP += dSP;
	externData->writeSP();
}

// ���ص���SP�ļ�����,����ֵΪ0ʱû����Ч��û�ö��������Լ����
int DataM::addSkill(int row, int col)
{
	int spDecrement = 0;
	switch (hType)
	{
	case TypeATK:
		spDecrement = ATKAddSkill(row, col);
		break;
	case TypeDEF:
		spDecrement = DEFAddSkill(row, col);
		break;
	case TypeSPE:
		spDecrement = SPEAddSkill(row, col);
		break;
	default:
		CCASSERT(false, "No exist Type!!");
		break;
	}
	externData->readSPNeed();	//�����Զ�����,����ʣ�����
	externData->writeSPSkill();  //������hType����
	externData->writeSP();		//���µ�ǰ����SP
	return spDecrement;
}
//ATK����̹�˼ӵ�
int DataM::ATKAddSkill(int row, int col)
{
	if (ATKSPMax[row][col] > ATKSP[row][col])
	{
		int spDecrement = ATKSPNeed[row][col];
		ATKSP[row][col]++;
		currentATKSP = currentATKSP - spDecrement;
		//�Ӷ���������Ч
		return spDecrement;
	}
	else
	{
		return 0;
	}
}
//DEF����̹�˼ӵ�
int DataM::DEFAddSkill(int row, int col)
{
	if (DEFSPMax[row][col] > DEFSP[row][col])
	{
		int spDecrement = DEFSPNeed[row][col];
		DEFSP[row][col]++;
		currentDEFSP = currentDEFSP - spDecrement;
		//�Ӷ���������Ч
		return spDecrement;
	}
	else
	{
		return 0;
	}
}
//SPE����̹�˼ӵ�
int DataM::SPEAddSkill(int row, int col)
{

	if (SPESPMax[row][col] > SPESP[row][col])
	{
		int spDecrement = SPESPNeed[row][col];
		SPESP[row][col]++;
		currentSPESP = currentSPESP - spDecrement;
		//�Ӷ���������Ч
		return spDecrement;
	}
	else
	{
		return 0;
	}
}

void DataM::getAllSPMatrix(int(*&SP)[5], int(*&SPMax)[5], int(*&SPNeed)[5], int(*&SPDepend)[5])
{
	switch (hType)
	{
	case TypeATK:
		SP = ATKSP;
		SPMax = ATKSPMax;
		SPNeed = ATKSPNeed;
		SPDepend = ATKSPDepend;
		break;

	case TypeDEF:
		SP = DEFSP;
		SPMax = DEFSPMax;
		SPNeed = DEFSPNeed;
		SPDepend = DEFSPDepend;
		break;

	case TypeSPE:
		SP = SPESP;
		SPMax = SPESPMax;
		SPNeed = SPESPNeed;
		SPDepend = SPESPDepend;
		break;
	}
}
//�õ���������̹�˵�id
int DataM::getSkinId()
{
	switch (hType)
	{
	case TypeATK:
		return ATKSkinId;
		break;
	case TypeDEF:
		return DEFSkinId;
		break;
	case TypeSPE:
		return SPESkinId;
		break;
	}
}

void DataM::updateSkinId(int id)
{
	switch (hType)
	{
	case TypeATK:
		ATKSkinId = id;
		break;
	case TypeDEF:
		DEFSkinId = id;
		break;
	case TypeSPE:
		SPESkinId = id;
		break;
	}
	externData->writeSkinID();
	return;
}

int DataM::getSP()
{
	switch (hType)
	{
	case TypeATK:
		return currentATKSP;
		break;
	case TypeDEF:
		return currentDEFSP;
		break;
	case TypeSPE:
		return currentSPESP;
		break;
	}
}

int(*DataM::getSPMartix())[5]
{
	switch (hType)
	{
	case TypeATK:
		return ATKSP;
		break;
	case TypeDEF:
		return DEFSP;
		break;
	case TypeSPE:
		return SPESP;
		break;
	}
}

int DataM::getSkinId(int id)
{
	switch (hType)
	{
	case TypeATK:
		return ATKSkinId;
		break;
	case TypeDEF:
		return DEFSkinId;
		break;
	case TypeSPE:
		return SPESkinId;
		break;
	default:
		break;
	}
}