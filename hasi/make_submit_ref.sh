cd $(dirname $0)
cd ..

python3.5 hasi/submit_list.py > hasi/submit_list.txt
awk '{print "./solution-submit "$0" hasi/solution_ref/"$0".txt" }' hasi/submit_list.txt
