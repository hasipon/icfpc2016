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
        self.segments = [Segment(p0, p1) for p0, p1 in zip(points, points[1:] + points[:1])]

    def __repr__(self):
        return "Polygon(" + repr(self.points) + ")"


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


def hoge(v: List[Vector]) -> str:
    r = None
    for i in range(len(v)):
        s = ' '.join(map(str, v[i:] + v[:i]))
        if r is None or s < r:
            r = s
    return r


def main():
    problem = Problem()
    problem.load(sys.argv[1])
    min_x = problem.polygons[0].points[0].x
    min_y = problem.polygons[0].points[0].y
    for p in problem.polygons:
        for q in p.points:
            min_x = min(min_x, q.x)
            min_y = min(min_y, q.y)
    moved_polygons = ';'.join(sorted(
        hoge([Vector(q.x - min_x, q.y - min_y) for q in p.points])
        for p in problem.polygons
    )).encode()
    h = hashlib.sha1(moved_polygons).hexdigest()
    ref_dir = os.path.join(os.path.dirname(__file__), 'reference')
    ref_path = os.path.join(ref_dir, h + '.txt')
    if not os.path.exists(ref_path):
        return
    with open(ref_path) as f:
        with open(sys.argv[2], 'w') as w:
            nv = f.readline()
            w.write(nv)
            for _ in range(int(nv)):
                w.write(f.readline())
            na = f.readline()
            w.write(na)
            for _ in range(int(na)):
                w.write(f.readline())
            for _ in range(int(nv)):
                v = Vector.from_str(f.readline())
                w.write('%s\n' % Vector(v.x + min_x, v.y + min_y))


main()
