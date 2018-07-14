set xlabel font "Helvetica,12"
set ylabel font "Helvetica,12"
set tics font "Helvetica,12"
set title font "Helvetica,12"
set xlabel "x"
set ylabel "y(x)"
set title "Soluções da EDO com h = 1/4"


plot "dados_11.1_1b.dat" u 2:3 w p pt 7 ps 2 t"Solução y_{1}(x)"
replot "dados_11.1_1b.dat" u 2:4 w p pt 7 ps 2 t"Solução y_{2}(x)"
replot "dados_11.1_1b.dat" u 2:5 w p pt 7 ps 2 t"Solução Geral y(x)"
f(x) = x + (exp(2.0*x+2.0)-exp(-2.0*x+2.0))/(exp(4.0)-1.0)
replot f(x) w l lw 2 t"Solução Teórica"
