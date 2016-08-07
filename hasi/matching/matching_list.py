import os.path
from glob import glob

with open(os.path.join(os.path.dirname(__file__), '..', 'solved.txt')) as f:
    solved = {int(x.split(' ')[0]) for x in f.readlines()}

for x in glob(os.path.join(os.path.dirname(__file__), 'solution', '*.txt')):
    y = int(os.path.basename(x)[:-4])
    if y not in solved:
        print(y)
