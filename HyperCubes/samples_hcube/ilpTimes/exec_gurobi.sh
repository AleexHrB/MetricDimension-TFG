for j in {1..3}
do
    {
        for i in {1..9}
        do
            printf "Time for $i \n"
            { time ./gurobi_cl TimeLimit=600 ../../ilpSamples/samples/prueba$i.lp 1>/dev/null; } 2>&1
                printf "\n"
                rm gurobi.log
            done
        } > resultGurobi$j.txt

    done
