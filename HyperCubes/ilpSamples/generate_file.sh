for i in {1..11}
do
    gcc -O2 -fopenmp -Dexp=$i hyper.c
    ./a.out > prueba$i.lp
done
