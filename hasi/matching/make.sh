cd $(dirname $0)

pushd ..
python3.5 solved.py ../solutions/ ../challenges/ > solved.txt
popd

awk '{print "./make_calc.sh "$1" "$2; }' ../solved.txt > make_main.sh
chmod +x make_main.sh
./make_main.sh
