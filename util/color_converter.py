import sys

# Input on stdin like:
#
#   red = #ff0000
#   black = #000000
#   yellow = #d79921
#
# Gets converted to:
#
#   ColourRGB red(1.0, 0.0, 0.0);
#   ColourRGB black(0.0, 0.0, 0.0);
#   ColourRGB yellow(0.84, 0.6, 0.13);


def convert(name, hex):
    name = name.strip()
    hex = hex.strip()[1:]
    s = ""
    floats = []
    while hex:
        s = hex[0:2]
        hex = hex[2:]
        f = int(s, 16) / 255
        floats.append(f)
    args = "{:.2}, {:.2}, {:.2}".format(*floats)
    return "ColourRGB {}({});".format(name, args)


colors = (l.strip().split('=')
          for l in sys.stdin.readlines())

for color in colors:
    print(convert(*color))
