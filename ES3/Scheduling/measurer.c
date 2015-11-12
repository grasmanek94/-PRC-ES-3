#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

static unsigned long long
convert_time (struct timespec * ts)
{
    // convert 'ts' to microseconds
    long long   nsec;
    long long   sec;

    // ensure that all items in the expression are 'long long'
    nsec = ts->tv_nsec;
    sec  = ts->tv_sec;
    return (nsec + sec * 1000000000LL);
}

static unsigned long long
get_time (void)
{
    // get the elapsed time (in microseconds)
    struct timespec ts;
    
    clock_gettime (CLOCK_REALTIME, &ts);
    return (convert_time (&ts));
}

extern int
main ()
{
	unsigned long long time_last = get_time();
	unsigned long long difference = 0;

    while (1)
    {
		long long t_now = get_time();
		difference = get_time() - t_now;
		if (difference > 100000)
		{
			struct timespec     ts;
			sched_rr_get_interval(getpid(), &ts);
			printf("Last diff time / shed_rr_g_i: %llu ms / %llu ms\n", (t_now - time_last) / 1000000, convert_time(&ts) / 1000000);
			time_last = t_now;
		}
    }

	return (0);
}

