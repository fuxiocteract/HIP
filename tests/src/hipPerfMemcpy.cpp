/*
Copyright (c) 2015-2016 Advanced Micro Devices, Inc. All rights reserved.
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include"test_common.h"
#include<iostream>
#include<time.h>

#define NUM_SIZE 8
#define NUM_ITER 12
static size_t size[NUM_SIZE];

void setup(){
	for(int i=0;i<NUM_SIZE;i++){
		size[i] = 1<<(i+6); // start at 8 bytes
	}
}

void valSet(int *A, int val, size_t size){
	size_t len = size/sizeof(int);
	for(int i=0;i<len;i++){
		A[i] = val;
	}
}

int main(){
	setup();
	int *A, *Ad;
	for(int i=0;i<NUM_SIZE;i++){
		std::cout<<size[i]<<std::endl;
		A = (int*)malloc(size[i]);
		valSet(A, 1, size[i]);
		hipMalloc(&Ad, size[i]);
		std::cout<<"Malloc success at size: "<<size[i]<<std::endl;
		clock_t start ,end;
		start = clock();
		for(int i=0;i<NUM_ITER;i++){
			hipMemcpy(Ad, A, size[i], hipMemcpyHostToDevice);
		}
		hipDeviceSynchronize();
		end = clock();
		double uS = (double)(end - start)*1000/(NUM_ITER*CLOCKS_PER_SEC);
		std::cout<<uS<<std::endl;
	}
}
