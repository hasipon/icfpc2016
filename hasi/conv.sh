
for x in ../problems/*.txt; do
  if [ ! -e ../problems2/$(basename $x) ]; then
    echo $x
    python3.5 conv.py $x > ../problems2/$(basename $x)
  fi
done
