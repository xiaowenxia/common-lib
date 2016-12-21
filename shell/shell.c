#include "shell.h"

#define CMD_MAX_ARGS        16      /* max number of command args */
#define CMD_MAX_LEN         256

typedef struct shell_item
{
    const xx_shell_t *shell;
    struct shell_item *next;
}shell_list_t;

static void shell_help(uint32_t argc, int8_t **argv);
static void shell_version(uint32_t argc, int8_t **argv);

static xx_shell_t s_shell_table[] =
{
    { "help","      Display list of commands.", shell_help},
    { "h","         alias for help.", shell_help},
    { "?","         alias for help.", shell_help},
	{ "version","   show program version.", shell_version},
    { "v","         alias for version.", shell_version}
};

static shell_list_t shell_list = {&s_shell_table[0],NULL};
static shell_list_t *shell_list_tail = &shell_list;

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

    if(argc == 0)
    {
        xx_printf("commands parse error\r\n");
        return xx_false;
    }

    /* parse commands */
    shell_list_t *p_shell_list = xx_null;

    for(p_shell_list = &shell_list; p_shell_list != NULL; p_shell_list = p_shell_list->next)
    {
        if(!strcmp((char const *)argv[0], p_shell_list->shell->cmd))
        {
            /* run the callback function */
            p_shell_list->shell->func(argc, argv);
            break;
        }
    }

    /* command is unknown */
    if(p_shell_list == NULL)
    {
        xx_printf("command is unknown\r\n");
        return xx_false;
    }

    return xx_true;
}

uint8_t cmd_register(xx_shell_t *shell)
{
    shell_list_t *new_shell = NULL;
    shell_list_t *p_shell_list = &shell_list;
    
    if(shell == NULL)
    {
        xx_printf("cmd_register failed,shell can not be null\r\n");
        return xx_false;
    }
    
    /* cmd must not exist in list */
    for(p_shell_list = &shell_list; p_shell_list != NULL; p_shell_list = p_shell_list->next)
    {
        if(!strcmp(p_shell_list->shell->cmd, shell->cmd))
        {
            xx_printf("command:[%s] is already in the shell_list\r\n", shell->cmd);
            return xx_false;
        }
    }
    new_shell = (shell_list_t *)xx_malloc(sizeof(shell_list_t));
    
    if(new_shell == NULL)
    {
        xx_printf("malloc failed\r\n");
        return xx_false;
    }
    
    /* insert shell to shell_list */
    new_shell->shell = shell;
    new_shell->next = NULL;
    shell_list_tail->next = new_shell;
    shell_list_tail = new_shell;
    
    return xx_true;
}

uint8_t cmd_register_array(xx_shell_t *shell, uint32_t array_size)
{
    xx_shell_t *p_shell = shell;

    uint32_t i = 0;
    for(i = 0; i < array_size; i++,p_shell++)
    {
        if(!cmd_register(p_shell))
        {
            /* register failed */
            return xx_false;
        }
    }

    return xx_true;
}

uint8_t cmd_init(void)
{
    shell_list.shell = &s_shell_table[0];
    shell_list.next  = xx_null;
    shell_list_tail  = &shell_list;

    return cmd_register_array(&s_shell_table[1], ARRAY_SIZE(s_shell_table)-1);
}

static void shell_help(uint32_t argc, int8_t **argv)
{
    shell_list_t *p_shell_list = NULL;

    CHECK_ARGC(1);
    
    xx_printf("*****************************************************\r\n");
    for(p_shell_list = &shell_list; p_shell_list != NULL; p_shell_list = p_shell_list->next)
    {
        xx_printf("%s%s\r\n", p_shell_list->shell->cmd, p_shell_list->shell->help);
    }
    xx_printf("*****************************************************\r\n");
}

static void shell_version(uint32_t argc, int8_t **argv)
{
    CHECK_ARGC(1);
    xx_printf("***************write by xiaxiaowen******************\r\n");
    xx_printf("*******************version:0.01*********************\r\n");
}