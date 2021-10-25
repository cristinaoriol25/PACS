# TODO: time pasandoles distintos tamaños de matrices
sizes="800 1000 1200 1500 2000 3000"
executables="sequential my_eigen_matmult"
repeat=10
out="logs/comparison.log"

echo "method N clk(ini) clk(mult) User(s) System(s) Real(s)" > ${out}



for ex in $executables; do
  echo "Testing ${ex}..."
  for n in $sizes; do
    for ((i=0; i<repeat; i++)); do
      echo "Size ${n}..."
      # echo -n "${ex} ${n} " >> "logs/${ex}.log" # en ficheros distintos
      echo -n "${ex} ${n} " >> ${out}
      # {time -o "./${ex}" ${n}} 2> "logs/${ex}-${n}.log"
      { \time -f "%U %S %e" -a -o ${out} "./${ex}" ${n}; } >> ${out}
    done
  done
  echo "-----------------------"
done
