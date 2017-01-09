#ifndef __AT_MUTEX_H__
#define __AT_MUTEX_H__

#include "at_config.h"
#include "freertos\FreeRTOS.h"
#include "freertos\semphr.h"

#define AT_MUTEX_DEFAULT_BLOCK_TIME    portMAX_DELAY

typedef struct cs_mutex{
    /* this is freertos mutex lock handle */
    xSemaphoreHandle mutex;
    
    /* xSemaphoreTake block time */
    TickType_t  block_time;

    /* take this mutex */
    uint8_t (* take)(struct cs_mutex *);
    
    /* give this mutex */
    uint8_t (* give)(struct cs_mutex *);
}cs_mutex_t;

typedef struct cs_queue{
    /* this is freertos queue lock handle */
    QueueHandle_t queue;
    
    /* queue length */
    uint16_t length;
    
    /* item size */
    uint16_t size;
    
    /* send block time */
    TickType_t  snd_block_time;

    /* recv block time */
    TickType_t  recv_block_time;
    
    /* send queue */
    uint8_t (* snd)(struct cs_queue *, void *p_data);
    
    /* send queue from isr */
    uint8_t (* snd_isr)(struct cs_queue *, void *p_data);
    
    /* receive queue */
    uint8_t (* rcv)(struct cs_queue *, void *p_data);
}cs_queue_t;

void queue_init(cs_queue_t *queue, uint16_t length, uint16_t size);
void mutex_init(cs_mutex_t *mutex);

#endif