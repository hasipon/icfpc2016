cd $(dirname $0)

for x in ../../problems/*.txt; do
  if [ ! -e solution/s_$(basename $x)_ ]; then
    echo $(basename $x)
    python3.5 solve.py $x solution/$(basename $x)
    touch solution/s_$(basename $x)_
  fi
done
