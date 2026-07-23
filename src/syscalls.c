/**
 * file: syscalls.c
 * brief: All the system call support for newlib to work
 */

/*Includes*/
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#define UNUSED(x) UNUSED_##x __attribute__((__unused__))
#undef errno
extern int errno;
char *__env[1] = {0};
char **environ = __env;

void exit(int UNUSED(status)) {
  while (1)
    ;
}

int _close(int UNUSED(file)) { return -1; }

int _lseek(int UNUSED(file), int UNUSED(ptr), int UNUSED(dir)) { return 0; }

int _read(int UNUSED(file), char *UNUSED(ptr), int UNUSED(len)) { return 0; }

int _write(int UNUSED(file), char *UNUSED(ptr), int len) { return len; }

caddr_t _sbrk(int UNUSED(incr)) {
#if 0
  extern char _end;		/* Defined by the linkerk */
  static char *heap_end;
  char *prev_heap_end;

  if (heap_end == 0) {
    heap_end = &_end;
  }
  prev_heap_end = heap_end;
  if (heap_end + incr > stack_ptr) {
    write (1, "Heap and stack collision\n", 25);
    abort ();
  }

  heap_end += incr;
  return (caddr_t) prev_heap_end;
#endif
  return NULL;
}

// int execve(char *name, char **argv, char **env) {
//   errno = ENOMEM;
//   return -1;
// }

// int fork(void) {
//   errno = EAGAIN;
//   return -1;
// }

// int fstat(int file, struct stat *st) {
//   st->st_mode = S_IFCHR;
//   return 0;
// }
