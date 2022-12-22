# Author:       Dawid Kwapisz (dkwapisz99@gmail.com, dkwapisz@student.agh.edu.pl)
# License:      GPLv3

from PIL import Image

image = Image.open("map3.png")
image_out = image.convert("RGB")

map_txt = open("map3.txt", "a")

# Clear file before writing
map_txt.seek(0)
map_txt.truncate()

for y in range(image_out.width):
    for x in range(image_out.height):
        if image_out.getpixel((x, y)) == (0, 0, 0):  # Wall
            map_txt.write("1 ")
        elif image_out.getpixel((x, y)) == (255, 255, 255):  # Floor
            map_txt.write("0 ")
        elif image_out.getpixel((x, y)) == (50, 0, 0):  # Box
            map_txt.write("2 ")
        elif image_out.getpixel((x, y)) == (170, 0, 150):  # StaticDanger
            map_txt.write("3 ")
        elif image_out.getpixel((x, y)) == (255, 255, 0):  # Coin
            map_txt.write("4 ")
        elif image_out.getpixel((x, y)) == (255, 0, 0):  # MovingDangerH
            map_txt.write("5 ")
        elif image_out.getpixel((x, y)) == (120, 0, 0):  # MovingDangerV
            map_txt.write("6 ")
        elif image_out.getpixel((x, y)) == (80, 120, 0):  # Finish
            map_txt.write("7 ")
        elif image_out.getpixel((x, y)) == (0, 255, 0):  # Player
            map_txt.write("9 ")
    map_txt.write("\n")

image.close()
map_txt.close()

print("Map correctly converted from PNG to TXT \n")

