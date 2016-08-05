
for x in ../problems/*.txt; do
  echo $x
  python3.5 conv.py $x > ../problems2/$(basename $x)
done
