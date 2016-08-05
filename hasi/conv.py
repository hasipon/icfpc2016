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
        #: :type: List[Segment]
        self.segments = []

    def load(self, filename):
        with open(filename) as f:
            num_polygons = int(f.readline())
            for _ in range(num_polygons):
                num_vertices = int(f.readline())
                self.polygons.append(Polygon([Vector.from_str(f.readline()) for _ in range(num_vertices)]))
            num_segments = int(f.readline())
            for _ in range(num_segments):
                p0, p1 = (Vector.from_str(x) for x in f.readline().split(' '))
                self.segments.append(Segment(p0, p1))


def intersect(s: Segment, t: Segment):
    sx = s.p1.x - s.p0.x
    sy = s.p1.y - s.p0.y
    tx = t.p1.x - t.p0.x
    ty = t.p1.y - t.p0.y
    cross = sx * ty - sy * tx
    if cross == Fraction(0):
        return None
    ux = t.p0.x - s.p0.x
    uy = t.p0.y - s.p0.y
    a = (ux * ty - uy * tx) / cross
    b = (ux * sy - uy * sx) / cross
    if Fraction(0) < a < Fraction(1) and Fraction(0) < b < Fraction(1):
        return Vector(a * sx + s.p0.x, a * sy + s.p0.y)
    return None


def position(s: Segment, p: Vector):
    x0, y0 = s.p0.x, s.p0.y
    x1, y1 = s.p1.x, s.p1.y
    x2, y2 = p.x, p.y
    sx = x0 - x2
    tx = x1 - x2
    sy = y0 - y2
    ty = y1 - y2
    cross = sx * ty - sy * tx
    if cross != Fraction(0):
        return None
    dot = sx * tx + sy * ty
    if dot > Fraction(0):
        return None
    if x0 != x1:
        return (x2 - x0) / (x1 - x0)
    else:
        return (y2 - y0) / (y1 - y0)


class Vertices:
    def __init__(self, p: Problem):
        points = set()
        for x in p.polygons:
            for y in x.points:
                points.add(y)
        for x in p.segments:
            points.add(x.p0)
            points.add(x.p1)
            for y in p.segments:
                p2 = intersect(x, y)
                if p2 is not None:
                    points.add(p2)
        #: :type: List[Vector]
        self.v_list = sorted(points)
        #: :type: Dict[Vector, int]
        self.v_dict = {x: i for i, x in enumerate(self.v_list)}


class Graph:
    def __init__(self, p: Problem, v: Vertices):
        self.p = p
        self.v = v
        self.G = {i: set() for i in range(len(v.v_list))}
        self.e_polygon = set()
        self.area_idx_dict = {}
        self.areas = []
        self.painted = {}

    def add_segment(self, s: Segment, is_polygon: bool):
        a = []
        for k, v in enumerate(self.v.v_list):
            p = position(s, v)
            if p is not None:
                a.append((p, k))
        b = [x[1] for x in sorted(a)]
        for s, t in zip(b, b[1:]):
            self.G[s].add(t)
            self.G[t].add(s)
            if is_polygon:
                self.e_polygon.add((s, t))

    def visit(self, p, q, area_idx):
        self.area_idx_dict[(p, q)] = area_idx
        if q in self.areas[area_idx]:
            return
        self.areas[area_idx].append(q)
        # todo 有理数化
        min_c = 2
        max_c = -2
        selected_r = None
        for r in self.G[q]:
            if p != r:
                vp = self.v.v_list[p]
                vq = self.v.v_list[q]
                vr = self.v.v_list[r]
                sx = vq.x - vp.x
                sy = vq.y - vp.y
                tx = vr.x - vq.x
                ty = vr.y - vq.y
                crs = sx * ty - sy * tx
                c = (sx * tx + sy * ty) / math.sqrt(sx * sx + sy * sy) / math.sqrt(tx * tx + ty * ty)
                if crs >= Fraction(0):
                    if c < min_c:
                        min_c = c
                        selected_r = r
                elif min_c == 2:
                    if c > max_c:
                        max_c = c
                        selected_r = r
        self.visit(q, selected_r, area_idx)

    def paint(self, area_idx, is_inside):
        if area_idx in self.painted:
            assert self.painted[area_idx] == is_inside
            return
        self.painted[area_idx] = is_inside

    def build_area(self):
        for x in self.p.polygons:
            for y in x.segments:
                self.add_segment(y, True)
        for x in self.p.segments:
            self.add_segment(x, False)

        for i in range(len(self.G)):
            for j in self.G[i]:
                if (i, j) not in self.area_idx_dict:
                    area_idx = len(self.areas)
                    self.areas.append([i])
                    self.visit(i, j, area_idx)

        for s, t in self.e_polygon:
            area_idx_i = self.area_idx_dict[(s, t)]
            area_idx_o = self.area_idx_dict[(t, s)]
            self.paint(area_idx_i, True)
            self.paint(area_idx_o, False)

    def print(self):
        print(len(self.v.v_list))
        for v in self.v.v_list:
            print(str(v))

        res = []
        for idx, area in enumerate(self.areas):
            if idx in self.painted:
                if self.painted[idx]:
                    res.append(' '.join(str(x) for x in area))
            else:
                res.append('??? ' + ' '.join(str(x) for x in area))
        print(len(res))
        for x in res:
            print(x)


def main():
    problem = Problem()
    problem.load(sys.argv[1])
    vertices = Vertices(problem)
    graph = Graph(problem, vertices)
    graph.build_area()
    graph.print()


main()
