
/* gnuplotlib.c 
 * Wrapper functions around gnuplot to give it a Matlab like interface.
 *
 * author: Samuel Ellicott (sellicott@cedarville.edu) 
 * date created: 08-23-20
 * date modified: 10-02-20
 */

#define _POSIX_C_SOURCE 2
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <math.h>

#include "gnuplotlib.h"

struct gnuplot_figure {
  size_t id;
};

struct gnuplot_handle {
  FILE* pipe;
  struct gnuplot_figure* figs;
  size_t size_figs; // allocated size of figs
  size_t num_figs;  // number of open figures

  gnuplot_figure_t* active_figure;
}; 


// private function definitions
static void allocate_figs(gnuplot_handle_t* h, size_t nfigs);
static void set_active_fig(gnuplot_handle_t* h, gnuplot_figure_t* fig);

gnuplot_handle_t* gnuplot_open(void)
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
  free(handle->figs);

  free(handle);
  handle = NULL;
}


gnuplot_figure_t* gnuplot_newfigure(gnuplot_handle_t* h)
{
  if (!h) return NULL;
  allocate_figs(h, 1);
  gnuplot_figure_t* fig = &h->figs[h->num_figs];
  fig->id = h->num_figs++;

  set_active_fig(h, fig);
  fflush(h->pipe);

  return fig;
}

void gnuplot_plot2d_scatter(gnuplot_handle_t* h, gnuplot_figure_t* fig,
                            const float* xvals, size_t xsize,
                            const float* yvals, size_t ysize)
{
  if (!h) return;
  set_active_fig(h, fig);
  fflush(h->pipe);
}


void gnuplot_plot2d_line(gnuplot_handle_t* h, gnuplot_figure_t* fig,
                         const float* xvals, size_t xsize,
                         const float* yvals, size_t ysize)
{
  if (!h) return;
  set_active_fig(h, fig);

  if (!xvals || !yvals) return;

  fprintf(h->pipe, "plot '-' with lines\n");

  // get the minimum of the two lengths
  size_t min_len = xsize < ysize ? xsize : ysize;

  for (int i = 0; i < min_len; ++i) {
    fprintf(h->pipe, "%f, %f\n", xvals[i], yvals[i]);
  }

  fputs("e volatile\n", h->pipe);
  fflush(h->pipe);
}

void gnuplot_hold_off(gnuplot_handle_t* h, gnuplot_figure_t* fig)
{
  if (!h) return;
  set_active_fig(h, fig);
  fflush(h->pipe);

}

void gnuplot_hold_on (gnuplot_handle_t* h, gnuplot_figure_t* fig)
{
  if (!h) return;
  set_active_fig(h, fig);
  fflush(h->pipe);

}

static void set_active_fig(gnuplot_handle_t* h, gnuplot_figure_t* fig)
{
  if (fig){
    h->active_figure = fig;
  }
  fprintf(h->pipe, "set term %s %ld \n", GNUPLOT_OUTPUT_TYPE, h->active_figure->id);
}

// private function implementations
static void allocate_figs(gnuplot_handle_t* h, size_t nfigs)
{
  // if we cannot fit into the avalible space resize
  size_t new_size = nfigs + h->num_figs;
  if(new_size >= h->size_figs) {
    if (h->size_figs == 0) {
      // do the first allocation
      h->figs = calloc(2, sizeof(struct gnuplot_figure));
      h->size_figs = 2;
    } else {
      // double the size of the figure buffer
      new_size = h->size_figs * 2;
      h->figs = realloc(h->figs, new_size * sizeof(struct gnuplot_figure));

      // clear the empty memory
      size_t fresh_mem = (new_size - h->num_figs) * sizeof(struct gnuplot_figure);
      memset(&h->figs[h->num_figs], 0, fresh_mem);
    }
  }

}