for j in {1..3}
do
    {
        for i in {1..9}
        do
            printf "Time for $i \n"
            { time ./cplex -c "read ../../ilpSamples/samples/prueba$i.lp" "set timelimit 300" "optimize" "quit" 1>/dev/null; } 2>&1
                printf "\n"
            done
        } > resultCPLEX$j.txt
        rm *.log
    done
