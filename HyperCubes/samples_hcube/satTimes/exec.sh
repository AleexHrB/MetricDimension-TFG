touch resultNB.txt
{
    for i in {1..9}
    do
        printf "Time for $i \n"
        { timeout 8m time ./cashwmaxsatcoreplus samples/prueba$i.wcnf; } 2>&1
        printf "\n"
    done
} > resultNB.txt

