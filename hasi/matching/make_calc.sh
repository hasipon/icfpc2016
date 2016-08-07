cd $(dirname $0)

if [ ! -e reference/$1 ]; then
  echo $1
  python3.5 make.py ../../problems/$1.txt ../../solutions/$1-$2.txt
  touch reference/$1
fi
