# include "types.h"
# include "dongle.h"
# include "utils.h"
# include "init.h"

void    dongle_lock(t_coder *coder, t_dongle *dongle) {
    long wait_time;

    pthread_mutex_lock(&dongle->dongle_mutex);
    heap_push(&dongle->heap, coder);

    while (dongle->in_use || heap_peek(&dongle->heap) != coder)
        pthread_cond_wait(&dongle->heap_cond, &dongle->dongle_mutex);
    ft_printer(coder->system, coder->coder_id, MSG_TAKE_DONGLE);
    dongle->in_use = true;
    heap_pop(&dongle->heap);
    pthread_mutex_unlock(&dongle->dongle_mutex);

    if (get_time_ms() < (long)dongle->available_time)
    {
        wait_time = dongle->available_time - get_time_ms();
        if (wait_time > 0)
            ft_usleep(wait_time, coder->system);
    }
}

void    dongle_unlock(t_dongle *dongle) {
    pthread_mutex_lock(&dongle->dongle_mutex);
    dongle->available_time = get_time_ms() + dongle->cooldown;
    dongle->in_use = false;
    pthread_cond_signal(&dongle->heap_cond);
    pthread_mutex_unlock(&dongle->dongle_mutex);
}