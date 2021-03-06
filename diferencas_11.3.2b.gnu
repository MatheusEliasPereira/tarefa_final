set xlabel font "Helvetica,12"
set ylabel font "Helvetica,12"
set tics font "Helvetica,12"
set title font "Helvetica,12"
set xlabel "x"
set ylabel "y(x)"
set title "Soluções da EDO com h = {/Symbol p}/8"
plot "dados_11.3_2b.dat" u 1:2 w p pt 7 ps 2 t"Solução y(x)"
g(x) = (-1/10.0)*(sin(x) + 3*cos(x))
replot g(x) w l lw 2 t"Solução Teórica"
