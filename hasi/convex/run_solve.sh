cd $(dirname $0)

for x in problems/*.txt; do
  if [ ! -e solutions/$(basename $x) ]; then
    echo $x
    python3.5 solve.py $x solutions/$(basename $x)
  fi
done
