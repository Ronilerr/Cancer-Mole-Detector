import os
import shutil
import pandas as pd

malignant = ["MEL", "SCC", "BCC"]
benign = ["NV", "BKL", "DF", "VASC", "AK"]

# Path to the folder with images after augmentation
output_dir = "dataset/processed_images/output"

# Path to the CSV file with labels
csv_file = "dataset/diagnoses.csv"  # Update this if needed

# Read the CSV file
df = pd.read_csv(csv_file)

# Create directories for categories if they don't exist
malignant_dir = os.path.join(output_dir, "malignant")
benign_dir = os.path.join(output_dir, "benign")
unknown_dir = os.path.join(output_dir, "unknown")

os.makedirs(malignant_dir, exist_ok=True)
os.makedirs(benign_dir, exist_ok=True)
os.makedirs(unknown_dir, exist_ok=True)

# Get list of all images in the output folder
all_images = os.listdir(output_dir)

# Iterate through each row in the CSV
for index, row in df.iterrows():
    isic_id = row["image"]
    label = row["dx"]

    # Find matching files containing the ISIC ID
    matching_files = [f for f in all_images if isic_id in f]

    # Move matching files to the appropriate folder
    for image_name in matching_files:
        image_path = os.path.join(output_dir, image_name)
        if os.path.exists(image_path):
            if label in malignant:
                shutil.move(image_path, os.path.join(malignant_dir, image_name))
            elif label in benign:
                shutil.move(image_path, os.path.join(benign_dir, image_name))
            else:
                shutil.move(image_path, os.path.join(unknown_dir, image_name))
