import cv2
import numpy as np
import matplotlib.pyplot as plt

L = 255

def SSIM(A: np.ndarray, B: np.ndarray, c1: float, c2: float) -> float:
    """
    Compute the Structural Similarity Index (SSIM) between two images.
    
    Parameters:
        A (np.ndarray): First grayscale image.
        B (np.ndarray): Second grayscale image.
        c1 (float): Constant to stabilize the division with weak denominator.
        c2 (float): Constant to stabilize the division with weak denominator.
        
    Returns:
        float: SSIM value.
    """
    mu_x = np.mean(A)
    mu_y = np.mean(B)
    sigma_x_pow = np.mean((A - mu_x) ** 2)
    sigma_y_pow = np.mean((B - mu_y) ** 2)
    sigma_xy = np.mean((A - mu_x) * (B - mu_y))
    
    return (
        (2 * mu_x * mu_y + (c1 * L) ** 2) * (2 * sigma_xy + (c2 * L) ** 2)) / \
        ((mu_x ** 2 + mu_y ** 2 + (c1 * L) ** 2) * (sigma_x_pow + sigma_y_pow + (c2 * L) ** 2)
    )

def main():
    A_path = input("Enter the path of the image A: ")
    B_path = input("Enter the path of the image B: ")

    # Read the images in grayscale
    A = cv2.imread(A_path, cv2.IMREAD_GRAYSCALE)
    B = cv2.imread(B_path, cv2.IMREAD_GRAYSCALE)
    
    if A is None or B is None:
        print("Error: One of the image paths is incorrect.")
        return
    
    # Constants for SSIM computation
    c1 = 1 / (L ** 0.5)
    c2 = 1 / (L ** 0.5)

    # Compute SSIM
    ssim = SSIM(A, B, c1, c2)

    # Display the images and SSIM value
    plt.figure(figsize=(10, 5))

    plt.subplot(1, 2, 1)
    plt.imshow(A, cmap="gray")
    plt.title("Image A")

    plt.subplot(1, 2, 2)
    plt.imshow(B, cmap="gray")
    plt.title("Image B")

    plt.suptitle(f"SSIM: {ssim:.4f}")
    plt.show()

if __name__ == "__main__":
    main()