#ifndef __CS_SHELL_H__
#define __CS_SHELL_H__

#include <stdint.h>

typedef struct xx_shell{
    /* command */
    const char *cmd;
    
    /* brief help text of this command */
    const char *help;
    
    /* point to the implementation of this command */
    void (* func)(uint32_t, int8_t **);
}xx_shell_t;

extern uint8_t cmd_parse(uint8_t *data);
#endif