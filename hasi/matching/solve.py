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


def read_reference_solution(data):
    nv = int(data[0])
    src = [Vector.from_str(s) for s in data[1:nv+1]]
    na = int(data[nv+1])
    area = data[nv+2:nv+2+na]
    dst = [Vector.from_str(s) for s in data[nv+2+na:nv+2+na+nv]]
    return src, area, dst


def sub(s: Vector, t: Vector):
    return Vector(s.x - t.x, s.y - t.y)


def dot(s: Vector, t: Vector):
    return s.x * t.x + s.y * t.y


def crs(s: Vector, t: Vector):
    return s.x * t.y - s.y * t.x


def sq(s: Vector):
    return dot(s, s)


def move(a, s: Vector):
    a11, a12, a13 = a[0]
    a21, a22, a23 = a[1]
    return Vector(
        a11 * s.x + a12 * s.y + a13,
        a21 * s.x + a22 * s.y + a23,
    )


def calc_matrix(s0: Vector, s1: Vector, s2: Vector, t0: Vector, t1: Vector, t2: Vector):
    s01 = sub(s1, s0)
    s12 = sub(s2, s1)
    t01 = sub(t1, t0)
    t12 = sub(t2, t1)
    if sq(s01) != sq(t01) or sq(s12) != sq(t12) or dot(s01, s12) != dot(t01, t12):
        return

    d = sq(s01)
    cc = dot(t01, s01) / d
    ss = crs(t01, s01) / d
    x = t0.x - cc * s0.x - ss * s0.y
    y = t0.y + ss * s0.x - cc * s0.y
    m = [[cc, ss, x], [-ss, cc, y]]
    u2 = move(m, s2)
    if u2.x == t2.x and u2.y == t2.y:
        return m

    print('warn')
    return None


def normalize(a: List[List[Vector]]):
    return sorted(
        min(s[i:] + s[:i] for i in range(len(s)))
        for s in a
    )


def get_matrix(polygons: List[List[Vector]], ref_polygon: List[List[Vector]]):
    s0, s1, s2 = ref_polygon[0][:3]
    target = normalize(polygons)
    for p in polygons:
        for t0, t1, t2 in zip(p, p[1:] + p[:1], p[2:] + p[:2]):
            m = calc_matrix(s0, s1, s2, t0, t1, t2)
            if not m:
                continue
            a = normalize([[move(m, t) for t in s] for s in ref_polygon])
            if target == a:
                return m
    return None


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
    ref_dir = os.path.join(os.path.dirname(__file__), 'reference')
    ref_path = os.path.join(ref_dir, name + '.txt')
    if not os.path.exists(ref_path):
        return
    with open(ref_path) as f:
        data = json.loads(f.read())
        ref_polygons = [[Vector.from_str(t) for t in s] for s in data[0]]
        ref_src, ref_area, ref_dst = read_reference_solution(data[1].split('\n'))

    a = get_matrix(polygons, ref_polygons)
    if not a:
        print('error')
        return

    with open(sys.argv[2], 'w') as w:
        w.write('%d\n' % len(ref_src))
        for s in ref_src:
            w.write('%s\n' % s)
        w.write('%d\n' % len(ref_area))
        for s in ref_area:
            w.write('%s\n' % s)
        for s in ref_dst:
            w.write('%s\n' % move(a, s))


main()
