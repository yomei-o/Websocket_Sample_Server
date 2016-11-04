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


#ifndef df_CFWDIPC_H_
#define df_CFWDIPC_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define CFWDIPC_SERVICE_MAIN "main_service"
#define CFWDIPC_SERVICE_ID_MAIN 1

#define CFWDIPC_MESSAGE_TYPE_START 1
#define CFWDIPC_MESSAGE_TYPE_STOP 2


typedef struct cfwdipc_message {
	int type;
	int sub_type;
	int sender_id;
	int param1;
	int param2;
	char data[2048];
}CFWDIPC_MESSAGE;

void* cfwdipc_start_service(char* name);
void cfwdipc_stop_service(void* h);
int cfwdipc_get_message(void* h,CFWDIPC_MESSAGE* m);
int cfwdipc_is_message(void* h);


void* cfwdipc_find_service(char* name);
void cfwdipc_free_service(void*);
int cfwdipc_send_message(void* h,CFWDIPC_MESSAGE* m);

#ifdef __cplusplus
}
#endif


#endif /* CFWDIPC */
	




