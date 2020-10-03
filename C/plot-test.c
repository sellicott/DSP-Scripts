/* plot_test.c - Quick C program to test plotting with gnuplot
 *
 * author: Samuel Ellicott (sellicott@cedarville.edu) 
 * date created: 08-23-20
 * date modified: 08-23-20
 */

#include <stdio.h>
#include <math.h>

#include "gnuplotlib.h"

int main(void);

int main(void)
{
  gnuplot_handle_t* gnuplot = gnuplot_open();


  const size_t num_elem = 100;
  const float pi = 3.141592654;
  float x[100] = {0};
  float y1[100] = {0};
  float y2[100] = {0};

  for (int i = 0; i < num_elem; i++) {
    x[i] = 2.0f * pi * i / (float) num_elem;
    y1[i] = sinf(x[i]);
    y2[i] = cosf(x[i]);
  }

  gnuplot_figure_t* fig1 = gnuplot_newfigure(gnuplot);
  gnuplot_plot2d_line(gnuplot, fig1, x, num_elem, y1, num_elem);
  gnuplot_newfigure(gnuplot);
  gnuplot_plot2d_line(gnuplot, NULL, x, num_elem, y2, num_elem);
  gnuplot_hold_on(gnuplot, fig1);

  puts("Press enter to exit\n");
  getc(stdin);
  gnuplot_close(gnuplot);

  return 0;
}