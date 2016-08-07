cd $(dirname $0)

pushd ..
python3.5 solved.py ../solutions/ ../challenges/ > solved.txt
popd

python3.5 matching_list.py > matching_list.txt
awk '{print "./solution-submit "$0" hasi/matching/solution/"$0".txt" }' matching_list.txt
