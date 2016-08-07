import os.path
from glob import glob
import sys

with open(os.path.join(os.path.dirname(__file__), '..', 'solved.txt')) as f:
    solved = {int(x.split(' ')[0]) for x in f.readlines()}

for x in glob(os.path.join(os.path.dirname(__file__), 'hull_solutions', '*.txt')):
    y = int(os.path.basename(x)[:-4])
    if y not in solved:
        with open(x) as f:
            t = f.read()
            cnt = sum(c not in ('\r', '\n', ' ') for c in t)
            if cnt <= 5000:
                print(y)
            # else:
            #    sys.stderr.write('%s over : %d\n' % (x, cnt))
