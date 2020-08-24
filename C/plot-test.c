/* plot_test.c - Quick C program to test plotting with gnuplot
 *
 * author: Samuel Ellicott (sellicott@cedarville.edu) 
 * date created: 08-23-20
 * date modified: 08-23-20
 */

// so the compiler doesn't complain at us
#define _POSIX_C_SOURCE 2

#include <stdio.h>

#include "gnuplotlib.h"

int main(void);

int main(void)
{
  gnuplot_handle_t* gnuplot = gnuplot_open();

  puts("Press enter to exit\n");
  getc(stdin);

  //fputs("EOF\n", gnuplot);
  pclose(gnuplot);
  return 0;
}