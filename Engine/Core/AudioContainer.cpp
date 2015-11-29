
#include "AudioContainer.h"
#include "fnv.h"

AudioContainer::AudioContainer(const TChar* name)
	: containerName(name),
	containerID(Aer::fnvHash(name)),
	child(nullptr),
	parent(nullptr), 
	sibling(nullptr)
{
}

AudioContainer::~AudioContainer()
{
	delete child;
	delete sibling;
}

void AudioContainer::SetChild(AudioContainer* container)
{
	child = container;
}

void AudioContainer::SetParent(AudioContainer* container)
{
	parent = container;
	PostAdd();
}

void AudioContainer::SetSibling(AudioContainer* container)
{
	sibling = container;
}

AudioContainer* AudioContainer::GetChild()
{
	return child;
}

AudioContainer* AudioContainer::GetParent()
{
	return parent;
}

AudioContainer* AudioContainer::GetSibling()
{
	return sibling;
}