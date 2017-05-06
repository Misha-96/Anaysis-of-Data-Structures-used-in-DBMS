set autoscale
set title "Plotting Execution Times of various trees"
set xlabel "Number of elements in Tree"
set ylabel "Execution Time(in Milliseconds)"
set style line 2  lc rgb '#FF0000' lt 1 lw 1.5
set style line 3  lc rgb '#006400' lt 1 lw 1.5
set style line 4  lc rgb '#0000FF' lt 1 lw 1.5
plot "plotter.dat" using 1:2 ls 2 title "Binary Search Tree" with linespoints, \
"plotter.dat" using 1:3 ls 3 title "AVL Tree" with linespoints, \
"plotter.dat" using 1:4 ls 4 title "B-Tree" with linespoints
