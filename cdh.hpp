/*--------------------------------------------------------------------------------------*/
// Name: practica_futex.c								*/
// Author: Alejandro Valero y Ruben Gran 
// Copyright: Universidad de Zaragoza
// Date: 12/12/2018
// Description: Mutex implementation and performance assesment
/*--------------------------------------------------------------------------------------*/

#ifndef CDH_HPP
#define CDH_HPP

#include <atomic>

class cdh
{
  private:
    const int valor_comparacion = 100; //valor contra el que se compara el de futex_suspensiÃ³n y lograr la suspensiÃ³n del proceso  
    int futex_suspension;
    std::atomic<int> durmiendo; //cuantos hilos hay esperando
  public:
	cdh();
	~cdh();
    void adormir();
    void despertar();
  private:
	//friend class Lock;
};

#endif
