
/* gnuplotlib.h 
 * Wrapper functions around gnuplot to give it a Matlab like interface.
 *
 * author: Samuel Ellicott (sellicott@cedarville.edu) 
 * date created: 08-23-20
 * date modified: 08-23-20
 */

// define some opaque structures for dealing with figure objects
struct gnuplot_handle;
typedef struct gnuplot_handle gnuplot_handle_t;

struct gnuplot_figure;
typedef struct gnuplot_figure gnuplot_figure_t;

gnuplot_handle_t* gnuplot_open();
void gnuplot_close(gnuplot_handle_t* handle);

gnuplot_figure_t* gnuplot_newfigure();

