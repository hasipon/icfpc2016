import json
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


def sub(s: Vector, t: Vector):
    return Vector(s.x - t.x, s.y - t.y)


def cross(s: Vector, t: Vector):
    return s.x * t.y - s.y * t.x


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
    min_x = min(s.x for s in a)
    min_y = min(s.y for s in a)
    b = [Vector(s.x - min_x, s.y - min_y) for s in a]
    if max(s.x for s in b) > Fraction(1) or max(s.y for s in b) > Fraction(1):
        return
        # todo 回転を考える

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
