// graph4 : strainsensor-loadcell_x-axis

fprintf(gp, "set terminal pngcairo enhanced font 'Times New Roman,15' \n");
fprintf(gp, "set output '%s'\n", graphname4);
// fprintf(gp, "unset key\n");
fprintf(gp, "set key left top\n");
fprintf(gp, "set term pngcairo size 1280, 960 font ',24'\n");

fprintf(gp, "set lmargin screen 0.10\n");
fprintf(gp, "set rmargin screen 0.90\n");
fprintf(gp, "set tmargin screen 0.90\n");
fprintf(gp, "set bmargin screen 0.15\n");

fprintf(gp, "set xrange [-8:0]\n");
fprintf(gp, "set xlabel 'Load-cell [V]'offset 0.0,0\n");
fprintf(gp, "set yrange [-2:6]\n");
fprintf(gp, "set ylabel 'Strain-sensor [V]'offset 0,0.0\n");
fprintf(gp, "set title 'x-axis (drag) direction'\n");

fprintf(gp, "plot '%s' using 2:3 with points ps 2 pt 5 lc 'royalblue' title 'drag', '%s' using 2:4 with points ps 2 pt 5 lc 'orange' title 'lift'\n", filename2, filename2);

fflush(gp); //Clean up Data

// graph5 : strainsensor-loadcell_y-axis

fprintf(gp, "set terminal pngcairo enhanced font 'Times New Roman,15' \n");
fprintf(gp, "set output '%s'\n", graphname5);
// fprintf(gp, "unset key\n");
fprintf(gp, "set key left bottom\n");
fprintf(gp, "set term pngcairo size 1280, 960 font ',24'\n");

fprintf(gp, "set lmargin screen 0.10\n");
fprintf(gp, "set rmargin screen 0.90\n");
fprintf(gp, "set tmargin screen 0.90\n");
fprintf(gp, "set bmargin screen 0.15\n");

fprintf(gp, "set xrange [-8:0]\n");
fprintf(gp, "set xlabel 'Load-cell [V]'offset 0.0,0\n");
fprintf(gp, "set yrange [-4:1]\n");
fprintf(gp, "set ylabel 'Strain-sensor [V]'offset 0,0.0\n");
fprintf(gp, "set title 'y-axis (lift) direction'\n");

// fprintf(gp, "plot '%s' using 1:2 with poinKts ps 2 pt 5 lc 'dark-grey' title 'load-cell', '%s' using 1:3 with points ps 2 pt 5 lc 'royalblue' title 'drag', '%s' using 1:4 with points ps 2 pt 5 lc 'orange' title 'lift'\n", filename3, filename3, filename3);
fprintf(gp, "plot '%s' using 2:3 with points ps 2 pt 5 lc 'royalblue' title 'drag', '%s' using 2:4 with points ps 2 pt 5 lc 'orange' title 'lift'\n", filename3, filename3);

fflush(gp); //Clean up Data