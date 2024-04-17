import cv2
import numpy as np
import matplotlib.pyplot as plt

# Configure the image filepath
SAMPLE_img = "./assets/input/C.jpg"
GRAYSCALE_G = "./assets/output/G.jpg"
GRAYSCALE_G_PLOT = "./assets/output/G-plot.jpg"
HE_G2 = "./assets/output/G2.jpg"
HE_G2_PLOT = "./assets/output/G2-plot.jpg"
OUTPUT_C1 = "./assets/output/C1.jpg"
OUTPUT_C2 = "./assets/output/C2.jpg"

def modify(img, g2_img, g_img, is_type2=False):
    b, g, r = cv2.split(img)

    if is_type2:
        # Equation to modify color intensity
        r_adjusted = r * (g2_img / g_img)
        g_adjusted = g * (g2_img / g_img)
        b_adjusted = b * (g2_img / g_img)
    else:
        # Using OpenCV's functions for element-wise multiplication and division
        r_adjusted = cv2.multiply(r, cv2.divide(g2_img, g_img))
        g_adjusted = cv2.multiply(g, cv2.divide(g2_img, g_img))
        b_adjusted = cv2.multiply(b, cv2.divide(g2_img, g_img))

    # Merge the adjusted color channels to form the modified image
    modify_img = cv2.merge([b_adjusted, g_adjusted, r_adjusted])
    return modify_img

def histogram_equalization(img):
    # Calculate the histogram and cumulative distribution function (CDF)
    histogram, bins = np.histogram(img.flatten(), 256, [0, 255])
    cdf = histogram.cumsum()
    cdf_normalized = cdf / cdf[-1]

    # Apply histogram equalization
    return (cdf_normalized[img] * 255).astype(np.uint8)

def main():
    
    # Read sample RGB image
    img = cv2.imread(SAMPLE_img)

    # Grayscale processing
    gray_img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    cv2.imwrite(GRAYSCALE_G, gray_img)

    # Plot and save histogram for grayscale image
    plt.hist(gray_img.ravel(), 256, [0, 255], label="GRAYSCALE G image")
    plt.legend()
    plt.savefig(GRAYSCALE_G_PLOT)
    plt.clf()

    # Histogram equalization processing
    equalize_img = histogram_equalization(gray_img)
    cv2.imwrite(HE_G2, equalize_img)

    # Plot and save histogram for histogram equalized image
    plt.hist(equalize_img.ravel(), 256, [0, 255], label="HE G' image")
    plt.legend()
    plt.savefig(HE_G2_PLOT)

    # Modify its color (r,g,b) by (r’,g’,b’) = (r,g,b) X G’ / G and save image
    modify1_img = modify(img, equalize_img, gray_img)
    modify2_img = modify(img, equalize_img, gray_img, is_type2=True)
    cv2.imwrite(OUTPUT_C1, modify1_img)
    cv2.imwrite(OUTPUT_C2, modify2_img)

if __name__ == "__main__":
    main()
