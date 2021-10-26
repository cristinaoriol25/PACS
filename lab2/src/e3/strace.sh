# TODO: time pasandoles distintos tamaños de matrices
executables="sequential my_eigen_matmult"

out="logs/e3-strace.log"

N=3000
# echo "method N clk(ini) clk(mult) User(s) System(s) Real(s)" > ${out}

mkdir "logs"

for ex in $executables; do
  echo "${ex} with CLOCK:" >> ${out} 2>&1
  strace -c "./${ex}" $N >> ${out} 2>&1
  echo "-----------------------" >> ${out} 2>&1
  echo "${ex} with gettimeofday:" >> ${out} 2>&1
  strace -c "./e2/${ex}" $N >> ${out} 2>&1
  echo "-----------------------" >> ${out} 2>&1
done
