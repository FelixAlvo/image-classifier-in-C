# 🧠 Image Classifier in C

This is a from-scratch image classification project written in C. The initial goal is to distinguish between grayscale images (e.g., cats vs. dogs), but the architecture is designed to be modular and extensible — allowing you to easily switch to different kinds of classification tasks (e.g., digits, logos) with minimal code changes.

---

## 🎯 Goals

- Learn and implement fundamental machine learning algorithms in C  
- Build a clean and understandable image classifier  
- Keep all parts of the code modular and reusable  
- Avoid unnecessary dependencies  

---

## 📁 Project Structure

image-classifier-in-C/
├── src/ # All source code (.c)
├── include/ # Header files (.h)
├── images/ # Input data (.pgm format)
├── Makefile # Build instructions
├── README.md # Project documentation
└── .gitignore # Ignore compiled files and temp output


---

## 🖼 Image Format

This project uses **ASCII `.pgm` (P2)** grayscale images.

### Requirements:
- All images must be the same dimensions
- Format must start with `P2`, followed by width, height, max grayscale value, and then pixel values
- Example filename format: `cat_01.pgm`, `dog_02.pgm`

---

## ⚙️ How to Build & Run

```bash
make
./classifier train    # For training (not implemented yet)
./classifier test     # For testing (not implemented yet)