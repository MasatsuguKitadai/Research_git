// drag

fprintf(gp, "set terminal pngcairo enhanced font 'Times New Roman,15' \n");
fprintf(gp, "set output '%s'\n", graphname7);
// fprintf(gp, "set multiplot\n");
// fprintf(gp, "unset key\n");
fprintf(gp, "set key left top\n");
fprintf(gp, "set term pngcairo size 1280, 960 font ',24'\n");
fprintf(gp, "set key font ',20'\n");
// fprintf(gp, "set size ratio %lf\n", size);

fprintf(gp, "set lmargin screen 0.10\n");
fprintf(gp, "set rmargin screen 0.90\n");
fprintf(gp, "set tmargin screen 0.90\n");
fprintf(gp, "set bmargin screen 0.15\n");

fprintf(gp, "set xrange [%d:%d]\n", x_min, x_max);
fprintf(gp, "set xlabel '%s'offset 0.0,0\n", xxlabel);
fprintf(gp, "set yrange [%d:%d]\n", y_min1, y_max1);
fprintf(gp, "set ylabel '%s'offset 2,0.0\n", yylabel);
fprintf(gp, "set title '%s drag'\n", label);

// fprintf(gp, "set samples 10000\n");
fprintf(gp, "plot 0 lw 2 lc 'dark-grey' notitle, '%s' using 1:3 with lines lw 2 lc 'orange' title 'correction', '%s' using 1:3 with lines dt (10,5) lw 3 lc 'green' title 'average (1)', '%s' using 1:2 with lines dt (10,5) lw 3 lc 'magenta' title 'average (2)'\n", filename7, filename8, filename8);

fflush(gp); //Clean up Data

// lift

fprintf(gp, "set terminal pngcairo enhanced font 'Times New Roman,15' \n");
fprintf(gp, "set output '%s'\n", graphname8);
// fprintf(gp, "unset key\n");
fprintf(gp, "set key left top\n");
fprintf(gp, "set term pngcairo size 1280, 960 font ',24'\n");
fprintf(gp, "set key font ',20'\n");
// fprintf(gp, "set size ratio %lf\n", size);

fprintf(gp, "set lmargin screen 0.10\n");
fprintf(gp, "set rmargin screen 0.90\n");
fprintf(gp, "set tmargin screen 0.90\n");
fprintf(gp, "set bmargin screen 0.15\n");

fprintf(gp, "set xrange [%d:%d]\n", x_min, x_max);
fprintf(gp, "set xlabel '%s'offset 0.0,0\n", xxlabel);
fprintf(gp, "set yrange [%d:%d]\n", y_min2, y_max2);
fprintf(gp, "set ylabel '%s'offset 2,0.0\n", yylabel);
fprintf(gp, "set title '%s lift'\n", label);

// fprintf(gp, "set samples 10000\n");
fprintf(gp, "plot 0 lw 2 lc 'dark-grey' notitle, '%s' using 1:5 with lines lw 2 lc 'orange' title 'correction', '%s' using 1:5 with lines dt (10,5) lw 3 lc 'green' title 'average (1)', '%s' using 1:4 with lines dt (10,5) lw 3 lc 'magenta' title 'average (2)'\n", filename7, filename8, filename8);

fflush(gp); //Clean up Data