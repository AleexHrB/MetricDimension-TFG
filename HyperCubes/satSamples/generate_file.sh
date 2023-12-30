for i in {1..9}
do
    gcc -O2 -fopenmp -Dexp=$i hyper_SAT.c
    ./a.out > prueba$i.wcnf
done
