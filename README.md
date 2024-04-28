# Fdf

Fdf is a project that uses the 42 MiniLibX graphics library to render an isometric, wire-frame projection.

The programme takes as a single input a text file with the extension .fdf, formatted as rows of integers.  For example:

> 0 0 0 0\
0 1 1 0\
0 1 1 0\
0 0 0 0

Rows (or lines) represent the axis (horizontally) and ordinate (vertically).  The altitude is represented by the integer values.

This is translated into a grid of nodes and edges, where each node is a vector with an x, y and z coordinate.  

I have included some additional features, for moving the relative position of the grid on the x and y axes of the screen, for zooming, for toggling edges on and off, toggling an additional relative plane, and the ability to scale the z axis.

Toggling the edges gives some nice aesthetic options.  However, it was functionally implemented to speed up transforms, so that the whole grid is not being redrawn every time through the loop.  The whole projection is only redrawn when there are transforms, or when the layers are toggled.

The Makefile complies the sources and links both Libft and the MiniLibX library.  Both libraries must be compiled separately and placed in the lib folder.  Additionally some dependencies must also be included.  The Makefile will run the following commands (specific to Linux). 

> cc -Wall -Werror -Wextra fdf.c fdf_utils0.c ... fdf_utils3.c -L ./lib/ -lft -lmlx *-lXext -lX11 -lm*

