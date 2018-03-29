
#include "System.h"
#include "Sound.h"
#include "Handles.h"
#include "EffectsDefinitions.h"
#include "EffectsManager.h"
#include "EventProcessor.h"
#include "PauseEvent.h"
#include "PlayEvent.h"
#include "SoundGroupManager.h"
#include "MainEffectContainer.h"
#include "SoundContainer.h"
#include "AerisUtilities.h"
#include "Music.h"

int main()
{
	AerEngineSettings initSettings;

	Aer::SoundEngine::Initialize(initSettings);

	Aer::SimpleReverbDescription desc;
	Aer::DefaultEffectSettings(&desc);
	desc.effectName = "Effect";
	Aer::Handle* sndHandle0 = Aer::CreateSound("arrowSound.wav", "Arrow Twang");
	Aer::Handle* sndHandle1 = Aer::CreateSound("Love and Feeling.wav", "Music1");

	//sndHandle0->Play();
	//sndHandle1.Play();
	//EventProcessor::AddEvent(new Pause(sndHandle0));
	//int count = 0;
	//bool played = false;

	// Sound Group test
	//*
	//AerEffect* eff = EffectsManager::CreateEffect(desc);

	MainEffectContainer* testGroupRoot = SoundGroupManager::CreateGroup("TestGroup");
	//testGroupRoot->SetEffect(eff->GetID());

	HierarchyContainer* hierContainer = new HierarchyContainer("TestHierarchy", 3);
	SoundGroupManager::AddContainer(hierContainer, testGroupRoot);

	SoundContainer* snd = new SoundContainer("TestSoundContainer", "Arrow Twang");
	SoundGroupManager::AddContainer(snd, hierContainer);

	SoundContainer* snd1 = new SoundContainer("TestContainer1", "Music1");
	SoundGroupManager::AddContainer(snd1, hierContainer);


	sndHandle0;// ->Play();
	sndHandle1->Play();
			   //*/

			   // Streaming Test
			   //Aer::Handle* musHandle = Aer::CreateMusic("Love and Feeling.wav", "Chet Streamed");
			   //Aer::Handle* musHandle = Aer::CreateMusic("arrowSound.wav", "Arrow");
			   //musHandle->Play();


	for (;;)
	{
		EventProcessor::ProcessEvents();
		/*if (count > 1000000)
		{
		EventProcessor::AddEvent(new Pause(sndHandle0));
		played = true;
		count = 0;
		}
		if (!played)
		{
		++count;
		}*/
	}

	//	return 0;
}	