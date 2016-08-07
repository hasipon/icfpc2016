cd $(dirname $0)

for x in ../../problems/*.txt; do
  if [ ! -e problems/$(basename $x) ]; then
    echo $(basename $x)
    python3.5 read_problem.py $x > problems/$(basename $x)
  fi
done
