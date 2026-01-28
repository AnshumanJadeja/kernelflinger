/*
function needed for compiling borningssl on Android O
*/
#include <log.h>
#pragma once
long syscall(long __number, ...){
	log(L"INSTRUMENT:%a : %a", __FILE__, __func__);
	return 0;};
