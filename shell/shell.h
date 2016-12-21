#ifndef __CS_SHELL_H__
#define __CS_SHELL_H__

#include <stdint.h>
#include "../common/define.h"

#define CHECK_ARGC(x)       if(argc != (x)){                    \
                                xx_printf("argc must be %d\r\n",x); \
                                return ;                        \
                            }

typedef struct xx_shell{
    /* command */
    const char *cmd;
    
    /* brief help text of this command */
    const char *help;
    
    /* point to the implementation of this command */
    void (* func)(uint32_t, int8_t **);
}xx_shell_t;

extern uint8_t cmd_init(void);
extern uint8_t cmd_parse(uint8_t *data);
extern uint8_t cmd_register(xx_shell_t *shell);
extern uint8_t cmd_register_array(xx_shell_t *shell, uint32_t array_size);

#endif