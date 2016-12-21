#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "shell.h"

#define MAX_CMD_LEN     128
#define CMD_PROMPT      "shell> "

char in_buf[MAX_CMD_LEN] = {0};
int buf_idx = 0;

void shell_who_am_i(uint32_t argc, int8_t **argv);
void shell_say_hello(uint32_t argc, int8_t **argv);

static xx_shell_t custom_shell_table[] =
{
    { "who","       who am i", shell_who_am_i},
    { "hello","     say hello", shell_say_hello}
};

void shell_who_am_i(uint32_t argc, int8_t **argv)
{
    CHECK_ARGC(1);

    xx_printf("this is shell\r\n");
}

void shell_say_hello(uint32_t argc, int8_t **argv)
{
    CHECK_ARGC(2);

    xx_printf("hi, nice to see you,%s\r\n", argv[1]);
}

int main(void)
{
    cmd_init();

    cmd_register_array(custom_shell_table, ARRAY_SIZE(custom_shell_table));
    
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