#ifndef __CS_SHELL_H__
#define __CS_SHELL_H__

#include <stdint.h>

typedef struct cs_shell{
    /* command */
    const char *cmd;
    
    /* brief help text of this command */
    const char *help;
    
    /* point to the implementation of this command */
    void (* func)(uint32_t, int8_t **);
}cs_shell_t;

extern void cmd_parse(uint8_t *data);
#endif