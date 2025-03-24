from keras.src.legacy.preprocessing.image import ImageDataGenerator
from keras.src.saving import load_model
import tensorflow as tf

tf.config.run_functions_eagerly(True)

# Load the saved model (if it was built in another file)
model = load_model("models/skin_lesion_classifier.h5")

model.compile(optimizer="adam", loss="categorical_crossentropy", metrics=["accuracy"])

# Reload the data for training
train_datagen = ImageDataGenerator(validation_split=0.2)

train_generator = train_datagen.flow_from_directory(
    "dataset/processed_images/output/",
    target_size=(224, 224),
    batch_size=32,
    class_mode="categorical",
    subset="training"
)

val_generator = train_datagen.flow_from_directory(
    "dataset/processed_images/output/",
    target_size=(224, 224),
    batch_size=32,
    class_mode="categorical",
    subset="validation"
)

# Train the model
history = model.fit(
    train_generator,
    validation_data=val_generator,
    epochs=50,
    verbose=1
)

print("✔ Training completed!")

# Save the model again after training
model.save("models/skin_lesion_classifier_trained.h5")
