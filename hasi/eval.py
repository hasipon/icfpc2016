import sys
import math
from fractions import Fraction

problem = sys.argv[1]

with open(problem) as f:
    num_polygons = int(f.readline())
    polygons = []
    for _0 in range(num_polygons):
        num_vertices = int(f.readline())
        polygons.append(
            [
                tuple(Fraction(x) for x in f.readline().split(','))
                for _1 in range(num_vertices)
            ]
        )
    num_segments = int(f.readline())
    segments = []
    for _2 in range(num_segments):
        segments.append(
            [tuple(Fraction(y) for y in x.split(',')) for x in f.readline().split(' ')]
        )


def intersect(s, t):
    sx = s[1][0] - s[0][0]
    sy = s[1][1] - s[0][1]
    tx = t[1][0] - t[0][0]
    ty = t[1][1] - t[0][1]
    cross = sx * ty - sy * tx
    if cross == Fraction(0):
        return None
    ux = t[0][0] - s[0][0]
    uy = t[0][1] - s[0][1]
    a = (ux * ty - uy * tx) / cross
    b = (ux * sy - uy * sx) / cross
    if Fraction(0) < a < Fraction(1) and Fraction(0) < b < Fraction(1):
        return a * sx + s[0][0], a * sy + s[0][1]
    return None


v_set = set()
for x in polygons:
    for y in x:
        v_set.add(y)
for x in segments:
    v_set.add(x[0])
    v_set.add(x[1])
    for y in segments:
        v = intersect(x, y)
        if v is not None:
            v_set.add(v)


def position(p0, p1, v):
    x0, y0 = p0
    x1, y1 = p1
    x2, y2 = v
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


class Hoge:
    def __init__(self, v_set):
        self.v_list = sorted(v_set)
        self.v_dict = {x: i for i, x in enumerate(self.v_list)}
        self.G = {i: set() for i in range(len(v_set))}
        self.polygon_idx = {}
        self.polygon = None
        self.polygon2 = []
        self.polygon3 = {}

    def add_segment(self, p0, p1):
        a = []
        for v, k in hoge.v_dict.items():
            p = position(p0, p1, v)
            if p is not None:
                a.append((p, k))
        b = [x[1] for x in sorted(a)]
        for s, t in zip(b, b[1:]):
            self.G[s].add(t)
            self.G[t].add(s)

    def visit(self, p, q):
        if q in self.polygon:
            return True
        self.polygon.append(q)
        # todo 有理数化
        min_c = 2
        max_c = -2
        selected_r = None
        for r in self.G[q]:
            if p != r:
                vp = self.v_list[p]
                vq = self.v_list[q]
                vr = self.v_list[r]
                sx = vq[0] - vp[0]
                sy = vq[1] - vp[1]
                tx = vr[0] - vq[0]
                ty = vr[1] - vq[1]
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
        if selected_r is None:
            return False
        return self.visit(q, selected_r)

    def build(self, polygons):
        n = len(self.G)
        for i in range(n):
            for j in self.G[i]:
                if (i, j) not in self.polygon_idx:
                    self.polygon = [i]
                    if self.visit(i, j):
                        idx = len(self.polygon2)
                        self.polygon2.append(self.polygon)
                        for k in range(len(self.polygon)):
                            self.polygon_idx[(self.polygon[k], self.polygon[(k+1) % len(self.polygon)])] = idx
        for x in polygons:
            a = [self.v_dict[y] for y in x]
            for i in range(len(a)):
                s = a[i]
                t = a[(i + 1) % len(a)]
                idx_i = self.polygon_idx[(s, t)]
                idx_o = self.polygon_idx[(t, s)]
                if idx_i in self.polygon3:
                    assert self.polygon3[idx_i]
                else:
                    self.polygon3[idx_i] = True
                if idx_o in self.polygon3:
                    assert not self.polygon3[idx_o]
                else:
                    self.polygon3[idx_o] = False

    def print_v_list(self):
        print(len(self.v_list))
        for v in self.v_list:
            print(','.join(str(x) for x in v))

    def print_polygon2(self):
        res = []
        for idx, v in enumerate(self.polygon2):
            if idx in self.polygon3:
                if self.polygon3[idx]:
                    res.append(' '.join(str(x) for x in v))
            else:
                res.append('??? ' + ' '.join(str(x) for x in v))
        print(len(res))
        for x in res:
            print(x)

hoge = Hoge(v_set)
for x in polygons:
    for i in range(len(x)):
        hoge.add_segment(x[i], x[(i + 1) % len(x)])
for x in segments:
    hoge.add_segment(x[0], x[1])
hoge.build(polygons)
hoge.print_v_list()
hoge.print_polygon2()
