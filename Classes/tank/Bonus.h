#pragma once
#include "cocos2d.h"

USING_NS_CC;

enum BonusType		// ������������ 
{
	hpUp = 1,		// hp+5  
	powerUp,		// power+1
	miss,			// miss
	statusUp		
};

/* �������� */
class Bonus : public Sprite
{
public:
	Bonus();
	~Bonus();
	static Bonus* create(BonusType type, Vec2 pos);
	bool init(BonusType type,Vec2 pos);
	bool isCollidePlayer();

private:
	void update(float dt);
	/* �Ƿ������̹�˽Ӵ� */

	BonusType _type;	// ������������ 
};