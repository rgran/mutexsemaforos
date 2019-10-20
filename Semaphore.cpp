//*****************************************************************
// File:   Semaphore.cpp
// Author: PSCD-Unizar
// Date:   octubre 2016
// Coms:   Ver Semaphore.h
//         La implementación se entenderá cuando veamos variables
//         condición y monitores
//*****************************************************************

//Infoŕmación útil para entender la implementación en
//http://en.cppreference.com/w/cpp/thread/condition_variable
//La estudiaremos con más detalle cuando tratemos en la asignatura la parte de "monitores"

//"The condition_variable class is a synchronization primitive that can be used to block a thread,
//or multiple threads at the same time, until:
//a notification is received from another thread
//a timeout expires, or
//a spurious wakeup occurs
//Any thread that intends to wait on std::condition_variable has to acquire a std::unique_lock first.
//The wait operations atomically release the mutex and suspend the execution of the thread. When the
//condition variable is notified, the thread is awakened, and the mutex is reacquired.
//Condition variables permit concurrent invocation of the wait, wait_for, wait_until, notify_one and
//notify_all member functions."

#include <Semaphore.hpp>


//----------------------------------------------------------
Semaphore::Semaphore(int n) {
    assert(n >= 0);           //aborta si se viola la Pre
    count = n;
    initialized = true;       //ya está inicializad
	
}
//----------------------------------------------------------
Semaphore::Semaphore() {
    initialized = false;      //habrá que inicializarlo
}
//----------------------------------------------------------
Semaphore::~Semaphore() {
    //nada que hacer

}
//----------------------------------------------------------
void Semaphore::adormir(int ve){
syscall(__NR_futex, &(count), FUTEX_WAIT, ve, NULL, 0, 0);
}
//----------------------------------------------------------
void Semaphore::despertar(){
	syscall(__NR_futex, &(count), FUTEX_WAKE, INT_MAX, NULL, 0, 0);
}
//----------------------------------------------------------
void Semaphore::setInitValue(int n) {

    mtx.lock();

    assert(!initialized && n >= 0);

    count = n;
    initialized = true;

    mtx.unlock();
}
//----------------------------------------------------------
void Semaphore::signal() {

	mtx.lock();

    assert(initialized);

    count++;
	
	despertar();

	mtx.unlock();
}
//----------------------------------------------------------
void Semaphore::wait() {
	
	mtx.lock();

    assert(initialized);

    while(count == 0) {
		int vr = count;		
		mtx.unlock();
		adormir(vr);
//		cola_suspendidos.adormir();
		mtx.lock();
    }
    count--;

	mtx.unlock();
}
//----------------------------------------------------------
void Semaphore::signal(int n) {
	
	mtx.lock();

    assert(initialized && n>0);

    count = count+n;
//	cola_suspendidos.despertar(); 

	mtx.unlock();
}
//----------------------------------------------------------
void Semaphore::wait(int n) {
	
	mtx.lock();

    assert(initialized && n>0);

    while(count < n) {
		int vr = count; 
		mtx.unlock();
		adormir(vr);
//		cola_suspendidos.adormir();
		mtx.lock();
    }
    count = count-n;

	mtx.unlock();
}
