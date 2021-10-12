// graph1 : nut-loadcell

fprintf(gp, "set terminal pngcairo enhanced font 'Times New Roman,15' \n");
fprintf(gp, "set output '%s'\n", graphname1);
fprintf(gp, "unset key\n");
// fprintf(gp, "set key left bottom\n");
fprintf(gp, "set term pngcairo size 1280, 960 font ',24'\n");

fprintf(gp, "set lmargin screen 0.10\n");
fprintf(gp, "set rmargin screen 0.90\n");
fprintf(gp, "set tmargin screen 0.90\n");
fprintf(gp, "set bmargin screen 0.15\n");

fprintf(gp, "set xrange [-1:4]\n");
fprintf(gp, "set xlabel 'Load cell [V]'offset 0,0.0\n");
fprintf(gp, "set yrange [-0.05:0.4]\n");
fprintf(gp, "set ylabel 'Load [N]'offset 2.0,0\n");
fprintf(gp, "set title 'Load - Loadcell'\n");

fprintf(gp, "plot '%s' using 2:1 with points ps 2 pt 5 lc 'dark-grey'\n", filename1);

fflush(gp); //Clean up Data

// graph2 : length-sensors_x-axis

fprintf(gp, "set terminal pngcairo enhanced font 'Times New Roman,15' \n");
fprintf(gp, "set output '%s'\n", graphname2);
// fprintf(gp, "unset key\n");
fprintf(gp, "set key left top\n");
fprintf(gp, "set term pngcairo size 1280, 960 font ',24'\n");

fprintf(gp, "set lmargin screen 0.10\n");
fprintf(gp, "set rmargin screen 0.90\n");
fprintf(gp, "set tmargin screen 0.90\n");
fprintf(gp, "set bmargin screen 0.15\n");

fprintf(gp, "set xrange [-0.025:0.425]\n");
fprintf(gp, "set xlabel 'Load-cell [mm]'offset 0.0,0\n");
fprintf(gp, "set yrange [-6:6]\n");
fprintf(gp, "set ylabel 'Output of Sensors [V]'offset 0,0.0\n");
fprintf(gp, "set title 'x-axis (drag) direction'\n");

fprintf(gp, "plot '%s' using 1:2 with points ps 2 pt 5 lc 'dark-grey' title 'load-cell', '%s' using 1:3 with points ps 2 pt 5 lc 'royalblue' title 'drag', '%s' using 1:4 with points ps 2 pt 5 lc 'orange' title 'lift'\n", filename2, filename2, filename2);

fflush(gp); //Clean up Data

// graph3 : length-sensors_y-axis

fprintf(gp, "set terminal pngcairo enhanced font 'Times New Roman,15' \n");
fprintf(gp, "set output '%s'\n", graphname3);
// fprintf(gp, "unset key\n");
fprintf(gp, "set key left bottom\n");
fprintf(gp, "set term pngcairo size 1280, 960 font ',24'\n");

fprintf(gp, "set lmargin screen 0.10\n");
fprintf(gp, "set rmargin screen 0.90\n");
fprintf(gp, "set tmargin screen 0.90\n");
fprintf(gp, "set bmargin screen 0.15\n");

fprintf(gp, "set xrange [-0.025:0.425]\n");
fprintf(gp, "set xlabel 'Load-cell [mm]'offset 0.0,0\n");
fprintf(gp, "set yrange [-6:1]\n");
fprintf(gp, "set ylabel 'Output of Sensors [V]'offset 0,0.0\n");
fprintf(gp, "set title 'y-axis (lift) direction'\n");

fprintf(gp, "plot '%s' using 1:2 with points ps 2 pt 5 lc 'dark-grey' title 'load-cell', '%s' using 1:3 with points ps 2 pt 5 lc 'royalblue' title 'drag', '%s' using 1:4 with points ps 2 pt 5 lc 'orange' title 'lift'\n", filename3, filename3, filename3);

fflush(gp); //Clean up Data