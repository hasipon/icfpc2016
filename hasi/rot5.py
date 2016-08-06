import sys
import math
from fractions import Fraction

import sys
import math
from fractions import Fraction
from typing import Dict, List


class Vector:
    def __init__(self, x: Fraction, y: Fraction):
        self.x = x
        self.y = y

    @staticmethod
    def from_str(s: str):
        x, y = s.split(',')
        return Vector(Fraction(x), Fraction(y))

    def __repr__(self):
        return "Vector(" + str(self.x) + ', ' + str(self.y) + ")"

    def __str__(self):
        return str(self.x) + ',' + str(self.y)

    def __eq__(self, other):
        return self.x == other.x and self.y == other.y

    def __lt__(self, other):
        return self.x < other.x or (self.x == other.x and self.y < other.y)

    def __hash__(self):
        return (self.x, self.y).__hash__()


with open(sys.argv[1]) as f:
    nv = int(f.readline())
    vs = [Vector.from_str(f.readline()) for _ in range(nv)]
    ng = int(f.readline())
    g = [f.readline().rstrip() for _ in range(ng)]
    vd = [Vector.from_str(f.readline()) for _ in range(nv)]

print(nv)
for v in vs:
    print(v)
print(ng)
for s in g:
    print(s)
for v in vd:
    print(Vector(
        Fraction(3, 5) * v.x  + Fraction(-4, 5) * v.y,
        Fraction(4, 5) * v.x + Fraction(3, 5) * v.y,
    ))
