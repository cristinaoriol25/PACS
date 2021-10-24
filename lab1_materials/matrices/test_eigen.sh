# TODO: time pasandoles distintos tamaños de matrices
sizes="10000" # 2000 2200 2400 2800 3000 
executables="my_eigen_matmult my_eigen_matmult_no_vect"
repeat=10

echo "method N User(s) System(s) Real(s)" > "logs/comparison.log"

out="comparison-eigen.log"

for ex in $executables; do
  echo "Testing ${ex}..."
  for n in $sizes; do
    for ((i=0; i<repeat; i++)); do
      echo "Size ${n}..."
      # echo -n "${ex} ${n} " >> "logs/${ex}.log" # en ficheros distintos
      echo -n "${ex} ${n} " >> "logs/${out}"
      # {time -o "./${ex}" ${n}} 2> "logs/${ex}-${n}.log"
      \time -f "%U %S %e" -a -o "logs/${out}" "./${ex}" ${n}
    done
  done
  echo "-----------------------"
done
