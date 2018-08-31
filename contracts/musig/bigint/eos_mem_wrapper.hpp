/**
 *  new/delete operator overloading for eosio smart contract ( on dawn2.x )
 * 
 * @copyright Mithrilcoin.io
 */
#ifndef __EOS_MEM_WRAPPER_H__
#define __EOS_MEM_WRAPPER_H__

#include <eosiolib/memory.h>

void *operator new(size_t size);
void *operator new[](size_t size);
void operator delete(void *ptr);
void operator delete[](void *ptr);
#endif