
import os
import zipfile
import shutil
from pathlib import Path
from PIL import Image, ImageDraw, ImageFont
import io
import logging

LOG = logging.getLogger(__name__)



def find_assets_dir() -> Path:
    # 1) env var override
    env = os.environ.get("SEAT_ASSETS_DIR") or os.environ.get("SEAT_ASSETS")
    if env:
        p = Path(env).expanduser()
        return p

    # 2) search sensible locations
    module_dir = Path(__file__).resolve().parent            # modules/
    project_root = module_dir.parent                        # project root
    candidates = [
        module_dir / "assets",        # modules/assets
        project_root / "assets",      # project_root/assets
        Path.cwd() / "assets",        # cwd/assets
    ]
    for cand in candidates:
        if cand.exists() and cand.is_dir():
            return cand

    # default to project_root/assets (we'll create it later if needed)
    return project_root / "assets"


MODULE_ROOT = Path(__file__).resolve().parent
ASSETS_DIR = find_assets_dir()
PLACEHOLDER = ASSETS_DIR / "nopic.jpg"

# DEBUG PRINTS
print("DEBUG → ASSETS_DIR =", ASSETS_DIR)
print("DEBUG → PLACEHOLDER =", PLACEHOLDER)
print("DEBUG → PLACEHOLDER exists:", PLACEHOLDER.exists())

def ensure_assets_placeholder():

    ASSETS_DIR.mkdir(parents=True, exist_ok=True)
    if PLACEHOLDER.exists():
        return str(PLACEHOLDER)

    try:
        img = Image.new("RGB", (400, 400), color=(245, 245, 245))
        draw = ImageDraw.Draw(img)
        try:
            fnt = ImageFont.load_default()
        except Exception:
            fnt = None
        text = "No Image Available"
        # Use textbbox for Pillow >=10
        try:
            bbox = draw.textbbox((0, 0), text, font=fnt)
            w = bbox[2] - bbox[0]
            h = bbox[3] - bbox[1]
        except Exception:
            # fallback
            w, h = draw.textsize(text, font=fnt) if hasattr(draw, "textsize") else (120, 14)
        draw.text(((400 - w) / 2, (400 - h) / 2), text, fill=(90, 90, 90), font=fnt)
        img.save(PLACEHOLDER, format="JPEG", quality=85)
        LOG.info("Created placeholder image at %s", PLACEHOLDER)
    except Exception:
        # If PIL operations fail, ensure an empty file exists so other code can reference it
        try:
            with open(PLACEHOLDER, "wb") as f:
                f.write(b"")
            LOG.warning("Created empty placeholder file at %s", PLACEHOLDER)
        except Exception:
            LOG.exception("Failed to create placeholder image; please create %s manually.", PLACEHOLDER)
    return str(PLACEHOLDER)


def safe_extract_photos_zip(uploaded_zip_file, dest_dir):
    """
    Extract a Streamlit UploadedFile (or file-like) safely into dest_dir.
    Flattens nested directories and avoids zip-slip.
    """
    Path(dest_dir).mkdir(parents=True, exist_ok=True)
    # read bytes
    if hasattr(uploaded_zip_file, "read"):
        data = uploaded_zip_file.read()
        bio = io.BytesIO(data)
    elif isinstance(uploaded_zip_file, (bytes, bytearray)):
        bio = io.BytesIO(uploaded_zip_file)
    else:
        bio = None

    if bio is None:
        # treat uploaded_zip_file as path
        with zipfile.ZipFile(uploaded_zip_file) as z:
            for member in z.namelist():
                p = Path(member)
                if p.is_absolute() or ".." in p.parts or member.endswith("/"):
                    continue
                outp = Path(dest_dir) / p.name
                with z.open(member) as src, open(outp, "wb") as dst:
                    shutil.copyfileobj(src, dst)
        return

    with zipfile.ZipFile(bio) as z:
        for member in z.namelist():
            p = Path(member)
            if p.is_absolute() or ".." in p.parts or member.endswith("/"):
                continue
            outp = Path(dest_dir) / p.name
            try:
                with z.open(member) as src, open(outp, "wb") as dst:
                    shutil.copyfileobj(src, dst)
            except RuntimeError:
                LOG.exception("Skipping member %s", member)


def setup_output_dir(tmpdir: str) -> str:
    out = Path(tmpdir) / "Output_Zip"
    out.mkdir(parents=True, exist_ok=True)
    return str(out)


def create_final_zip(output_root: str, output_name: str) -> str:
    out_root = Path(output_root)
    out_zip_path = out_root.parent / f"{output_name}.zip"
    shutil.make_archive(str(out_zip_path.with_suffix("")), 'zip', str(out_root))
    return str(out_zip_path)



# --- replace the get_photo_for_roll function's fallback logic with this ---
def get_photo_for_roll(photos_dir: str, roll: str):
    # If caller supplied photos_dir and it is non-empty, use it.
    photos_path = None
    if photos_dir:
        photos_path = Path(photos_dir)

    # If not supplied or doesn't exist, try project-level photos folder (project_root/photos)
    if photos_path is None or not photos_path.exists():
        project_root = Path(__file__).resolve().parent.parent
        candidate = project_root / "photos"
        if candidate.exists():
            photos_path = candidate

    # finally, fallback to current directory
    if photos_path is None or not photos_path.exists():
        photos_path = Path(".")

    # ensure assets placeholder is available (this will create ASSETS_DIR if necessary)
    placeholder = ensure_assets_placeholder()

    base = (str(roll) or "").strip()
    if not base:
        return placeholder

    # direct candidates
    for ext in ("jpg", "jpeg", "png"):
        p = photos_path / f"{base}.{ext}"
        if p.exists():
            return str(p)
        p_up = photos_path / f"{base}.{ext.upper()}"
        if p_up.exists():
            return str(p_up)

    # normalized search through photos_path
    try:
        norm = base.replace(" ", "").replace(".", "").lower()
        for p in photos_path.glob("*"):
            if p.is_file() and p.suffix.lower() in {".jpg", ".jpeg", ".png"}:
                stem = p.stem.lower()
                if norm == stem or base.lower() == stem or base.lower() in p.name.lower():
                    return str(p)
    except Exception:
        LOG.exception("Error scanning photos_dir %s", photos_path)

    # final fallback to placeholder
    return placeholder
