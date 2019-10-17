/*--------------------------------------------------------------------------------------*/
// Name: practica_futex.c								*/
// Author: Alejandro Valero y Ruben Gran 
// Copyright: Universidad de Zaragoza
// Date: 12/12/2018
// Description: Mutex implementation and performance assesment
/*--------------------------------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <linux/futex.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <limits.h>
#include <stdint.h>
#include <inttypes.h>
#include <iostream>
#include "cdh.hpp"

cdh::cdh(){
	
	futex_suspension = valor_comparacion;
	durmiendo = 0;
	
}


cdh::~cdh()
{

//procederia despertar a todos por ultima vez?

}

void cdh::adormir(){
	// si el valor de futex_suspension y el de valor_comparaciÃn son iguales, el hilo quedara suspendido (dormido)
	this.durmiendo ++;
	syscall(__NR_futex, &(this.futex_suspension), FUTEX_WAIT, this.valor_comparacion, NULL, 0, 0);
}

void cdh::despertar(){
	this.durmiendo = 0;
	syscall(__NR_futex, &(this.futex_suspension), FUTEX_WAKE, INT_MAX, NULL, 0, 0);

}

