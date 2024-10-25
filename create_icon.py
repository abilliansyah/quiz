# create_icon.py
from PIL import Image, ImageDraw, ImageFont

# Buat gambar 256x256
size = 256
img = Image.new('RGBA', (size, size), (255, 255, 255, 0))
draw = ImageDraw.Draw(img)

# Gambar lingkaran
margin = 20
draw.ellipse([margin, margin, size-margin, size-margin], 
             fill='#4CAF50', outline='#388E3C', width=8)

# Tambah teks "Q"
try:
    font = ImageFont.truetype("arial.ttf", 144)
except:
    font = ImageFont.load_default()
    
draw.text((size//3, size//4), "Q", fill='white', font=font)

# Simpan sebagai ICO
img.save('resources/icon.ico', format='ICO')