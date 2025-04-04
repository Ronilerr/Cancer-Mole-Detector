import numpy as np
import tensorflow as tf
import json
import os
from keras.src.utils import load_img, img_to_array
import sys

# Load the trained model
model_path = "models/skin_lesion_classifier.h5"
model = tf.keras.models.load_model(model_path)

# Define class labels
class_labels = ['malignant', 'benign', 'unknown']

# JSON file path
json_file_path = "predictions.json"

def preprocess_image(image_path):
    """Load and preprocess an image."""
    img = load_img(image_path, target_size=(224, 224))  # Resize to match model input
    img_array = img_to_array(img) / 255.0  # Normalize pixel values
    img_array = np.expand_dims(img_array, axis=0)  # Add batch dimension
    return img_array

def save_to_json(image_path, predicted_class, prediction_probs):
    """Overwrite prediction results in a JSON file."""
    result = {
        "data": [  # Ensure it's wrapped inside "data" key
            {
                "image_path": image_path,
                "predicted class": predicted_class,
                "prediction": prediction_probs.tolist()  # Convert to list for JSON serialization
            }
        ]
    }
    
    # **Overwrite the JSON file**
    with open(json_file_path, "w") as f:
        json.dump(result, f, indent=4)

def predict(image_path):
    """Run model prediction on an image and save results."""
    img_array = preprocess_image(image_path)
    prediction = model.predict(img_array)
    predicted_class = class_labels[np.argmax(prediction)]  # Get the class label
    
    print(f"Predicted Class: {predicted_class}")
    
    # Save prediction to JSON (overwrite previous content)
    save_to_json(image_path, predicted_class, prediction)

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python run_model.py <image_path>")
    else:
        image_path = sys.argv[1]
        predict(image_path)
