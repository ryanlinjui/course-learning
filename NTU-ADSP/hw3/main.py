import numpy as np
from PIL import Image
import matplotlib.pyplot as plt
import os, io

def subsample_420(channel: np.ndarray) -> np.ndarray:
    """Subsample the chrominance channels by a factor of 2 in both axes."""
    return channel[::2, ::2]

def upsample_420(channel: np.ndarray) -> np.ndarray:
    """Upsample the chrominance channels by a factor of 2 using bilinear interpolation."""
    return channel.repeat(2, axis=0).repeat(2, axis=1)

def compress_420(img: Image) -> Image:
    """Compress an RGB image using the 4:2:0 compression scheme."""
    
    # Convert RGB to YCbCr
    ycbcr_img = img.convert("YCbCr")
    np_ycbcr = np.array(ycbcr_img)

    # Split into separate channels
    Y = np_ycbcr[:, :, 0]
    Cb = np_ycbcr[:, :, 1]
    Cr = np_ycbcr[:, :, 2]

    # Subsample Cb and Cr channels
    Cb_sub = subsample_420(Cb)
    Cr_sub = subsample_420(Cr)

    # Upsample Cb and Cr channels
    Cb_upsampled = upsample_420(Cb_sub)
    Cr_upsampled = upsample_420(Cr_sub)

    # Reconstruct YCbCr image with original Y and upsampled Cb, Cr
    reconstructed_ycbcr = np.stack((Y, Cb_upsampled, Cr_upsampled), axis=-1).astype(np.uint8)
    reconstructed_img = Image.fromarray(reconstructed_ycbcr, "YCbCr")

    # Convert back to RGB
    return reconstructed_img.convert("RGB")

def main():
    
    # Load the input image
    img_path = input("Enter the path of the image: ")
    A_input_color_img = Image.open(img_path)
    A_input_color_img_size = os.path.getsize(img_path)

    # Apply the 4:2:0 compression technique
    B_reconstructed_img = compress_420(A_input_color_img)

    # Save the reconstructed image to a byte buffer instead of disk
    buffer = io.BytesIO()
    B_reconstructed_img.save(buffer, format='JPEG')
    B_reconstructed_img_size = buffer.tell()
    B_reconstructed_img.save("reconstructed.jpg")

    # Display the original and reconstructed images and information
    fig, ax = plt.subplots(1, 2)
    ax[0].imshow(A_input_color_img)
    ax[0].set_title("Original Image")
    ax[1].imshow(B_reconstructed_img)
    ax[1].set_title("Reconstructed Image")
    ax[0].text(0, -130, f"Size: {A_input_color_img.size}")
    ax[1].text(0, -130, f"Size: {B_reconstructed_img.size}")
    ax[0].text(0, -100, f"File size (in bytes): {A_input_color_img_size}")
    ax[1].text(0, -100, f"File size (in bytes): {B_reconstructed_img_size}")
    plt.show()

if __name__ == "__main__":
    main()