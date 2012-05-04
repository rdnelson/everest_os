#include <string.h>

//TODO: memcpy: Optimize to use integer sizes
void* memcpy(void * dst, void* src, size_t num) {
	void* ori_dst = dst;
	for(;num!=0;num--)
		((char*)dst)[num-1] = ((char*)src)[num-1];
	return ori_dst;
}

//TODO: memset: Optimize to use integer sizes
void* memset(void* dst, int val, size_t num) {
	void* ori_dst = dst;
	for(;num!=0;num--)
		((char*)dst)[num-1] = (char)val;
	return ori_dst;
}

