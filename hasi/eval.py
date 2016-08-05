import sys
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
    a = (ty * ux + tx * uy) / cross
    b = (- sy * ux - sx * uy) / cross
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
print(v_set)
