
# Skin Lesion Classification using Deep Learning

This project classifies skin lesions into three categories:
- **malignant**
- **benign**
- **unknown**

It uses transfer learning with **MobileNetV2** and data augmentation techniques
to improve performance on dermoscopic images from the ISIC 2019 dataset.

---

## Project Overview

- **Dataset**: ISIC 2019 dermoscopic images  
- **Preprocessing**: All images resized to 224x224  
- **Augmentation**: Performed using `Augmentor` (rotation, flip, zoom, brightness)  
- **Model**: MobileNetV2 with custom dense layers  
- **Training**: Using `ImageDataGenerator` with 80/20 train-validation split  
- **Output**: Trained Keras model saved as `.h5` file  

---

## Folder Structure

```
dataset/
├── images/                      # Original images
├── processed_images/           # Resized images
│   └── output/
│       ├── malignant/
│       ├── benign/
│       └── unknown/
├── diagnoses.csv               # CSV file containing image IDs and labels

models/
├── skin_lesion_classifier.h5           # Base model before training
├── skin_lesion_classifier_trained.h5   # Final model after training
```

---

## Main Steps

1. **Preprocess Images**  
   Resize all images to 224x224 using OpenCV.

2. **Augment Dataset**  
   Use `Augmentor` to create variations of images with transformations.

3. **Organize Dataset**  
   Move images into `malignant`, `benign`, or `unknown` folders based on the CSV.

4. **Build Model**  
   Load MobileNetV2 without top layers.  
   Add Dense, Dropout, and Softmax output layer for 3 classes.

5. **Train the Model**  
   Use `ImageDataGenerator` to load and train with validation split.  
   Save the trained model to the `models` folder.

---

## Requirements

Install the required libraries before running the scripts:

```bash
pip install tensorflow keras opencv-python pandas Augmentor
```

---

## Future Improvements

- Add model evaluation metrics (confusion matrix, F1-score)
- Enable fine-tuning of base MobileNetV2 layers
- Create a web interface for real-time predictions
- Use a larger dataset to improve generalization

---

## Important Notes

- Ensure the `diagnoses.csv` file has at least two columns: `image` and `dx`
- File names of images should match the `image` field in the CSV
- Run preprocessing, augmentation, and sorting scripts before training

---

## License

This project is intended for educational and research use.  
If using ISIC data, please follow the dataset's usage guidelines.
