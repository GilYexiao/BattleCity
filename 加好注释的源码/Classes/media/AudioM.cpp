/***********************************************

�ýӿ�Ԥ�������������ѷ�������û��ʹ��
����һ�������洢��Ч����

***********************************************/

#include "AudioM.h"

void AudioM::preloadAllAudio()
{
	const char* audio[] = {""};
	for (auto name : audio)
	{
		AudioEngine::preload(name);
	}
}

//int AudioM::play2d(const std::string& filePath, bool loop, float volume, const AudioProfile *profile)
//{
//	///* �ؿ�������Ч�ڼ䣬���˱�ը����ͣ��Ч���⣬������Ч�������� */
//	//if (_startAudioPlaying == true && filePath != A_PAUSE && filePath != A_ENEMY_BOMB && filePath != A_PLAYER_BOMB) return INVALID_AUDIO_ID;
//	//auto audioID = AudioEngine::play2d(filePath, loop, volume, profile);
//	//if (filePath == A_START)
//	//{
//	//	_startAudioPlaying = true;
//	//	AudioM::setFinishCallback(audioID, [&](int id, const std::string& filePath) {
//	//		_startAudioPlaying = false;
//	//		NotificationCenter::getInstance()->postNotification("start_audio_end");
//	//	});
//	//}
//	//return audioID;
//	
//	//AudioM::setFinishCallback(,)
//}