# TODO: time pasandoles distintos tamaños de matrices
sizes="50 100 200 500 700 800 1000 1200 1500 2000"
executables="sequential my_eigen_matmult my_eigen_matmult_no_vect"

for ex in $executables; do
  echo "Testing ${ex}..."
  for n in $sizes; do
    echo "Size ${n}..."
    # {time -o "./${ex}" ${n}} 2> "logs/${ex}-${n}.log"
    \time -f "%U %S %e" -o "logs/${ex}-${n}.log" "./${ex}" ${n}
  done
  echo "-----------------------"
done
