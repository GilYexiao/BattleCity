/***********************************************

��Ҫ��ȡ�ⲿJson�ļ���
��Ϊ��Ϸ�ڲ����ݺ��ⲿ�ļ����ݶԽӵ�����

***********************************************/

#pragma once
#include "json\rapidjson.h"
#include "json\writer.h"
#include "json\document.h"
#include "cocos2d.h"
#include "DataM.h"
USING_NS_CC;
using namespace rapidjson;
class DataM;
class ExternData
{
public:
	// �˴��ƻ���װ������������
	friend DataM;
	// ˢ���ݶȼӵ�
	void changeToGradSP(int(*SPNeed)[5], int(*SP)[5]);

private:

	static ExternData *getInstance();

	bool init();		// ���ⲿ��ȡ����

	// ��SPNeed��ע�⣬���ĸ���hType��������
	void readSPNeed();

	//д�����ͨ�������ļ�
	void writeMaxLevelCanPlayed();

	//д��LevelMaxScoreArray�����ļ�
	void writeLevelMaxScoreArray();

	//д��SP�����ļ���3��������
	void writeSP();

	////д��SPMax���ļ�,ע�⣬д�ĸ���hType��������
	//void writeSPMax();

	//д��SP���ļ�,ע�⣬д�ĸ���hType��������
	void writeSPSkill();

	//д��SkinID���ļ�,3��������
	void writeSkinID();

	DataM *dataM;

};