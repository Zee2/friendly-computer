from PIL import Image
import sys

if(len(sys.argv) == 1):
    print("Please supply a filename")
    quit()

img = Image.open(sys.argv[1]).convert(mode="RGB")

width, height = img.size

sheetname = sys.argv[1].split(".")[0]

print("Image format: ", end="")
print(img.format)
print(img.size)
print(img.mode)

outputfile = open(sheetname + ".c", "w")

charPositions = []

outputfile.write("const uint8_t " + sheetname + "[] = {\n")

for y in range(height):
    outputfile.write("    ")
    for x in range(width):

        if(y == 0):
            if(img.getpixel((x,y))[2] > img.getpixel((x,y))[0]):
                charPositions.append(x)
                print("Red value: " + str(img.getpixel((x,y))[0]))


        if(img.getpixel((x,y))[0] > 127 or img.getpixel((x,y))[2] > img.getpixel((x,y))[0]):
            pixelval = 255
        else:
            pixelval = 0
        pixelstring = "0x" + format(pixelval, '02x')
        outputfile.write(pixelstring + ", ")
    outputfile.write("\n")

outputfile.write("};\n\n")

outputfile.write("const uint16_t " + sheetname + "_charpos[] = {\n    ")
for pos in charPositions:
    outputfile.write(str(pos) + ", ")
outputfile.write("\n};\n")
print(charPositions)