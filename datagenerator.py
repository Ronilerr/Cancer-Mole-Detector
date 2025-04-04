import sys
import os
import Augmentor

# path of the main directory 
BASE_DIR = os.path.dirname(os.path.abspath("/Users/asaframati/Documents/Reichman/IOT/isicChallenge"))
# Add the isic-2019 directory to Python's search path
sys.path.append(os.path.join(BASE_DIR, "isic-2019"))

# Create an Augmentor Pipeline for your images
pipeline = Augmentor.Pipeline("dataset/processed_images")  # Path to your images

num_images = len([f for f in os.listdir("dataset/processed_images") if f.endswith((".jpg"))])

# Add transformations to the Augmentor pipeline
pipeline.rotate(probability=0.7, max_left_rotation=10, max_right_rotation=10)  # Slight rotation
pipeline.flip_left_right(probability=0.5)  # Horizontal flip
pipeline.zoom(probability=0.5, min_factor=1.1, max_factor=1.3)  # Random zoom
pipeline.random_brightness(probability=0.5, min_factor=0.7, max_factor=1.3)  # Brightness variation

# Run the augmentation to generate 1000 new images
pipeline.sample(num_images * 2)
print("done")
