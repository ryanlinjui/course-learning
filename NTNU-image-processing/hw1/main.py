import numpy as np
import matplotlib.pyplot as plt

# Configure the image filepath
IMAGE_DIR = "./assets/"
SAMPLE_IMAGE = f"{IMAGE_DIR}sample.jpg"
RGB_IMAGE = f"{IMAGE_DIR}rgb.jpg"
GRAY_IMAGE = f"{IMAGE_DIR}gray.jpg"
MATLAB_GRAY_IMAGE = f"{IMAGE_DIR}matlab_gray.jpg"
GRAY_WITHOUTCMAP_IMAGE = f"{IMAGE_DIR}gray_without_cmap.jpg"

# Read the original RGB image
rgb_img = plt.imread(SAMPLE_IMAGE)

# Convert the RGB image to grayscale
gray_img = np.dot(rgb_img[..., :3], [0.3, 0.3, 0.3])

# Convert the RGB image to grayscale by Matlab method
matlab_gray_img = np.dot(rgb_img[..., :3], [0.2989, 0.5870, 0.1140])

# Save image
plt.imsave(RGB_IMAGE, rgb_img)

# Save image with cmap
plt.imsave(GRAY_IMAGE, gray_img, cmap="gray")

# Save image with cmap
plt.imsave(MATLAB_GRAY_IMAGE, matlab_gray_img, cmap="gray")

# Save image without cmap
plt.imsave(GRAY_WITHOUTCMAP_IMAGE, gray_img)