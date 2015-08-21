# the compiler: gcc for C program, define as g++ for C++
CC = clang
# set as gcc if you don't have clang

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall -std=gnu11

# define any directories containing header files other than /usr/include
# -I/home/newhall/include  -I../include
INCLUDES = 

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
LFLAGS =

# define any libraries to link into executable:
#   if I want to link in libraries (libx.so or libx.a) I use the -llibname 
#   option, something like (this will link in libmylib.so and libm.so:
LIBS = -lpthread

LIST = basic_locking basic_thread locking fork_example semaphore notify n_notify bounded_notify semaphore_buffer

all: $(LIST)

basic_locking: basic_locking.c
	$(CC) $(CFLAGS) basic_locking.c -o basic_locking $(LIBS)

basic_thread: basic_thread.c
	$(CC) $(CFLAGS) basic_thread.c -o basic_thread $(LIBS)

locking: locking.c
	$(CC) $(CFLAGS) locking.c -o locking $(LIBS)

fork_example: fork_example.c
	$(CC) $(CFLAGS) fork_example.c -o fork_example

semaphore: semaphore.c
	$(CC) $(CFLAGS) semaphore.c -o semaphore $(LIBS)

notify: notify.c
	$(CC) $(CFLAGS) notify.c -o notify $(LIBS)

n_notify: n_notify.c
	$(CC) $(CFLAGS) n_notify.c -o n_notify $(LIBS)

bounded_notify: bounded_notify.c
	$(CC) $(CFLAGS) bounded_notify.c -o bounded_notify $(LIBS)

semaphore_buffer: semaphore_buffer.c
	$(CC) $(CFLAGS) semaphore_buffer.c -o semaphore_buffer $(LIBS)

clean:
	$(RM) $(LIST)