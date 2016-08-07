cd $(dirname $0)

pushd ..
python3.5 solved.py ../solutions/ ../challenges/ > solved.txt
popd

python3.5 convex_list.py > convex_list.txt

#awk '{print "./solution-submit "$0" hasi/convex/solutions/"$0".txt" }' convex_list.txt
for i in $(cat convex_list.txt); do
  size=`perl -pe 's|\s||g' solutions/$i.txt | wc --bytes`
  if [ $size -le 5000 ]; then
    echo "./solution-submit $i hasi/convex/solutions/$i.txt"
  else
    echo "# [SKIPPED] $i.txt (solution size = $size)"
  fi
done
