/***********************************************

����һ���ɾ����ݵĹ���ϵͳ����Ҫ���ܰ�����
�ⲿ�ɾ�Json�Ķ�д����ǰ��Ϸ��ʱ�ɾ͵ĸ��£�
����Ҫͨ��update�����ӿ�����ɣ����Լ��ɾ���ɵ��ж�

***********************************************/

#pragma once
#include "json\rapidjson.h"
#include "json\writer.h"
#include "json\document.h"
#include "cocos2d.h"
#include "data\Global.h"
#include "data\DataM.h"

USING_NS_CC;
using namespace rapidjson;
class SuccessData 
{
public :
	static SuccessData *getInstance();
	//�������Ľӿ�
	//���³���ʱ��
	void updateStayTime();
	//���´��Ƶ�ש����
	void updateBrickNum();
	//���´����̹����Ŀ
	void updateHitTankNum();
	//�����õ����ӵ���Ŀ
	void updateBulletNum();
	//������������
	void updateDeathTime();
	//���¼ұ��򴩵Ĵ���
	void updateHomeBreakTime();
	//���·Ŵ��еĴ���
	void updateBigSkillTime();
	//���⼼�ܴﵽ����������ؿ����
	void updateIsSkillMax();
	//����ͨ��,�������ؿ����
	void updateIsAllLevel();
private:
	//��ͨ���гɾ�
	void updateIsAllOpen();

public:

	//���³ɾ�����õ�Ƥ��
	int updateSkin();
	//��Ϸ����ʱд������
	std::vector<char *> updateAlldata();

	//���success����-������
	int getAllLevelProgress();  //��ͨ���йؿ�����
	int getAllOpenProgress();	  //�ɾ�ȫ������
	int getBigSkillTimeProgress();  //�����ͷŴ�������
	int getBrickNumProgress(); //��ש����
	int getBulletNumProgress(); //�ӵ�����
	int getDeathTimeProgress();  //������������
	int getHitTankNumProgress(); //�ߵн���
	int getHomeBreakTimeProgress(); //���ҽ���
	int getSkillMaxProgress(); //������������
	int getStayTime();	//����ʱ��

	bool isAllLevelFinished() { return isAllLevel; }//�Ƿ�ͨ�����еĹؿ�
	bool isSkillMaxFinished() { return isSkillMax; }//���⼼������
	bool isBrickNumFinished() { return isBrickNum; } //���Ƶ�ש����
	bool isHitTankNumFinished() { return isHitTankNum; } //�����̹����Ŀ
	bool isBulletNumFinished() { return isBulletNum; }//�õ����ӵ���Ŀ
	bool isDeathTimeFinished() { return isDeathTime; }//��������
	bool isHomeBreakTimeFinished() { return isHomeBreakTime; } // �ұ��򴩵Ĵ���
	bool isBigSkillTimeFinished() { return isBigSkillTime; }//�Ŵ��еĴ���
	bool isStayTimeFinished() {return isStayTime; }//����ʱ��
	bool isAllOpenFinished() {return isAllOpen; } //�Ƿ�ȫ����ͨ
										
private:
	bool init(); //���ⲿ��ȡ����

	//�ж��Ƿ�õ�Ƥ��
	int DEFSkin();
	int SPESkin();
	int ATKSkin();

	//Progress.json�ⲿ��д
	int brickNum; //���Ƶ�ש������
	int	hitTankNum; //�����̹����Ŀ��
	int bulletNum;//�õ����ӵ���Ŀ��
	int deathTime; //����������
	int homeBreakTime; // �ұ��򴩵Ĵ�����
	int bigSkillTime; //�Ŵ��еĴ�����

	//FinishedSuccess.json�ⲿ��д
	bool isAllLevel; //�Ƿ�ͨ�����еĹؿ�		Finished
	bool isSkillMax; //���⼼������			Finished
	bool isBrickNum; //���Ƶ�ש����			Finished
	bool isHitTankNum; //�����̹����Ŀ		Finished
	bool isBulletNum;//�õ����ӵ���Ŀ			Finished
	bool isDeathTime; //��������				Finished
	bool isHomeBreakTime; // �ұ��򴩵Ĵ���	Finished
	bool isBigSkillTime; //�Ŵ��еĴ���		Finished
	bool isStayTime; //����ʱ��				Finished
	bool isAllOpen;  //�Ƿ�ȫ����ͨ			Finished

	void updateFinishedSuccess();

	//��ǰ��ɵĳɾͣ���Ϸʤ����ʧ�ܡ���ͣ����ʱ�ᱻ��飬���
	std::vector<char *> currentFinished;


};