#include "SuccessData.h"
#include "DataM.h"
#include "data\StayTime.h"
#include "ChineseFonts.h"

static SuccessData * s_successData = nullptr;

SuccessData *SuccessData::getInstance()
{
	if (!s_successData)
	{
		s_successData = new SuccessData();
		s_successData->init();
		assert(s_successData, "No enough memory of externData.");
	}
	return s_successData;
}

bool SuccessData::init()
{
	Document progress;
	std::string progressString = FileUtils::getInstance()->getStringFromFile("Progress.json");
	progress.Parse<kParseDefaultFlags>(progressString.c_str());

	//��ȡ�����ͷŴ���
	bigSkillTime = progress["BigSkillTime"].GetInt();
	// ��ȡ���Ƶ�ש����
	brickNum = progress["BrickNum"].GetInt();
	//��ȡ�����ӵ�����
	bulletNum = progress["BulletNum"].GetInt();
	//��ȡ��������
	deathTime = progress["DeathTime"].GetInt();
	//��ȡ����̹������
	hitTankNum = progress["HitTankNum"].GetInt();
	//��ȡ�ұ��򱬴���
	homeBreakTime = progress["HomeBreakTime"].GetInt();

	Document finishedSuccess;
	std::string finishedSuccessString = FileUtils::getInstance()->getStringFromFile("FinishedSuccess.json");
	finishedSuccess.Parse<kParseDefaultFlags>(finishedSuccessString.c_str());

	isAllLevel = finishedSuccess["AllLevel"].GetBool();
	isSkillMax = finishedSuccess["SkillMax"].GetBool();
	isBrickNum = finishedSuccess["BrickNum"].GetBool();
	isHitTankNum = finishedSuccess["HitTankNum"].GetBool();
	isBulletNum = finishedSuccess["BulletNum"].GetBool();
	isDeathTime = finishedSuccess["DeathTime"].GetBool();
	isHomeBreakTime = finishedSuccess["HomeBreakTime"].GetBool();
	isBigSkillTime = finishedSuccess["BigSkillTime"].GetBool();
	isStayTime = finishedSuccess["StayTime"].GetBool();
	isAllOpen = finishedSuccess["AllOpen"].GetBool();

	//currentFinished.clear();

	return true;
}

//�������ĺ���
void SuccessData::updateBrickNum()
{
	brickNum++;

}

void SuccessData::updateHitTankNum() 
{
	hitTankNum++;
}

void SuccessData::updateBulletNum() 
{
	bulletNum++;
}

void SuccessData::updateDeathTime() 
{
	deathTime++;
}

void SuccessData::updateHomeBreakTime() 
{
	homeBreakTime++;
}

void SuccessData::updateBigSkillTime() 
{
	bigSkillTime++;
}

void SuccessData::updateStayTime()
{
	if (!isStayTime)
	{
		isStayTime = true;
		char * temp = (FontToUTF8("��ϴ���� ���!"));
		currentFinished.push_back(temp);
		//ʱ�䵽��д��json
		updateAlldata();
	}
}

void SuccessData::updateIsSkillMax()
{
	if (!isSkillMax)
	{
		int(*SP)[5] = DataM::getInstance()->getSPMartix();
		if (SP[0][0] == 5 || SP[1][0] == 5 || SP[2][0] == 5)
		{
			isSkillMax = true;
			char * temp = (FontToUTF8("��ʦ ���!"));
			currentFinished.push_back(temp);
		}
	}
}

void SuccessData::updateIsAllLevel()
{
	if (!isAllLevel && DataM::getInstance()->get_id() == 15)
	{
		isAllLevel = true;
		char * temp = (FontToUTF8("������� ���!"));
		currentFinished.push_back(temp);
	}
}

void SuccessData::updateIsAllOpen()
{
	if (!isAllOpen)
	{
		isAllOpen = true;
		char * temp = (FontToUTF8("��˾�� ���!"));
		currentFinished.push_back(temp);
	}
}


//�ܵĽ���ɾ�
std::vector<char *> SuccessData::updateAlldata()
{
	//׼�����ص�ǰ��ɵĳɾ�
	updateFinishedSuccess();

	//����
	Document progress;
	progress.SetObject();
	rapidjson::Document::AllocatorType &allocator1 = progress.GetAllocator();

	progress.AddMember("BigSkillTime", bigSkillTime, allocator1);
	progress.AddMember("BrickNum", brickNum, allocator1);
	progress.AddMember("BulletNum", bulletNum, allocator1);
	progress.AddMember("DeathTime", deathTime, allocator1);
	progress.AddMember("HitTankNum", hitTankNum, allocator1);
	progress.AddMember("HomeBreakTime", homeBreakTime, allocator1);

	StringBuffer buffer1;
	rapidjson::Writer<StringBuffer> writer1(buffer1);
	progress.Accept(writer1);
	FILE* file1 = fopen("externData/successData/Progress.json", "wb");
	if (file1)
	{
		fputs(buffer1.GetString(), file1);
		fclose(file1);
	}

	//������гɾ�
	if (isAllLevel && isSkillMax && isBrickNum && isHitTankNum && isBulletNum && isDeathTime && isHomeBreakTime && isBigSkillTime && isStayTime)
	{
		updateIsAllOpen();
	}

	//������
	Document finishedSuccess;
	finishedSuccess.SetObject();
	rapidjson::Document::AllocatorType &allocator2 = finishedSuccess.GetAllocator();

	finishedSuccess.AddMember("AllLevel", isAllLevel, allocator2);
	finishedSuccess.AddMember("AllOpen", isAllOpen, allocator2);
	finishedSuccess.AddMember("BigSkillTime", isBigSkillTime, allocator2);
	finishedSuccess.AddMember("BrickNum", isBrickNum, allocator2);
	finishedSuccess.AddMember("BulletNum", isBulletNum, allocator2);
	finishedSuccess.AddMember("DeathTime", isDeathTime, allocator2);
	finishedSuccess.AddMember("HitTankNum", isHitTankNum, allocator2);
	finishedSuccess.AddMember("HomeBreakTime", isHomeBreakTime, allocator2);
	finishedSuccess.AddMember("SkillMax", isSkillMax, allocator2);
	finishedSuccess.AddMember("StayTime", isStayTime, allocator2);

	StringBuffer buffer2;
	rapidjson::Writer<StringBuffer> writer2(buffer2);
	finishedSuccess.Accept(writer2);
	FILE* file2 = fopen("externData/successData/FinishedSuccess.json", "wb");
	if (file2)
	{
		fputs(buffer2.GetString(), file2);
		fclose(file2);
	}

	//����һ��Vector��������ʾ�����ɶɶɶ
	std::vector<char *> tempCurrentFinished(currentFinished);
	currentFinished.clear();

	return tempCurrentFinished;
}

void SuccessData::updateFinishedSuccess()
{
	//1
	if (brickNum >= 1000 && isBrickNum == false)
	{
		isBrickNum = true;
		char * temp(FontToUTF8("��ש�� ���!"));
		currentFinished.push_back(temp);
	}
	//2
	if (hitTankNum >= 300 && isHitTankNum == false)
	{
		isHitTankNum = true;
		char * temp = (FontToUTF8("ɱ������ ���!"));
		currentFinished.push_back(temp);
	}
	//3
	if (bulletNum >= 2000 && isBulletNum == false)
	{
		isBulletNum = true;
		char * temp = (FontToUTF8("��ǹ�� ���!"));
		currentFinished.push_back(temp);
	}
	//4
	if (deathTime >= 15 && isDeathTime == false)
	{
		isDeathTime = true;
		char * temp = (FontToUTF8("�������� ���!"));
		currentFinished.push_back(temp);
	}
	//5
	if (homeBreakTime >= 20 && isHomeBreakTime == false)
	{
		isHomeBreakTime = true;
		char * temp = (FontToUTF8("�������� ���!"));
		currentFinished.push_back(temp);
	}
	//6
	if (bigSkillTime >= 30 && isBigSkillTime == false)
	{
		isBigSkillTime = true;
		char *temp = (FontToUTF8("���֮�� ���!"));
		currentFinished.push_back(temp);
	}
//�����ĸ�д������ĸ��Ե�update��
}

//�ж��Ƿ���Ƥ��
int SuccessData::DEFSkin() {
	int skinNum = 1;
	if (isBrickNum && isHitTankNum && isBigSkillTime)
		skinNum++;
	if (isAllOpen)
		skinNum++;
	return skinNum;
}

int SuccessData::SPESkin() {
	int skinNum = 1;
	if (isHomeBreakTime && isSkillMax && isDeathTime)
		skinNum++;
	if (isAllOpen)
		skinNum++;
	return skinNum;
}

int SuccessData::ATKSkin() 
{
	int skinNum = 1;
	if (isAllLevel  && isBulletNum && isStayTime)
		skinNum++;
	if (isAllOpen)
		skinNum++;
	return skinNum;
}

int SuccessData::updateSkin()
{
	int skinNum;
	switch (DataM::getInstance()->getHType())
	{
	case TypeDEF:
		skinNum = DEFSkin();
		break;
	case TypeATK:
		skinNum = ATKSkin();
		break;
	case TypeSPE:
		skinNum = SPESkin();
		break;
	}
	return skinNum;
}

//���success����-������

//��ͨ���йؿ�����
int SuccessData::getAllLevelProgress()
{
	return isAllLevel ? (LEVEL_NUM) : (DataM::getInstance()->maxLevelCanPlayed - 1); 
}  
  //�ɾ�ȫ������
int SuccessData::getAllOpenProgress()
{
	return (int)isAllLevel
		+ (int)isSkillMax
		+ (int)isBrickNum
		+ (int)isHitTankNum
		+ (int)isBulletNum
		+ (int)isDeathTime
		+ (int)isHomeBreakTime
		+ (int)isBigSkillTime
		+ (int)isStayTime
		+ (int)isAllOpen;
}	 

//�����ͷŴ�������
int SuccessData::getBigSkillTimeProgress() 
{
	return bigSkillTime; 
}  

//��ש����
int SuccessData::getBrickNumProgress()
{ 
	return brickNum; 
}  

//�ӵ�����
int SuccessData::getBulletNumProgress() 
{
	return bulletNum; 
} 

//������������
int SuccessData::getDeathTimeProgress()
{
	return deathTime; 
}  

//�ߵн���
int SuccessData::getHitTankNumProgress()
{
	return hitTankNum;
}  

//���ҽ���
int SuccessData::getHomeBreakTimeProgress()
{ 
	return homeBreakTime;
} 

//������������
int SuccessData::getSkillMaxProgress()
{

	DataM *dataM = DataM::getInstance();
	int currentTypeNum = (int)(dataM->getHType());
	int maxSkillLearned = 0;
	//ѭ��������Ӣ�����Ͳ���
	for (int i = 2; i >= 0; --i)
	{
		dataM->setHType((HeroType)((currentTypeNum + i) % 3));
		int(*SPMartix)[5] = dataM->getSPMartix();
		for (int j = 0; j < 3; j++)
		{
			maxSkillLearned = (SPMartix[j][0]>maxSkillLearned) ? SPMartix[j][0] : maxSkillLearned;
		}
	}
	return maxSkillLearned;
} 

//����ʱ��
int SuccessData::getStayTime() 
{ 
	return StayTime::getStayTime(); 
}