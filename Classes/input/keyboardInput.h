#pragma once
#include "cocos2d.h"
USING_NS_CC;

enum KeyTag
{
	kKeyUpTag,	//W��
	kKeyRightTag, //D��
	kKeyDownTag, //S��
	kKeyLeftTag, //A��
	kKeySelctTag,
	kKeyStartTag,
	kKeyBTag,  //K��
	kKeyATag,  //J��
	kKeyQTag,
	kKeyETag,
	kKeyRTag,
	kKeyTTag,
	kKeyYTag,
	kKeyUTag,
	kKeyITag,
	kKeyOTag,
	kKeyPTag,
	kKeyFTag,
	kKeyGTag,
	kKeyHTag,
	kKeyLTag,
	kKeyZTag,
	kKeyXTag,
	kKeyCTag,
	kKeyVTag,
	kKey_BTag,
	kKeyNTag,
	kKeyMTag,
};

class KeyboardInput :public Layer
{
public:
	KeyboardInput();
	~KeyboardInput();
	CREATE_FUNC(KeyboardInput);
	virtual bool init();

private:
	/* ���ð���״̬ */
	void setKeyState(EventKeyboard::KeyCode keyCode, bool state);
};
