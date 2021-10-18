// drag fft 1

fprintf(gp, "set terminal pngcairo enhanced font 'Times New Roman,15' \n");
fprintf(gp, "set output '%s'\n", graphname9);
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

fprintf(gp, "set xrange [0:0.5]\n");
fprintf(gp, "set xlabel 'frequency [Hz]'offset 0.0,0\n");
fprintf(gp, "set yrange [0:25]\n");
fprintf(gp, "set ylabel 'power spectral density'offset 1,0.0\n");
fprintf(gp, "set title '%s drag'\n", label);

// fprintf(gp, "set samples 10000\n");
fprintf(gp, "plot '%s' using 2:1 with lines lw 2 lc 'blue' notitle\n", filename9);

fflush(gp); //Clean up Data

// drag fft 2

fprintf(gp, "set terminal pngcairo enhanced font 'Times New Roman,15' \n");
fprintf(gp, "set output '%s'\n", graphname10);
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

fprintf(gp, "set xrange [0:0.5]\n");
fprintf(gp, "set xlabel 'frequency [Hz]'offset 0.0,0\n");
fprintf(gp, "set yrange [0:25]\n");
fprintf(gp, "set ylabel 'power spectral density'offset 1,0.0\n");
fprintf(gp, "set title '%s drag'\n", label);

// fprintf(gp, "set samples 10000\n");
fprintf(gp, "plot '%s' using 2:1 with lines lw 2 lc 'blue' notitle\n", filename10);

fflush(gp); //Clean up Data

// drag fft 1

fprintf(gp, "set terminal pngcairo enhanced font 'Times New Roman,15' \n");
fprintf(gp, "set output '%s'\n", graphname11);
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

fprintf(gp, "set xrange [0:0.5]\n");
fprintf(gp, "set xlabel 'frequency [Hz]'offset 0.0,0\n");
fprintf(gp, "set yrange [0:25]\n");
fprintf(gp, "set ylabel 'power spectral density'offset 1,0.0\n");
fprintf(gp, "set title '%s drag'\n", label);

// fprintf(gp, "set samples 10000\n");
fprintf(gp, "plot '%s' using 2:1 with lines lw 2 lc 'red' notitle\n", filename11);

fflush(gp); //Clean up Data

// lift fft 2

fprintf(gp, "set terminal pngcairo enhanced font 'Times New Roman,15' \n");
fprintf(gp, "set output '%s'\n", graphname12);
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

fprintf(gp, "set xrange [0:0.5]\n");
fprintf(gp, "set xlabel 'frequency [Hz]'offset 0.0,0\n");
fprintf(gp, "set yrange [0:25]\n");
fprintf(gp, "set ylabel 'power spectral density'offset 1,0.0\n");
fprintf(gp, "set title '%s drag'\n", label);

// fprintf(gp, "set samples 10000\n");
fprintf(gp, "plot '%s' using 2:1 with lines lw 2 lc 'red' notitle\n", filename12);

fflush(gp); //Clean up Data