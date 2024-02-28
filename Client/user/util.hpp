#pragma once

#define UNIQUE_NAME(prefix)	_CONCAT(prefix ## _, __COUNTER__) ## _CONCAT(at, __LINE__)

#define _synchronized(lock, name, mtx)	if (lock name(mtx); true)
#define synchronized_read(smtx)	_synchronized(std::shared_lock<decltype(smtx)>, UNIQUE_NAME(rdLock), smtx)
#define synchronized_write(mtx)	_synchronized(std::unique_lock<decltype(mtx)>, UNIQUE_NAME(lock), mtx)
/*
	it mimics the behaviour of the Java construct
	"synchronized(this) { }"
*/
#define synchronized(mtx)	synchronized_write(mtx)
/*
	to secure a code-block, use the following syntax:
	"{ SYNCHRONIZED(mutex); <commands> }"
*/
#define SYNCHRONIZED(mtx)	std::scoped_lock UNIQUE_NAME(lock)(mtx)