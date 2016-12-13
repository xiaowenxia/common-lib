#include "../common/define.h"
#include "shell.h"

#define CMD_MAX_ARGS        16      /* max number of command args */
#define CMD_MAX_LEN         256
#define CHECK_ARGC(x)       if(argc != (x)){                    \
                                xx_printf("argc must be %d",x); \
                                return ;                        \
                            }

static void cmd_help(uint32_t argc, int8_t **argv);
static void cmd_version(uint32_t argc, int8_t **argv);

static xx_shell_t s_cmd_table[] =
{
    { "help","      Display list of commands.", cmd_help},
    { "h","         alias for help.", cmd_help},
    { "?","         alias for help.", cmd_help},
	{ "version","   show program version.", cmd_version},
    { "v","         alias for version.", cmd_version}
};

static int cmd_parse_argv(const int8_t *cmd, int8_t *argv[])
{
    uint32_t nargs = 0;
    int8_t last = 0;
    int8_t *line = (int8_t *)cmd;

    while (nargs < CMD_MAX_ARGS)
    {
        /* skip any white space */
        while ((*line == ' ') || (*line == '\t') || (*line == '-'))
        {
            last = *line;
            line++;
        }
        
        /* end of line, no more args */
        if (*line == '\0') {
            argv[nargs] = NULL;
            return (nargs);
        }
        
        /* begin of argument string */
        argv[nargs++] = line;
        
        /* find end of string */
        while (*line && (*line != ' ') && (*line != '\t'))
        {
            if (*line == '-')
            {
                if (last != ' ')
                {
                    last = *line;
                    line++;
                }
                else
                {
                    break;
                }
            }
            else
            {
                last = *line;
                line++;
            }
        }
        
        /* end of line, no more args */
        if (*line == '\0')
        {
            argv[nargs] = NULL;
            return (nargs);
        }
        
        /* terminate current arg */
        *line++ = '\0';
    }
    xx_printf("** Too many args (max. %d) **\n", CMD_MAX_ARGS);
    return (nargs);
}
uint8_t cmd_parse(uint8_t *data)
{
    int8_t *argv[CMD_MAX_ARGS + 1] = {NULL};
    int8_t cmd_data[CMD_MAX_LEN] = {0};
    uint32_t argc;
    uint8_t l_cmd_len = strlen((char const *)data);
    
    //DUMP_BUFFER(data, l_cmd_len);

    /* commands must end of \r\n */
    if(data[l_cmd_len - 1] != '\n' || data[l_cmd_len - 2] != '\r')
    {
        xx_printf("commands must end of CR&LF\r\n");
        return xx_false;
    }
        
    
    /* get the command parameter */
    memcpy(cmd_data, data, l_cmd_len - 2);
    argc = cmd_parse_argv(cmd_data, argv);
    /* parse commands */
    uint32_t i = 0;
    for(i = 0; i < ARRAY_SIZE(s_cmd_table); i++)
    {
        if(!strcmp((char const *)argv[0], (char const *)s_cmd_table[i].cmd))
        {
            /* run the callback function */
            s_cmd_table[i].func(argc, argv);
            break;
        }
    }

    /* command is unknown */
    if(i == ARRAY_SIZE(s_cmd_table))
    {
        xx_printf("command is unknown\r\n");
        return xx_false;
    }

    return xx_true;
}

static void cmd_help(uint32_t argc, int8_t **argv)
{
    uint32_t i = 0;
    CHECK_ARGC(1);
    xx_printf("************************************************\r\n");
    for(i = 0; i < ARRAY_SIZE(s_cmd_table); i++)
    {
        xx_printf("%s%s\r\n", s_cmd_table[i].cmd, s_cmd_table[i].help);
    }
    xx_printf("************************************************\r\n");
}

extern void talkie_project_show(void);
extern uint8_t para_display(void);

static void cmd_version(uint32_t argc, int8_t **argv)
{
    CHECK_ARGC(1);
    xx_printf("***************write by xiaxiaowen******************\r\n");
    xx_printf("*******************version:0.01*********************\r\n");
}