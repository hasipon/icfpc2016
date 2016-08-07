import json
import sys
import math
from fractions import Fraction
from typing import Dict, List
import hashlib
import os.path

def sqrt(n: Fraction):
    if n == Fraction(0):
        return Fraction(0)

    small = Fraction(0)
    large = Fraction(n)

    for i in range(0,1000):
        mid = (small + large) / Fraction(2)
        if mid * mid < n:
            small = mid
        else:
            large = mid
    return large if large * large == n else None

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

    def norm(self):
        return self.x * self.x + self.y * self.y

    def abs(self):
        return sqrt(self.norm())

def sub(s: Vector, t: Vector):
    return Vector(s.x - t.x, s.y - t.y)


def cross(s: Vector, t: Vector):
    return s.x * t.y - s.y * t.x

def rot(v: Vector, sin: Fraction):
    cos = Fraction(1) - sin
    x = v.x * cos - v.y * sin
    y = v.x * sin + v.y * cos
    return Vector(x, y)

def rot_angle(_v: Vector):
    v = Vector(_v.x, _v.y)
    v.x = max(v.x, -1 * v.x)
    v.y = max(v.y, -1 * v.y)
    if v.abs() is None:
        return None
    return v.y / v.abs()

def calc(polygons: List[List[Vector]]):
    # 穴あきは対象外
    if len(polygons) >= 2:
        return
    a = polygons[0]

    # 凸チェック
    for s, t, u in zip(a, a[1:] + a[:1], a[2:] + a[:2]):
        if cross(sub(t, s), sub(u, t)) < Fraction(0):
            return

    # 0,0から1,1に収まってるかを確認
    def move(vs):
        min_x = min(s.x for s in vs)
        min_y = min(s.y for s in vs)
        return [Vector(s.x - min_x, s.y - min_y) for s in vs]

    # 遠いですか?
    def is_faraway(vs):
        if max(s.x for s in vs) > Fraction(1) or max(s.y for s in vs) > Fraction(1):
            return True
        if min(s.x for s in vs) < Fraction(0) or min(s.y for s in vs) < Fraction(0):
            return True
        return False

    b = a
    if is_faraway(a):
        for v, u in zip(a, a[1:]):
            if v == u: continue
            w = sub(v, u)
            th = rot_angle(w)
            if th is None: continue
            b = list(map(lambda n: rot(n, th), a))
            b = move(b)
            if not is_faraway(b): break

    min_x = min(s.x for s in b)
    min_y = min(s.y for s in b)
    return {
        'a': True,
        'x': ['1', '0', str(min_x)],  # 出力変換式
        'y': ['0', '1', str(min_y)],
        'v': [str(s) for s in b],
    }


def main():
    with open(sys.argv[1]) as f:
        num_polygons = int(f.readline())
        polygons = []
        for _ in range(num_polygons):
            num_vertices = int(f.readline())
            polygons.append([Vector.from_str(f.readline()) for _ in range(num_vertices)])
    r = calc(polygons)
    if r:
        print(json.dumps(r))
    else:
        print(json.dumps({'a': False}))


main()
