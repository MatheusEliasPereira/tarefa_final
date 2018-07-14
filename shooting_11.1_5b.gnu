set xlabel font "Helvetica,12"
set ylabel font "Helvetica,12"
set tics font "Helvetica,12"
set title font "Helvetica,12"
set xlabel "x"
set ylabel "y(x)"
set title "Soluções da EDO com h = 0,05"
set key top left
plot "dados_11.1_5b.dat" u 2:3 w p pt 7 ps 2 t"Solução y_{1}(x)"
replot "dados_11.1_5b.dat" u 2:4 w p pt 7 ps 2 t"Solução y_{2}(x)"
replot "dados_11.1_5b.dat" u 2:5 w p pt 7 ps 2 t"Solução Geral y(x)"
f(x) = exp(-10*x)
replot f(x) w l lw 2 t"Solução Teórica"
set key default
