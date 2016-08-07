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
            solved.add((problem_id, s['solution_spec_hash']))
for x in glob(os.path.join(sys.argv[2], '*.json')):
    with open(x) as f:
        s = json.loads(f.read())
        solved.add((s['problem_id'], ''))
for x, t in sorted(solved):
    print(x, t)
