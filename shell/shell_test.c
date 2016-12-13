#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "shell.h"

#define MAX_CMD_LEN     128
#define CMD_PROMPT      "shell> "

char in_buf[MAX_CMD_LEN] = {0};
int buf_idx = 0;

char c = 0;
int main(void)
{
    while(1)
    {
        memset(in_buf, 0, MAX_CMD_LEN);
        buf_idx = 0;
        printf("%s", CMD_PROMPT);

        while ((in_buf[buf_idx++] = getchar()) != '\n');
        //printf("%s", in_buf);

        buf_idx --;
        in_buf[buf_idx++] = '\r';
        in_buf[buf_idx++] = '\n';

        cmd_parse((uint8_t *)in_buf);
    }

    return 0;
}