from keras.src.applications.mobilenet_v2 import MobileNetV2
from keras.src.layers import Dense, Flatten, Dropout
from keras.src.models import Model
import os

# Load MobileNetV2 without the top layers
base_model = MobileNetV2(input_shape=(224, 224, 3), include_top=False, weights="imagenet")

# Add custom layers for 3 categories
x = Flatten()(base_model.output)
x = Dense(128, activation="relu")(x)
x = Dropout(0.3)(x)  # Dropout to prevent overfitting
x = Dense(3, activation="softmax")(x)  # Three categories: malignant, benign, unknown

# Build the final model
model = Model(inputs=base_model.input, outputs=x)

# Freeze the base MobileNetV2 layers to prevent retraining
for layer in base_model.layers:
    layer.trainable = False

# Compile the model
model.compile(optimizer="adam", loss="categorical_crossentropy", metrics=["accuracy"])

# Create the models folder if it doesn't exist
if not os.path.exists("models"):
    os.makedirs("models")

# Save the model
model.save("models/skin_lesion_classifier.h5")
