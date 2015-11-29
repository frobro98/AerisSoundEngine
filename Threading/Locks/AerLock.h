#pragma once

#include <mutex>

// Aeris mutex lock
// In most cases, don't use this mutex
// Use AerScopedLock
class AerLock final
{
public:
	AerLock()
	{
	}

	AerLock(const AerLock&) = delete;
	AerLock& operator=(const AerLock&) = delete;

	void lock()
	{
		_mut.lock();
	}

	void unlock()
	{
		_mut.unlock();
	}

private:
	friend class AerCondVar;

	std::mutex _mut;

};

// Aeris Scoped Lock
class AerScopedLock final
{
public:
	AerScopedLock()
	{
		_lock.lock();
	}
	~AerScopedLock()
	{
		_lock.unlock();
	}

	AerScopedLock(const AerScopedLock&) = delete;
	AerScopedLock& operator=(const AerScopedLock&) = delete;

private:
	AerLock _lock;
};