cd $(dirname $0)

for x in ../problems/*.txt; do
  echo $x
  python3.5 solve_ref.py $x solution_ref/$(basename $x)
done
