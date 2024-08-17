from PIL import Image, ImageDraw

RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLUE = (0, 0, 255)
YELLOW = (255, 255, 0)
MAGENTA = (255, 0, 255)
CYAN = (0, 255, 255)

MAPPINGS = {
    "+": RED,
    "-": YELLOW,
    "<": BLUE,
    ">": CYAN,
    "[": GREEN,
    "]": MAGENTA
}

PAPER_WIDTH = 500
BLOCK_WIDTH = 400
BLOCK_START = (PAPER_WIDTH - BLOCK_WIDTH) // 2 # x
BLOCK_END = PAPER_WIDTH - BLOCK_START # x
BLOCK_HEIGHT = 50

# TODO: this doesn't work properly if there's any invalid characters
code = input()
paper_height = (len(code) * 2 + 1) * BLOCK_HEIGHT

# Create a new image
image = Image.new("RGB", (PAPER_WIDTH, paper_height), "white")
draw = ImageDraw.Draw(image)

for i, c in enumerate(code):
    if c in MAPPINGS:
        y_start = BLOCK_HEIGHT * (2 * i + 1)
        draw.rectangle((BLOCK_START, y_start, BLOCK_END, y_start + BLOCK_HEIGHT), MAPPINGS[c])
    

# Show the image
image.show()
