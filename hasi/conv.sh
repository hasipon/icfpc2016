
for x in ../problems/*.txt; do
  echo $x
  python3 eval.py $x > ../problems2/$(basename $x)
done
