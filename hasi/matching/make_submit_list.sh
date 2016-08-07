cd $(dirname $0)

pushd ..
python3.5 solved.py ../solutions/ ../challenges/ > solved.txt
popd

python3.5 matching_list.py > matching_list.txt

# awk '{print "./solution-submit "$0" hasi/matching/solution/"$0".txt" }' matching_list.txt
for i in $(cat matching_list.txt); do
  size=`perl -pe 's|\s||g' solution/$i.txt | wc --bytes`
  if [ $size -le 5000 ]; then
    echo "./solution-submit $i hasi/matching/solution/$i.txt"
  else
    echo "# [SKIPPED] $i.txt (solution size = $size)"
  fi
done
