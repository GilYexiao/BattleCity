#pragma once
#ifndef __AUDIO_M_H__
#define __AUDIO_M_H__

#include "cocos2d.h"
#include "AudioEngine.h"

USING_NS_CC;
using namespace experimental;


/* ���������� */
class AudioM : public AudioEngine
{
public:
	/* Ԥ�������� */
	static void preloadAllAudio();
	/* ��д����play2d�����������Ϸ�Լ����߼� */
	//static int play2d(const std::string& filePath, bool loop = false, float volume = 1.0f, const AudioProfile *profile = nullptr);

private:

};

#endif