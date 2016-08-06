import sys
import math
from fractions import Fraction
from typing import Dict, List
import hashlib
import os.path


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


class Segment:
    def __init__(self, p0: Vector, p1: Vector):
        self.p0 = p0
        self.p1 = p1

    def __repr__(self):
        return "Segment(" + repr(self.p0) + ', ' + repr(self.p1) + ")"


class Polygon:
    def __init__(self, points: List[Vector]):
        self.points = points


class Problem:
    def __init__(self):
        #: :type: List[Polygon]
        self.polygons = []

    def load(self, filename):
        with open(filename) as f:
            num_polygons = int(f.readline())
            for _ in range(num_polygons):
                num_vertices = int(f.readline())
                self.polygons.append(Polygon([Vector.from_str(f.readline()) for _ in range(num_vertices)]))


class Solution:
    def __init__(self):
        #: :type: List[Vector]
        self.source = None
        #: :type: List[str]
        self.area = None
        #: :type: List[Vector]
        self.target = None

    def load(self, filename):
        with open(filename) as f:
            nv = int(f.readline())
            self.source = [Vector.from_str(f.readline()) for _ in range(nv)]
            na = int(f.readline())
            self.area = [f.readline() for _ in range(na)]
            self.target = [Vector.from_str(f.readline()) for _ in range(nv)]


def hoge(v: List[Vector]) -> str:
    r = None
    for i in range(len(v)):
        s = ' '.join(map(str, v[i:] + v[:i]))
        if r is None or s < r:
            r = s
    return r


def func(v: List[Vector], flip_x, flip_y, swap_xy):
    def f(p: Vector):
        x = -p.x if flip_x else p.x
        y = -p.y if flip_y else p.y
        if swap_xy:
            x, y = y, x
        return Vector(x, y)
    return [f(q) for q in v]


def calc(polygons: List[List[Vector]], solution: Solution, flip_x, flip_y, swap_xy):
    problem0 = [func(q, flip_x, flip_y, swap_xy) for q in polygons]
    if flip_x:
        problem0 = problem0[::-1]
    if flip_y:
        problem0 = problem0[::-1]
    if swap_xy:
        problem0 = problem0[::-1]
    source = solution.source
    target0 = func(solution.target, flip_x, flip_y, swap_xy)

    min_x = min(min(p.x for p in q) for q in problem0)
    min_y = min(min(p.y for p in q) for q in problem0)
    problem = [[Vector(p.x - min_x, p.y - min_y) for p in q] for q in problem0]
    target = [Vector(p.x - min_x, p.y - min_y) for p in target0]

    moved_polygons = ';'.join(sorted(hoge(p) for p in problem)).encode()
    h = hashlib.sha1(moved_polygons).hexdigest()
    ref_dir = os.path.join(os.path.dirname(__file__), 'reference')
    ref_path = os.path.join(ref_dir, h + '.txt')
    if os.path.exists(ref_path):
        return
    with open(ref_path, 'w') as f:
        f.write('%d\n' % len(solution.source))
        for s in source:
            f.write('%s\n' % s)
        f.write('%d\n' % len(solution.area))
        for s in solution.area:
            f.write(s)
        for s in target:
            f.write('%s\n' % s)


def main():
    problem = Problem()
    problem.load(sys.argv[1])
    solution = Solution()
    solution.load(sys.argv[2])
    for i in range(8):
        calc([x.points for x in problem.polygons], solution, bool(i & 4), bool(i & 2), bool(i & 1))


main()
