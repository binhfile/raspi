#include <thread.h>
#include <unistd.h>

using namespace lib::platform;
Thread::Thread(ROUTINE fxn){
	m_fxn = fxn;
	m_obj = 0;
	m_isRunning = false;
	m_isTerminate = true;
	m_threadHandle = -1;
}
Thread::~Thread(){
	stop(100);
}
int Thread::start(void* obj){
	int ret = -1;
	if(!isRunning()){
		m_obj = obj;
		m_isTerminate = false;
		pthread_create(&m_threadHandle, 0, run, this);
		ret = 0;
	}
	return ret;
}
int Thread::stop(int timeout){
	if(isRunning()){
		m_isTerminate = true;
		pthread_join(m_threadHandle, 0);
	}
	return 0;
}
bool Thread::isRunning(){
	return m_isRunning;
}
void Thread::sleepMs(int ms){
	usleep(1000 * ms);
}
void Thread::sleepUs(int us){
	usleep(us);
}
void* Thread::run(void *param){
	Thread* inst = (Thread*)param;
	inst->m_isRunning = true;
	if(inst->m_fxn){
		inst->m_fxn(inst->m_obj, &inst->m_isTerminate);
	}
	inst->m_isRunning = false;
	return 0;
}
