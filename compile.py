from PIL import Image, ImageDraw, ImageFont
from sys import stdin
from math import ceil

RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLUE = (0, 0, 255)
YELLOW = (255, 255, 0)
MAGENTA = (255, 0, 255)
CYAN = (0, 255, 255)
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)

NOP = ""
EOF = "END"

MAPPINGS = {
    "+": RED,
    "-": YELLOW,
    "<": BLUE,
    ">": CYAN,
    "[": GREEN,
    "]": MAGENTA,
    NOP: WHITE,
    EOF: BLACK
}

SCALING = 2

A4_WIDTH = 595 * 2
A4_HEIGHT = 842 * 2

TOP_BOT_MARGIN = 20 * SCALING

BLOCK_WIDTH = 400 * SCALING
BLOCK_START = (A4_WIDTH - BLOCK_WIDTH) // 2 # x
BLOCK_END = A4_WIDTH - BLOCK_START # x
BLOCK_HEIGHT = 200 * SCALING
BLOCKS_PER_PAGE = (A4_HEIGHT - 2 * TOP_BOT_MARGIN) // BLOCK_HEIGHT

PAGE_TEXT_COLOUR = "#454c5a"
CODE_TEXT_COLOUR = "#454c5a"

code = [c for c in stdin.read() if c in MAPPINGS]

new_code = [code[0]]
for c1, c2 in zip(code, code[1:]):
    if c1 == c2:
        new_code.append(NOP)
    new_code.append(c2)
code = new_code
code.append(EOF)

pages = ceil(len(code) / BLOCKS_PER_PAGE)

page_font = ImageFont.load_default(size=40 * SCALING)
code_font = ImageFont.load_default(size=60 * SCALING)

i = 0
image_array = []

for page in range(pages):
    # Create a new image
    image = Image.new("RGB", (A4_WIDTH, A4_HEIGHT), "white")
    draw = ImageDraw.Draw(image)

    draw.text((5 * SCALING, 0), str(page), font=page_font, fill=PAGE_TEXT_COLOUR)
    
    for _ in range(BLOCKS_PER_PAGE):
        if i >= len(code):
            break

        c = code[i]
        y_start = BLOCK_HEIGHT * (i % BLOCKS_PER_PAGE) + TOP_BOT_MARGIN
        draw.rectangle((BLOCK_START, y_start, BLOCK_END, y_start + BLOCK_HEIGHT), MAPPINGS[c])

        draw.text((BLOCK_END + (15 * SCALING), y_start - (15 * SCALING)), c, font=code_font, fill=CODE_TEXT_COLOUR)

        i += 1

    image_array.append(image.copy())

image_array[0].save("out.pdf", save_all=True, append_images=image_array[1:])
print("PDF saved in cwd!")
