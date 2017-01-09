#include "at_mutex.h"
#include "string.h"

uint8_t mutex_take(struct cs_mutex * p_mutex);
uint8_t mutex_give(struct cs_mutex * p_mutex);
uint8_t queue_snd(struct cs_queue * p_queue, void *p_data);
uint8_t queue_snd_isr(struct cs_queue * p_queue, void *p_data);
uint8_t queue_rcv(struct cs_queue * p_queue, void *p_data);

void mutex_init(cs_mutex_t *p_mutex)
{
    AT_ASSERT(p_mutex);
    memset(p_mutex,0,sizeof(cs_mutex_t));
    
    p_mutex->mutex      = xSemaphoreCreateMutex();
    AT_ASSERT(p_mutex->mutex);
    
    p_mutex->block_time = AT_MUTEX_DEFAULT_BLOCK_TIME;
    p_mutex->take       = mutex_take;
    p_mutex->give       = mutex_give;
}

uint8_t mutex_take(struct cs_mutex * p_mutex)
{
    AT_ASSERT(p_mutex);
    if(xSemaphoreTake(p_mutex->mutex, p_mutex->block_time) != pdPASS)
        return AT_FALSE;
    return AT_TRUE;
}

uint8_t mutex_give(struct cs_mutex * p_mutex)
{
    AT_ASSERT(p_mutex);
    if(xSemaphoreGive(p_mutex->mutex) != pdPASS)
        return AT_FALSE;
    return AT_TRUE;
}

void queue_init(cs_queue_t *p_queue, uint16_t length, uint16_t size)
{
    AT_ASSERT(p_queue);
    
    memset(p_queue,0,sizeof(cs_queue_t));
    
    p_queue->length = length;
    p_queue->size = size;
    
    p_queue->queue      = xQueueCreate(p_queue->length, p_queue->size);
    AT_ASSERT(p_queue->queue);
    
    p_queue->snd_block_time  = AT_MUTEX_DEFAULT_BLOCK_TIME;
    p_queue->recv_block_time = AT_MUTEX_DEFAULT_BLOCK_TIME;
    p_queue->snd       = queue_snd;
    p_queue->snd_isr   = queue_snd_isr;
    p_queue->rcv       = queue_rcv;
}

uint8_t queue_snd(struct cs_queue * p_queue, void *p_data)
{
    AT_ASSERT(p_queue);
    if(xQueueSend(p_queue->queue, p_data, p_queue->snd_block_time) != pdPASS)
        return AT_FALSE;
    return AT_TRUE;
}

/* this function must call by irq */
uint8_t queue_snd_isr(struct cs_queue * p_queue, void *p_data)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    
    if( errQUEUE_FULL == xQueueSendFromISR( p_queue->queue, p_data, &xHigherPriorityTaskWoken ) )
	{
		/* did not send to the queue */
		return AT_FALSE;
	}
	
	/* check the priority task woken flag */
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    return AT_TRUE;
}

uint8_t queue_rcv(struct cs_queue * p_queue, void *p_data)
{
    AT_ASSERT(p_queue);
    if(xQueueReceive(p_queue->queue, p_data, p_queue->recv_block_time) != pdPASS)
        return AT_FALSE;
    return AT_TRUE;
}