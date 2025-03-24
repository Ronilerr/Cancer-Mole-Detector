import cv2
import os

# Path to the image folder
input_folder = "./dataset/images"
output_folder = "./dataset/processed_images"

# Create a new folder for processed images
os.makedirs(output_folder, exist_ok=True)

# Loop through all images in the folder
for filename in os.listdir(input_folder):
    if filename.endswith(".jpg"):
        img_path = os.path.join(input_folder, filename)
        img = cv2.imread(img_path)

        # Resize the image to 224x224
        img_resized = cv2.resize(img, (224, 224))

        # Save the processed image
        output_path = os.path.join(output_folder, filename)
        cv2.imwrite(output_path, img_resized)

print(img_resized)
