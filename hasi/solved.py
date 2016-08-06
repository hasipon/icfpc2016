from glob import glob
import os.path
import sys
import json

solved = set()
for x in glob(os.path.join(sys.argv[1], '*.json')):
    problem_id = int(os.path.basename(x).split('-')[0])
    with open(x) as f:
        s = json.loads(f.read())
        if s['resemblance'] == 1:
            solved.add(problem_id)
for x in sorted(solved):
    print(x)
