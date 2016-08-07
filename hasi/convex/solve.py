import json
import sys
import math
from fractions import Fraction
from typing import Dict, List
import hashlib
import os.path


ZERO = Fraction(0)
ONE = Fraction(1)


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


class Edge:
    def __init__(self, p0: Vector, p1: Vector):
        self.p0 = p0
        self.p1 = p1

    def __repr__(self):
        return "Edge(" + repr(self.p0) + ', ' + repr(self.p1) + ")"

    def cross(self, p: Vector):
        return cross(sub(p, self.p0), sub(self.p1, self.p0))

    def cross_point(self, s: Vector, t: Vector):
        v0 = sub(self.p0, self.p1)
        v1 = sub(t, s)
        v2 = sub(t, self.p1)
        b = (- v0.y * v2.x + v0.x * v2.y) / (v0.x * v1.y - v1.x * v0.y)
        return Vector(t.x - b * v1.x, t.y - b * v1.y), b

    def mirror(self, p: Vector):
        a = self.p1.y - self.p0.y
        b = self.p0.x - self.p1.x
        c = a * self.p0.x + b * self.p0.y
        d = a * p.y - b * p.x
        e = a * a + b * b
        x = (a*c - b*d) / e
        y = (b*c + a*d) / e
        v = Vector(x + x - p.x, y + y - p.y)
        return Vector(x + x - p.x, y + y - p.y)


class Facet:
    def __init__(self, src: List[Vector], dst: List[Vector]):
        self.src = src
        self.dst = dst
        if not src:
            raise Exception()

    def __repr__(self):
        return "Facet(" + repr(self.src) + ', ' + repr(self.dst) + ")"

    def cut(self, e: Edge):
        dst_to_src = {d: s for s, d in zip(self.src, self.dst)}
        dst_cross = [e.cross(s) for s in self.dst]
        point_mapping = {
            p: e.mirror(p) if c > ZERO else p
            for p, c in zip(self.dst, dst_cross)
        }
        cross_point = set()
        segments = []
        for s, t, p0, p1 in zip(dst_cross, dst_cross[1:] + dst_cross[:1], self.dst, self.dst[1:] + self.dst[:1]):
            if s == ZERO and t == ZERO:
                return [Facet(self.src, [point_mapping[s] for s in self.dst])]
            elif (s < ZERO < t) or (s > ZERO > t):
                p2, b = e.cross_point(p0, p1)
                cross_point.add(p2)
                s0 = dst_to_src[p0]
                s1 = dst_to_src[p1]
                ss = sub(s0, s1)
                s2 = Vector(b * ss.x + s1.x, b * ss.y + s1.y)
                point_mapping[p2] = p2
                dst_to_src[p2] = s2
                segments.append((p0, p2))
                segments.append((p2, p1))
            else:
                if s == ZERO:
                    cross_point.add(p0)
                if t == ZERO:
                    cross_point.add(p1)
                segments.append((p0, p1))

        if len(cross_point) < 2:
            return [Facet(self.src, [point_mapping[s] for s in self.dst])]

        plus_edges = []
        minus_edges = []
        for s, t in segments:
            cs = e.cross(s)
            ct = e.cross(t)
            if cs < ZERO or ct < ZERO:
                minus_edges.append((s, t))
            else:
                plus_edges.append((s, t))

        facets = []

        for es in (plus_edges, minus_edges):
            src = []
            dst = []
            used = set()
            for p in es:
                for s in p:
                    if s not in used:
                        used.add(s)
                        src.append(dst_to_src.get(s))
                        dst.append(point_mapping[s])
            facets.append(Facet(src, dst))

        return facets


def calc(v: List[Vector]) -> List[Facet]:
    u = [Vector(ZERO, ZERO), Vector(ONE, ZERO), Vector(ONE, ONE), Vector(ZERO, ONE)]
    facets = [Facet(u, u)]

    edges = [Edge(s, t) for s, t in zip(v, v[1:] + v[:1])]

    idx = 0
    while True:
        if len(facets) > 3000:
            return []
        # sys.stderr.write('%d\n' % len(facets))

        # select edge
        e = None
        for i in range(len(edges)):
            ee = edges[idx]
            idx = (idx + 1) % len(edges)
            if any(any(ee.cross(d) > 0 for d in c.dst) for c in facets):
                e = ee
                break

        if not e:
            break

        #: :type: List[Facet]
        new_facets = sum((c.cut(e) for c in facets), [])
        facets = new_facets
    return facets


def main():
    with open(sys.argv[1]) as f:
        data = json.loads(f.read())
        if not data['a']:
            return
    facets = calc([Vector.from_str(s) for s in data['v']])
    if not facets:
        return

    a11, a12, a13 = map(Fraction, data['x'])
    a21, a22, a23 = map(Fraction, data['y'])
    print([a11, a12, a13, a21, a22, a23])

    #: :type: Dict[Vector, Vector]
    mapping = {}
    for f in facets:
        for s, d in zip(f.src, f.dst):
            mapping[s] = d
    src_v_list = list(mapping.keys())
    src_v_dict = {s: i for i, s in enumerate(src_v_list)}

    print(len(src_v_list))
    for s in src_v_list:
        print(s)
    print(len(facets))
    for s in facets:
        print(' '.join(map(str, [len(s.src)] + [src_v_dict[t] for t in s.src])))
    for s in src_v_list:
        p = mapping[s]
        q = Vector(p.x * a11 + p.y * a12 + a13, p.x * a21 + p.y * a22 + a23)
        print(q)


main()
