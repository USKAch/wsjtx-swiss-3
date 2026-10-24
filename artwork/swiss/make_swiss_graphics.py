"""Generate the WSJT-SWISS 3 graphics from the plain WSJT globe.

Writes, relative to the repository root:
  icons/windows-icons/wsjtx.ico          program, window and installer icon
  icons/Darwin/wsjtx.iconset/icon_128x128.png   splash and About dialog icon
  icons/windows-icons/installer_logo.bmp NSIS installer header (150x57)
  artwork/splash.png                     splash screen background (570x472)

Run from the repository root on Windows (uses Arial from C:\\Windows\\Fonts):
  python artwork/swiss/make_swiss_graphics.py
"""

from pathlib import Path

from PIL import Image, ImageDraw, ImageFont

ROOT = Path(__file__).resolve().parents[2]
GLOBE = ROOT / "icons/Darwin/wsjt.iconset/icon_512x512@2x.png"
FONTS = Path("C:/Windows/Fonts")

SWISS_RED = (218, 41, 28)
WHITE = (255, 255, 255)
CANTONS = ("AG AI AR BE BL BS FR GE GL GR JU LU NE "
           "NW OW SG SH SO SZ TG TI UR VD VS ZG ZH")


def font(name, size):
    return ImageFont.truetype(str(FONTS / name), size)


def swiss_flag(size, border=0):
    """Square Swiss flag: 32-unit field, 6-unit arms of 20-unit length."""
    flag = Image.new("RGBA", (size, size), WHITE + (255,))
    d = ImageDraw.Draw(flag)
    d.rectangle((border, border, size - 1 - border, size - 1 - border),
                fill=SWISS_RED)
    inner = size - 2 * border
    u = inner / 32.0
    o = border
    d.rectangle((o + 13 * u, o + 6 * u, o + 19 * u, o + 26 * u), fill=WHITE)
    d.rectangle((o + 6 * u, o + 13 * u, o + 26 * u, o + 19 * u), fill=WHITE)
    return flag


def globe(size):
    g = Image.open(GLOBE).convert("RGBA")
    g = g.crop(g.getbbox())
    side = max(g.size)
    square = Image.new("RGBA", (side, side), (0, 0, 0, 0))
    square.paste(g, ((side - g.width) // 2, (side - g.height) // 2))
    return square.resize((size, size), Image.LANCZOS)


def icon(size):
    """Globe with a Swiss flag badge, bottom right; bigger badge when small."""
    work = 1024
    img = Image.new("RGBA", (work, work), (0, 0, 0, 0))
    img.alpha_composite(globe(int(work * 0.94)), (int(work * 0.03),) * 2)
    ratio = 0.58 if size <= 32 else 0.46
    badge = int(work * ratio)
    flag = swiss_flag(badge, border=max(int(badge * 0.06), 1))
    img.alpha_composite(flag, (work - badge, work - badge))
    return img.resize((size, size), Image.LANCZOS)


def write_ico():
    sizes = [16, 20, 24, 32, 40, 48, 64, 96, 128, 256]
    frames = [icon(s) for s in sizes]
    frames[-1].save(ROOT / "icons/windows-icons/wsjtx.ico", format="ICO",
                    sizes=[(s, s) for s in sizes], append_images=frames[:-1])
    icon(128).save(ROOT / "icons/Darwin/wsjtx.iconset/icon_128x128.png")


def write_installer_logo():
    img = Image.new("RGB", (150, 57), WHITE)
    img.paste(swiss_flag(37).convert("RGB"), (5, 10))
    d = ImageDraw.Draw(img)
    d.text((49, 11), "WSJT-SWISS 3", font=font("arialbd.ttf", 13),
           fill=(30, 30, 30))
    d.text((49, 31), "Swiss XMAS Contest", font=font("arial.ttf", 10),
           fill=(110, 110, 110))
    img.save(ROOT / "icons/windows-icons/installer_logo.bmp")


def write_splash():
    w, h = 570, 472
    # widgets/SplashScreen.cpp keeps its check box above the bottom strip
    top, bottom = 58, 34
    img = Image.new("RGB", (w, h), WHITE)
    d = ImageDraw.Draw(img)

    # Pale body with a faint cross watermark behind the splash text.
    for y in range(top, h - bottom):
        shade = 252 - int(6 * (y - top) / (h - top - bottom))
        d.line((0, y, w, y), fill=(shade, shade, shade))
    u = 300 / 32.0
    cx, cy = w // 2, top + (h - top - bottom) // 2
    tint = (250, 232, 230)
    d.rectangle((cx - 3 * u, cy - 10 * u, cx + 3 * u, cy + 10 * u), fill=tint)
    d.rectangle((cx - 10 * u, cy - 3 * u, cx + 10 * u, cy + 3 * u), fill=tint)

    # Red title band with the flag cross and program name.
    d.rectangle((0, 0, w, top), fill=SWISS_RED)
    img.paste(swiss_flag(42, border=2).convert("RGB"), (12, 8))
    d.text((66, 10), "WSJT-SWISS 3", font=font("arialbd.ttf", 30), fill=WHITE)
    sub = "Swiss XMAS Contest"
    sub_font = font("arial.ttf", 15)
    d.text((w - 14 - d.textlength(sub, font=sub_font), 21), sub,
           font=sub_font, fill=WHITE)

    # Canton codes along the bottom.
    d.rectangle((0, h - bottom, w, h), fill=(244, 244, 244))
    d.line((0, h - bottom, w, h - bottom), fill=SWISS_RED, width=2)
    codes = CANTONS.split()
    code_font = font("arialbd.ttf", 10)
    step = (w - 24) / len(codes)
    for i, code in enumerate(codes):
        x = 12 + i * step + (step - d.textlength(code, font=code_font)) / 2
        d.text((x, h - bottom + 10), code, font=code_font, fill=(150, 60, 55))

    img.save(ROOT / "artwork/splash.png")


if __name__ == "__main__":
    write_ico()
    write_installer_logo()
    write_splash()
