// graph6 : Load-Loadcell least squares

fprintf(gp, "set terminal pngcairo enhanced font 'Times New Roman,15' \n");
fprintf(gp, "set output '%s'\n", graphname6);
// fprintf(gp, "unset key\n");
fprintf(gp, "set key left top\n");
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

fprintf(gp, "plot '%s' using 1:2 with lines lw 3 lc 'dark-grey' title 'y = 0.12 x - 0.004', '%s' using 2:1 with points ps 2 pt 5 lc 'dark-grey' notitle\n", filename6, filename1);

fflush(gp); //Clean up Data

// graph7 : strainsensor-force

fprintf(gp, "set terminal pngcairo enhanced font 'Times New Roman,15' \n");
fprintf(gp, "set output '%s'\n", graphname7);
// fprintf(gp, "unset key\n");
fprintf(gp, "set key left top\n");
fprintf(gp, "set term pngcairo size 1280, 960 font ',24'\n");

fprintf(gp, "set lmargin screen 0.10\n");
fprintf(gp, "set rmargin screen 0.90\n");
fprintf(gp, "set tmargin screen 0.90\n");
fprintf(gp, "set bmargin screen 0.15\n");

fprintf(gp, "set xrange [-6:6]\n");
fprintf(gp, "set xlabel 'Strain-sensor [V]'offset 0.0,0\n");
fprintf(gp, "set yrange [-1.5:0]\n");
fprintf(gp, "set ylabel 'Input force [N]'offset 1.0,0.0\n");
fprintf(gp, "set title 'Strain sensor - Input force'\n");

fprintf(gp, "plot '%s' using 1:2 with points ps 2 pt 5 lc 'royalblue' title 'drag', '%s' using 1:2 with points ps 2 pt 5 lc 'orange' title 'lift'\n", filename4, filename5);

fflush(gp); //Clean up Data

// graph8 : strainsensor-force & formula

fprintf(gp, "set terminal pngcairo enhanced font 'Times New Roman,15' \n");
fprintf(gp, "set output '%s'\n", graphname8);
// fprintf(gp, "unset key\n");
fprintf(gp, "set key left top\n");
fprintf(gp, "set term pngcairo size 1280, 960 font ',24'\n");

fprintf(gp, "set lmargin screen 0.10\n");
fprintf(gp, "set rmargin screen 0.90\n");
fprintf(gp, "set tmargin screen 0.90\n");
fprintf(gp, "set bmargin screen 0.15\n");

fprintf(gp, "set xrange [-6:6]\n");
fprintf(gp, "set xlabel 'Strain-sensor [V]'offset 0.0,0\n");
fprintf(gp, "set yrange [-1.5:0]\n");
fprintf(gp, "set ylabel 'Input force [N]'offset 1.0,0.0\n");
fprintf(gp, "set title 'Strain sensor - Input force'\n");

fprintf(gp, "plot '%s' using 1:2 with points ps 2 pt 5 lc 'royalblue' title 'drag', '%s' using 1:2 with points ps 2 pt 5 lc 'orange' title 'lift', '%s' using 1:2 with lines lw 3 lc 'royalblue' title 'line 1', '%s' using 1:3 with lines lw 3 lc 'orange' title 'line 2'\n", filename4, filename5, filename7, filename7);

fflush(gp); //Clean up Data