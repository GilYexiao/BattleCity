/***********************************************

��Ҫ�洢Ӣ��ҳ�漼����Ϣ����ϸ����

***********************************************/

#include "SkillDetail.h"
#include "ChineseFonts.h"

static SkillDetail* _skillDetail = nullptr;

SkillDetail *SkillDetail::getInstance()
{
	if (nullptr == _skillDetail)
	{
		_skillDetail = new (std::nothrow) SkillDetail();
		_skillDetail->init();
		CCASSERT(_skillDetail, "No memory to create _skillDetail");
	}
	return _skillDetail;
}

bool SkillDetail::init()
{
	return true;
}

//�õ��������ƣ�����char*
char *SkillDetail::getSkillName(int row, int col)
{
	SP = DataM::getInstance()->getSPMartix();
	char *nameInChinese = "";
	if (0 == col)
	{
		switch (row)
		{
		case 0:
			if (SP[row][col] < 5)
			{
				String *name = String::createWithFormat("�͹� Lv%d", SP[row][col] + 1);
				nameInChinese = const_cast<char *>(name->getCString());
			}
			else  //������
			{
				nameInChinese = "�͹� Lv5 �Ѽ���";
			}
			break;
		case 1:
			if (SP[row][col] < 5)
			{
				String *name = String::createWithFormat("�ؼ� Lv%d", SP[row][col] + 1);
				nameInChinese = const_cast<char *>(name->getCString());
			}
			else  //������
			{
				nameInChinese = "�ؼ� Lv5 �Ѽ���";
			}
			break;
		case 2:
			if (SP[row][col] < 5)
			{
				String *name = String::createWithFormat("���� Lv%d", SP[row][col] + 1);
				nameInChinese = const_cast<char *>(name->getCString());
			}
			else  //������
			{
				nameInChinese = "���� Lv5 �Ѽ���";
			}
			break;
		}
	}
	else  //col !=0
	{

		switch (DataM::getInstance()->getHType())
		{
		case TypeATK:
			if (2 == col)
			{
				if (row>=0 &&row <= 2)
					nameInChinese = "����ȫ��";
				else if (3 == row)
					nameInChinese = "ά����";
			}
			else if (3 == col)
			{
				if (row >= 1 && row <= 3)
					nameInChinese = "��������";
			}
			else if (4 == col)
			{
				if (2 == row)
					nameInChinese = "�ۻ����";
				else if (3 == row)
					nameInChinese = "���⿪��";
			}
			break;
		case TypeDEF:
			if (2 == col)
			{
				if (row <= 1 && row >= 0)
					nameInChinese = "����ȫ��";
				else if (row == 2)
					nameInChinese = "������־";
			}
			else if (3 == col)
			{
				if (row >= 0 && row <= 1)
					nameInChinese = "��������";
				else if (2 == row)
					nameInChinese = "�����ữ";
				else if (3 == row)
					nameInChinese = "�޵�֮ʦ";
			}
			break;
		case TypeSPE:
			if (2 == col)
			{
				if (row >= 0 && row <= 1)
					nameInChinese = "��";
				else if(2 == row)
					nameInChinese = "��";
			}
			else if (3 == col)
			{
				if (row <= 2 && row >= 1)
					nameInChinese = "��";
			}
			else if (4 == col)
			{
				if (row <= 3 && row >= 1)
					nameInChinese = "��";
			}
			break;
		default:
			break;
		}
	}
	return FontToUTF8(nameInChinese);
}

//�õ���������������char*
char *SkillDetail::getSkillDescribe(int row, int col)
{
	char *nameInChinese = "";
	if (0 == col)
	{
		switch (row)
		{
		case 0:
				nameInChinese = "������+10";
			break;
		case 1:
				nameInChinese = "������+10";
			break;
		case 2:
				nameInChinese = "�ٶ�+10";  //��λ px/20frame
			break;
		}
	}
	else  //col !=0
	{

		switch (DataM::getInstance()->getHType())
		{
		case TypeATK:
			if (2 == col)
			{
				if (row >= 0 && row <= 2)
					nameInChinese = "�ӵ��ٶ�+40";  //��λpx/20frame
				else if (3 == row)
					nameInChinese = "�ռ����ܣ���ǹ��  ��ȴʱ��-15��";
			}
			else if (3 == col)
			{
				if (row >= 1 && row <= 3)
					nameInChinese = "�ӵ�������������+1";
			}
			else if (4 == col)
			{
				if (2 == row)
					nameInChinese = "������������";
				else if (3 == row)
					nameInChinese = "��ͨ������ɷ�Χ�˺���������������";
			}
			break;
		case TypeDEF:
			if (2 == col)
			{
				if (row <= 1 && row >= 0)
					nameInChinese = "�ӵ��ٶ�+40";
				else if (row == 2)
					nameInChinese = "�����󸴻�һ�Σ����100HP";
			}
			else if (3 == col)
			{
				if (row >= 0 && row <= 1)
					nameInChinese = "�ӵ�������������+1";
				else if (2 == row)
					nameInChinese = "�����˺�-10";
				else if (3 == row)
					nameInChinese = "�ռ����ܣ�ʥ��ʿ  ����ʱ��+5��";
			}
			break;
		case TypeSPE:
			if (2 == col)
			{
				if (row >= 0 && row <= 1)
					nameInChinese = "������ȴʱ��-0.1�룬��˸��ȴʱ��-1.0��";
				else if (2 == row)
					nameInChinese = "�ռ����ܣ���  ��˸����+1����˸��ȴʱ��-2��";
			}
			else if (3 == col)
			{
				if (row <= 2 && row >= 1)
					nameInChinese = "���ڹ�������+1��";
			}
			else if (4 == col)
			{
				if (row <= 3 && row >= 1)
					nameInChinese = "����15%�ر���";
			}
			break;
		default:
			break;
		}
	}
	return FontToUTF8(nameInChinese);
}

char *SkillDetail::getSkinName()
{
	HeroType hTyoe = DataM::getInstance()->getHType();
	int skinId = DataM::getInstance()->getSkinId();
	char *nameInChinese;
	switch (hTyoe)
	{
	case TypeATK:
		if (0 == skinId)
		{
			nameInChinese = "������Ƥ��";
		}
		else if (1 == skinId)
		{
			nameInChinese = "�����Ͷ����Ƥ��";
		}
		else if (2 == skinId)
		{
			nameInChinese = "�����Ϳ����ߵ���ר�ü�ͷƤ��";
		}
		break;
	case TypeDEF:
		if (0 == skinId)
		{
			nameInChinese = "������Ƥ��";
		}
		else if (1 == skinId)
		{
			nameInChinese = "��������ʥ��Ƥ��";
		}
		else if (2 == skinId)
		{
			nameInChinese = "�����Ϳ����ߵ���ר�ü�ͷƤ��";
		}
		break;
	case TypeSPE:
		if (0 == skinId)
		{
			nameInChinese = "�ٶ���Ƥ��";
		}
		else if (1 == skinId)
		{
			nameInChinese = "�ٶ���ʥ����Ƥ��";
		}
		else if (2 == skinId)
		{
			nameInChinese = "�ٶ��Ϳ����ߵ���ר�ü�ͷƤ��";
		}
		break;
	default:
		break;
	}
	return FontToUTF8(nameInChinese);
}