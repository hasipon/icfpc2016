cd $(dirname $0)

pushd ..
python3.5 solved.py ../solutions/ ../challenges/ > solved.txt
popd

python3.5 convex_list.py > convex_list.txt
awk '{print "./solution-submit "$0" hasi/convex/solutions/"$0".txt" }' convex_list.txt
