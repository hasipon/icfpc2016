cd $(dirname $0)

pushd ../../watanabe-yuya/convex/
make
popd

for x in ../../problems/*.txt; do
  if [ ! -e problems/$(basename $x) ]; then
    echo $(basename $x)
    python3.5 read_problem.py $x > problems/$(basename $x)
  fi
  if [ ! -e hulls/$(basename $x) ]; then
    echo $(basename $x)
    ../../watanabe-yuya/convex/a.out < $x > hulls/$(basename $x)_
    python3.5 read_problem.py hulls/$(basename $x)_ > hulls/$(basename $x)
  fi
done
