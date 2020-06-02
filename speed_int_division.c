#include <stdint.h>
#include <stdio.h>
#include <time.h>

#define ffs32(x) ((__builtin_ffs(x)) - 1)

size_t PAGE_QUEUES[60] = {
    1,       2,       3,       4,       5 << 1,  5 << 2,  5 << 3,  5 << 4,
    5 << 5,  5 << 6,  5 << 7,  5 << 8,  5 << 9,  5 << 10, 5 << 11, 5 << 12,
    5 << 13, 5 << 14, 6 << 1,  6 << 2,  6 << 3,  6 << 4,  6 << 5,  6 << 6,
    6 << 7,  6 << 8,  6 << 9,  6 << 10, 6 << 11, 6 << 12, 6 << 13, 6 << 14,
    7 << 1,  7 << 2,  7 << 3,  7 << 4,  7 << 5,  7 << 6,  7 << 7,  7 << 8,
    7 << 9,  7 << 10, 7 << 11, 7 << 12, 7 << 13, 7 << 14, 8 << 1,  8 << 2,
    8 << 3,  8 << 4,  8 << 5,  8 << 6,  8 << 7,  8 << 8,  8 << 9,  8 << 10,
    8 << 11, 8 << 12, 8 << 13, 8 << 14,
};

static long timespec_diff(struct timespec *a, struct timespec *b) {
  return ((b->tv_sec - a->tv_sec) * 1000000000) + (b->tv_nsec - a->tv_nsec);
}

int main(int argc, char *argv[])
{
  size_t blockidx;
  size_t offset = 0xffffffff;
  size_t divident;
  struct timespec t1, t2;

  clock_gettime(CLOCK_REALTIME, &t1);
  for (int j = 0; j < 1000000; j++) {
    for (int i = 0; i < sizeof(PAGE_QUEUES) / sizeof(PAGE_QUEUES[0]); i++) {
      divident = PAGE_QUEUES[i];

#ifdef SPEED_UP_INT_DIVISION
    blockidx = offset >> ffs32(divident);
    divident >>= ffs32(divident);
    switch (divident) {
    case 3:
      blockidx /= 3;
      break;
    case 5:
      blockidx /= 5;
      break;
    case 7:
      blockidx /= 7;
      break;
    default:
      break;
    }
#else
    blockidx = offset / divident;
#endif
  }
  }
  clock_gettime(CLOCK_REALTIME, &t2);

#ifdef SPEED_UP_INT_DIVISION
  printf("Speed up, integer division. Time cost (us): %ld\n",
         timespec_diff(&t1, &t2));
#else
  printf("Integer division. Time cost (us): %ld\n", timespec_diff(&t1, &t2));
#endif

  return 0;
}
