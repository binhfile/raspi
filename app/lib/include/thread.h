#ifndef THREAD_H__
#define THREAD_H__
#include <pthread.h>
namespace lib{
namespace platform{
class Thread{
public:
	typedef void (*ROUTINE)(void* obj, bool* terminate);
	Thread(ROUTINE fxn);
	virtual ~Thread();
	int start(void* obj);
	int stop(int timeout);
	bool isRunning();

    static void sleepMs(int ms);
    static void sleepUs(int us);
private:
	ROUTINE m_fxn;
	void*	m_obj;
	bool	m_isRunning;
	bool	m_isTerminate;

	pthread_t m_threadHandle;

    static void* run(void *param);
};
}
}
#endif
