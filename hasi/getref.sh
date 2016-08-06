cd $(dirname $0)
python3.5 solved.py ../solutions/ > solved.txt
awk '{print "python3.5 getref.py ../problems/"$1".txt ../solutions/"$1"-"$2".txt" }' solved.txt > getref_main.sh
chmod +x getref_main.sh
./getref_main.sh
