cd $(dirname $0)

pushd ..
python3.5 solved.py ../solutions/ ../challenges/ > solved.txt
popd

python3.5 hull_list.py > hull_list.txt
awk '{print "./solution-submit "$0" hasi/convex/hull_solutions/"$0".txt" }' hull_list.txt
