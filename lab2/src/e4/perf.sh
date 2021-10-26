executables="sequential my_eigen_matmult"

out="logs/e4-perf.log"
reps=5
N=3000
# echo "method N clk(ini) clk(mult) User(s) System(s) Real(s)" > ${out}

mkdir "logs"

# perf stat -e cycles,instructions ls
for ex in $executables; do
  echo "${ex} with CLOCK:" >> ${out} 2>&1
  perf stat -r ${reps} "./${ex}" $N >> ${out} 2>&1
  echo "-----------------------" >> ${out} 2>&1
  echo "${ex} with gettimeofday:" >> ${out} 2>&1
  perf stat -r ${reps} "./e2/${ex}" $N >> ${out} 2>&1
  echo "-----------------------" >> ${out} 2>&1
done
