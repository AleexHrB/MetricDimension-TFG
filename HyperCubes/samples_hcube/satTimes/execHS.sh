for j in {1..3}
do
    {
        for i in {1..9}
        do
            printf "Time for $i \n"
            { time ./maxhs -cpu-lim=300 ../../satSamples/samples/prueba$i.wcnf 1>/dev/null; } 2>&1
                printf "\n"
            done
        } > resultHS$j.txt
    done
