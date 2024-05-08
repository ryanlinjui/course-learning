import cv2
import numpy as np

# Paths for the image files
SAMPLE_IMG = "./assets/input/sample.jpg"
RESULT_3X3 = "./assets/output/result-3x3.jpg"
RESULT_4X4 = "./assets/output/result-4x4.jpg"

def skeletonize(img: np.ndarray, kernel_size: tuple) -> np.ndarray:

    # Lantuéjoul's method suggests a cross-like structuring element
    kernel = cv2.getStructuringElement(cv2.MORPH_CROSS, kernel_size)

    size = np.size(img)
    skeleton = np.zeros(img.shape, np.uint8)
    
    while True:
        
        # Erosion
        eroded = cv2.erode(img, kernel)
        # Opening
        opening = cv2.morphologyEx(eroded, cv2.MORPH_OPEN, kernel)
        # Subtraction
        tmp = cv2.subtract(eroded, opening)
        # Union of skeletons
        skeleton = cv2.bitwise_or(skeleton, tmp)
        # Update img for next iteration
        img = eroded.copy()
        
        # If no more changes, break the loop
        if cv2.countNonZero(img) == 0:
            break

    return skeleton


def main():

    # Load the image in grayscale
    img = cv2.imread(SAMPLE_IMG, 0)
    threshold_img = cv2.threshold(img, 127, 255, cv2.THRESH_BINARY)[1]

    # Apply the skeletonization method
    skeleton_3x3 = skeletonize(threshold_img, (3, 3))
    skeleton_4x4 = skeletonize(threshold_img, (4, 4))

    # Save the results    
    cv2.imwrite(RESULT_3X3, skeleton_3x3)
    cv2.imwrite(RESULT_4X4, skeleton_4x4)

if __name__ == "__main__":
    main()