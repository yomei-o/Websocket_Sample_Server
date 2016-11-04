/*
Copyright (c) 2016, Yomei Otani <yomei.otani@gmai.com>
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies,
either expressed or implied, of the FreeBSD Project.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cfwdipc.h"
#include "myfifo.h"

#if defined(_WIN32) && !defined(__GNUC__)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif


void* cfwdipc_start_service(char* name)
{
	return myfifo_open_read(name);
}
void cfwdipc_stop_service(void* h)
{
	myfifo_close(h);
}
int cfwdipc_get_message(void* h,CFWDIPC_MESSAGE* m)
{
	return myfifo_read(h,m,sizeof(CFWDIPC_MESSAGE));
}

int cfwdipc_is_message(void* h)
{
	return myfifo_ismessage(h);
}


void* cfwdipc_find_service(char* name)
{
	return myfifo_open_write(name);
}
void cfwdipc_free_service(void* h)
{
	myfifo_close(h);
}
int cfwdipc_send_message(void* h,CFWDIPC_MESSAGE* m)
{
	return myfifo_write(h,m,sizeof(CFWDIPC_MESSAGE));
}




//
//
// test code
//
//

#if 0

void do_service(void)
{
	void* h;

	printf("starting service mode\n");

	h=cfwdipc_start_service(CFWDIPC_SERVICE_MAIN);
	if(h==NULL){
		printf("stat service error\n");
		return;
	}
	while(1){
		CFWDIPC_MESSAGE m;
		int r;
		r=cfwdipc_get_message(h,&m);
		printf(".");
		fflush(stdout);
		if(r>0){
			if(m.type==CFWDIPC_MESSAGE_TYPE_STOP){
				printf("\n");
				printf("STOP request was received\n");
				break;
			}
		}
	}
	if(h)cfwdipc_stop_service(h);
	printf("stopped service \n");
}

void do_client(void)
{
	void* h;
	CFWDIPC_MESSAGE m;

	printf("starting client mode\n");

	h=cfwdipc_find_service(CFWDIPC_SERVICE_MAIN);
	if(h==NULL){
		printf("find service error\n");
		return;
	}
	memset(&m,0,sizeof(m));
	m.type=CFWDIPC_MESSAGE_TYPE_STOP;
	cfwdipc_send_message(h,&m);

	cfwdipc_free_service(h);
}


int main(int argc,char* argv[])
{
	int i;
	int service=0;

#if defined(_WIN32) && !defined(__GNUC__)
//	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_WNDW);
//	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_WNDW);
//	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_WNDW);
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);
#endif

	for(i=1;i<argc;i++)if(strstr(argv[i],"-s"))service=1;
	for(i=1;i<argc;i++)if(strstr(argv[i],"-d"))service=1;

	if(service){
		do_service();
	}else{
		do_client();
	}

	return 0;
}


#endif
