# TODO: time pasandoles distintos tamaños de matrices
sizes="50 100 200 500 700 800 1000 1200 1500 2000"
executables="sequential my_eigen_matmult my_eigen_matmult_no_vect"
repeat=10

echo "method N User(s) System(s) Real(s)" > "logs/comparison.log"


for ex in $executables; do
  echo "Testing ${ex}..."
  for n in $sizes; do
    for ((i=0; i<repeat; i++)); do
      echo "Size ${n}..."
      # echo -n "${ex} ${n} " >> "logs/${ex}.log" # en ficheros distintos
      echo -n "${ex} ${n} " >> "logs/comparison.log"
      # {time -o "./${ex}" ${n}} 2> "logs/${ex}-${n}.log"
      \time -f "%U %S %e" -a -o "logs/comparison.log" "./${ex}" ${n}
    done
  done
  echo "-----------------------"
done
