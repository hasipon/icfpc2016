cd $(dirname $0)

for x in hulls/*.json; do
  if [ ! -e hull_solutions/$(basename $x) ]; then
    echo $x
    python3.5 solve.py $x hull_solutions/$(basename $x)
  fi
done
