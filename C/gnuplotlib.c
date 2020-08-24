
/* gnuplotlib.c 
 * Wrapper functions around gnuplot to give it a Matlab like interface.
 *
 * author: Samuel Ellicott (sellicott@cedarville.edu) 
 * date created: 08-23-20
 * date modified: 08-23-20
 */

#define _POSIX_C_SOURCE 2
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>


#include "gnuplotlib.h"

struct gnuplot_handle {
  FILE* pipe;

}; 

gnuplot_handle_t* gnuplot_open()
{
  // allocate memory for the handle
  struct gnuplot_handle* handle = calloc(1, sizeof(struct gnuplot_handle));

  // open a pipe for writing to gnuplot
  handle->pipe = popen("gnuplot", "w");
  if (!handle->pipe) {
    perror("Unable to open gnuplot");
    free(handle);
    handle = NULL;
  }

  return handle;
}

void gnuplot_close(gnuplot_handle_t* handle)
{
  if (!handle) return;
  fflush(handle->pipe);
  pclose(handle->pipe);

  // Do more cleanup here if necessary

  free(handle);
  handle = NULL;
}