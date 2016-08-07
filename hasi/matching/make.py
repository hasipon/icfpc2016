import sys
import math
from fractions import Fraction
from typing import Dict, List
import hashlib
import os.path
import json


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


def calc_hash(polygons: List[List[Vector]], u: Vector):
    def f(t: Vector):
        return t.x*t.x + t.y*t.y

    def g(t: Vector):
        return t.x*u.y - t.y*u.x

    def h(t: Vector):
        return t.x*u.x + t.y*u.y

    a = [
        [(f(t), g(t), h(t)) for t in s]
        for s in polygons
    ]
    b = sorted(
        min(s[i:] + s[:i] for i in range(len(s)))
        for s in a
    )
    return hashlib.sha1(
        ';'.join(','.join('%s %s %s' % (t1, t2, t3) for t1, t2, t3 in s) for s in b).encode()
    ).hexdigest()


def calc(polygons: List[List[Vector]]):
    sum_x = Fraction(0)
    sum_y = Fraction(0)
    n = 0
    for s in polygons:
        for t in s:
            sum_x += t.x
            sum_y += t.y
            n += 1
    x0 = sum_x / Fraction(n)
    y0 = sum_y / Fraction(n)
    polygons_moved = [[Vector(t.x - x0, t.y - y0) for t in s] for s in polygons]
    polygons_flip = [[Vector(-t.x, t.y) for t in s][::-1] for s in polygons_moved]
    hash_set = set()
    for s in polygons_moved:
        for p1 in s:
            if p1.x != 0 or p1.y != 0:
                hash_set.add(calc_hash(polygons_moved, p1))
    for s in polygons_flip:
        for p1 in s:
            if p1.x != 0 or p1.y != 0:
                hash_set.add(calc_hash(polygons_flip, p1))
    return min(hash_set)


def main():
    if not os.path.exists(sys.argv[1]):
        return
    with open(sys.argv[1]) as f:
        num_polygons = int(f.readline())
        polygons = []
        for _ in range(num_polygons):
            num_vertices = int(f.readline())
            polygons.append([Vector.from_str(f.readline()) for _ in range(num_vertices)])
        name = calc(polygons)
    print(name)
    with open(sys.argv[2]) as f:
        solution = f.read()
    print(json.dumps([[[str(t) for t in s] for s in polygons], solution]))


main()
