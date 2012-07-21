/*
    OSX files watcher with kqueue
    
    Watch file-paths given as arguments. Exits when one of them changed.
    It uses kqueue to register for change events. Based on Apple's example.

    Copyright (c), 2012 Thierry Passeron

    The MIT License

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to
    deal in the Software without restriction, including without limitation the
    rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
    sell copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include <errno.h>
#include <string.h>
#include <inttypes.h>
  
int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: watchfiles <file-path> [<file-path> [...]]\n");
        exit(-1);
    }
 
    int kq;

    /* Open a kernel queue. */
    if ((kq = kqueue()) < 0) {
        fprintf(stderr, "Could not open kernel queue.  Error was %s.\n", strerror(errno));
    }


    /* Set up a list of events to monitor. */
    int vnode_events = NOTE_DELETE |  NOTE_WRITE | NOTE_EXTEND | NOTE_ATTRIB | NOTE_LINK | NOTE_RENAME | NOTE_REVOKE;

    int num_files = argc - 1;

    /* Set up the events_to_monitor and event_data arrays */
    struct kevent *events_to_monitor = malloc(sizeof(struct kevent) * num_files);
    struct kevent *events_data = malloc(sizeof(struct kevent) * num_files);
    int *event_fds = malloc(sizeof(int) + num_files);
 
    int argn = 1;
    
    while (argn < argc) {
        int index = argn - 1;

        /* Get fd */
        char *path = argv[argn];
        event_fds[index] = open(path, O_EVTONLY);
        if (event_fds[index] <= 0) {
            fprintf(stderr, "The file %s could not be opened for monitoring.  Error was %s.\n", path, strerror(errno));
            exit(-1);
        }

        EV_SET(&events_to_monitor[index], event_fds[index], EVFILT_VNODE, EV_ADD | EV_CLEAR, vnode_events, 0, (void*)path /* the user_data */);

        argn++;
    }
 
    
    int ret = 0;
    int i;

    /* Let's wait here */
    int event_count = kevent(kq, events_to_monitor, num_files, events_data, num_files, NULL);

    /* finished waiting */
    if (event_count < 0) {
        for (i = 0; i < num_files; i++) {
            if (events_data[i].flags == EV_ERROR) {
                fprintf(stderr, "An error occurred (event count %d).  The error was %s.\n", event_count, strerror(errno));
                ret = -1;
            }
        }  
    } 
        
    /* close fds */
    for (i = 0; i < num_files; i++) close(event_fds[i]);

    /* frees */
    free(event_fds);
    free(events_data);
    free(events_to_monitor);

    return ret;
}
 
