
/* gnuplotlib.h 
 * Wrapper functions around gnuplot to give it a Matlab like interface.
 *
 * author: Samuel Ellicott (sellicott@cedarville.edu) 
 * date created: 08-23-20
 * date modified: 08-23-20
 */

#define GNUPLOT_OUTPUT_TYPE "qt"

// define some opaque structures for dealing with figure objects
struct gnuplot_handle;
typedef struct gnuplot_handle gnuplot_handle_t;

struct gnuplot_figure;
typedef struct gnuplot_figure gnuplot_figure_t;


gnuplot_handle_t* gnuplot_open(void);
void gnuplot_close(gnuplot_handle_t* handle);

gnuplot_figure_t* gnuplot_newfigure(gnuplot_handle_t* h);

void gnuplot_plot2d_scatter(gnuplot_handle_t* h, gnuplot_figure_t* fig,
                            const float* xvals, size_t xsize,
                            const float* yvals, size_t ysize);
void gnuplot_plot2d_line   (gnuplot_handle_t* h, gnuplot_figure_t* fig,
                            const float* xvals, size_t xsize,
                            const float* yvals, size_t ysize);

void gnuplot_plot2d_stem   (gnuplot_handle_t* h, gnuplot_figure_t* fig,
                            const float* xvals, size_t xsize,
                            const float* yvals, size_t ysize);

void gnuplot_hold_off(gnuplot_handle_t* h, gnuplot_figure_t* fig);
void gnuplot_hold_on (gnuplot_handle_t* h, gnuplot_figure_t* fig);

void gnuplot_xlabel(gnuplot_handle_t* h, gnuplot_figure_t* fig, const char* xlabel);
void gnuplot_ylabel(gnuplot_handle_t* h, gnuplot_figure_t* fig, const char* ylabel);
void gnuplot_title (gnuplot_handle_t* h, gnuplot_figure_t* fig, const char* title);
