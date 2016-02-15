import sys
import argparse

from PIL import Image

def to_mist32_bitmap(pixels):
    for p in pixels:
        pixel = (p[2] >> 3) & 0x1f
        pixel |= ((p[1] >> 2) & 0x3f) << 5
        pixel |= ((p[0] >> 3) & 0x1f) << 11
        pixel &= 0xffff
        yield pixel >> 8
        yield pixel & 0xff

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("images", metavar='image', type=str, nargs="+")
    parser.add_argument("-o", dest="out", metavar="file", type=str, default="mmc.img")
    args = parser.parse_args()

    mmc = open(args.out, "wb")

    for imgfile in args.images:
        print("Processing...\t%s" % imgfile)
        with Image.open(imgfile) as img:
            if img.size != (640, 480):
                img = img.resize((640, 480))

            mmc.write(bytearray(to_mist32_bitmap(img.getdata())))
    mmc.close()
