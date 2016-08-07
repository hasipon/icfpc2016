from glob import glob
import os.path
import sys
import json
import shutil

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
        problem_id = s['problem_id']
        solution_spec_hash = s['solution_spec_hash']
        solved.add((problem_id, solution_spec_hash))
        json_path = os.path.join(sys.argv[1], '%d-%s.json' % (problem_id, solution_spec_hash))
        if not os.path.exists(json_path):
            with open(json_path, 'w') as ff:
                tt = s
                tt['resemblance'] = 1
                ff.write(json.dumps(tt))
        shutil.copyfile(x[:-5] + '.txt', os.path.join(sys.argv[1], '%d-%s.txt' % (problem_id, solution_spec_hash)))
for x, t in sorted(solved):
    print(x, t)
