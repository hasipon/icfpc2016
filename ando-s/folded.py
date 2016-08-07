# python folded.py <width>
# で，1辺の長さを(1-width)になるように折りたたんでから風車を折る．
# 制約: width <= 1/3

import sys
from fractions import Fraction
from typing import NamedTuple

Point = NamedTuple('Point', [('x', Fraction), ('y', Fraction)])

# 反時計回りに90度回転
def rot90(p: Point) -> Point:
    return Point(-p.y, p.x)

w=Fraction(sys.argv[1])

# srcs, dsts は (1,1), (-1,1), (-1,-1), (1,-1) を四隅としているので，あとで変換して戻す
srcs = [
    Point(-Fraction('1'), Fraction('1')),
    Point(-w, Fraction('1')),
    Point(Fraction('0'), Fraction('1')),
    Point(-w/2, 1-w/2),
    Point(-w, 1-w),
    Point(Fraction('0'), 1-w),
    Point(-(1+w)/2, (1+w)/2),
    Point(-Fraction('1/2'), Fraction('1/2')),
    Point(-(1-w)/2, (1-w)/2),
    Point(-Fraction('1'), w),
    Point(-1+w, w),
]

dsts = [
    Point(Fraction('0'), 1 - w),
    Point(Fraction('0'), Fraction('0')),
    Point(Fraction('0'), w),
    Point(-w/2, w/2),
    Point(Fraction('0'), w),
    Point(Fraction('0'), Fraction('0')),
    Point(-(1-w)/2, (1-w)/2),
    Point(w-Fraction('1/2'), Fraction('1/2')),
    Point(-(1-w)/2, (1-w)/2),
    Point(Fraction('0'), Fraction('0')),
    Point(Fraction('0'), w),
]

size = len(srcs)

facets = [
    (0,6,1),
    (1,3,2),
    (1,6,7,4),
    (1,4,3),
    (3,4,5),
    (4,7,8,5),
    (0,9,6),
    (6,9,10,7),
    (9,size+2,10),
    (10,size+2,size+3,size+5),
    (7,10,size+5,size+8,8),
]

for i in range(size,4*size):
    srcs.append(rot90(srcs[i-size]))
    dsts.append(rot90(dsts[i-size]))
for i in range(4*size):
    srcs[i]=Point((srcs[i].x+1)/2,(srcs[i].y+1)/2)
    dsts[i]=Point((dsts[i].x+1)/2,(dsts[i].y+1)/2)

for i in range(size,4*size):
    facets.append(tuple((x+size) % (4*size) for x in facets[i-size]))
facets.append((8,8+size,8+2*size,8+3*size))


# print solution
print(len(srcs))
for p in srcs:
    print('{},{}'.format(p.x,p.y))
print(len(facets))
for f in facets:
    print(len(f),' '.join(map(str,f)))
for p in dsts:
    print('{},{}'.format(p.x,p.y))
