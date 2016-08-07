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
    if max(s.x for s in b) <= Fraction(1) and max(s.y for s in b) <= Fraction(1):
        return {
            'a': True,
            'x': ['1', '0', str(min_x)],  # 出力変換式
            'y': ['0', '1', str(min_y)],
            'v': [str(s) for s in b],
        }

    pyt = [
        (3, 4, 5),
        (5, 12, 13),
        (7, 24, 25),
        (8, 15, 17),
        (9, 40, 41),
        (11, 60, 61),
        (12, 35, 37),
        (13, 84, 85),
        (16, 63, 65),
        (20, 21, 29),
        (28, 45, 53),
        (33, 56, 65),
        (36, 77, 85),
        (39, 80, 89),
        (48, 55, 73),
        (65, 72, 97),
        (20, 99, 101),
        (60, 91, 109),
        (15, 112, 113),
        (44, 117, 125),
        (88, 105, 137),
        (17, 144, 145),
        (24, 143, 145),
        (51, 140, 149),
        (85, 132, 157),
        (119, 120, 169),
        (52, 165, 173),
        (19, 180, 181),
        (57, 176, 185),
        (104, 153, 185),
        (95, 168, 193),
        (28, 195, 197),
        (84, 187, 205),
        (133, 156, 205),
        (21, 220, 221),
        (140, 171, 221),
        (60, 221, 229),
        (105, 208, 233),
        (120, 209, 241),
        (32, 255, 257),
        (23, 264, 265),
        (96, 247, 265),
        (69, 260, 269),
        (115, 252, 277),
        (160, 231, 281),
        (161, 240, 289),
        (68, 285, 293),
    ]
    for aa, bb, cc in pyt:
        for i in range(8):
            cs = Fraction(aa, cc)
            sn = Fraction(bb, cc)
            if i & 1: cs, sn = sn, cs
            if i & 2: cs = -cs
            if i & 4: sn = -sn
            a_rot = [Vector(cs * s.x + sn * s.y, - sn * s.x + cs * s.y) for s in a]
            min_x = min(s.x for s in a_rot)
            min_y = min(s.y for s in a_rot)
            b_rot = [Vector(s.x - min_x, s.y - min_y) for s in a_rot]
            if max(s.x for s in b_rot) <= Fraction(1) and max(s.y for s in b_rot) <= Fraction(1):
                return {
                    'a': True,
                    'x': [str(cs), str(-sn), str((cs * min_x - sn * min_y))],  # 出力変換式
                    'y': [str(sn), str(cs), str((sn * min_x + cs * min_y))],
                    'v': [str(s) for s in b_rot],
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
