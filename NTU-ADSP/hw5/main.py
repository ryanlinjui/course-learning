import numpy as np

def fftreal(f1: np.ndarray, f2: np.ndarray) -> tuple:
    
    # Step 1: f3[n] = f1[n] + jf2[n]
    f3 = f1 + 1j * f2

    # Step 2: F3[m] = DFT{f3[n]}
    F3 = np.fft.fft(f3)

    # Step 3
    # F1[m] = (F3[m] + F3^*[N-m]) / 2
    # F2[m] = (F3[m] - F3^*[N-m]) / (2j)
    N = len(f1)
    F3_conj_reverse = np.conj(F3[::-1])
    F3_conj_shifted = np.roll(F3_conj_reverse, 1)
    F1 = (F3 + F3_conj_shifted) / 2
    F2 = (F3 - F3_conj_shifted) / (2 * 1j)
    
    return F1, F2

def main():
    print("")

    # Generate random floating-point numbers between -100 and 100
    print("================ Randomly generated x, y ================")
    x = np.random.uniform(-100, 100, 8)
    y = np.random.uniform(-100, 100, 8)
    print("x:", x)
    print("y:", y)
    print("")

    # Apply twice DFT for each x and y
    Fx_direct = np.fft.fft(x)
    Fy_direct = np.fft.fft(y)
    print("================ Direct Algorithm ================")
    print("Fx:", Fx_direct)
    print("Fy:", Fy_direct)
    print("")

    # Fast Algorithm (Only One N-point FFT)
    Fx, Fy = fftreal(x, y)
    print("================ Fast Algorithm ================")
    print("Fx:", Fx)
    print("Fy:", Fy)
    print("")

    # Compare the results, they should be the same
    print("================ Compare the results ================")
    print("Fx == Fx_direct:", np.allclose(Fx, Fx_direct))
    print("Fy == Fy_direct:", np.allclose(Fy, Fy_direct))
    print("")

if __name__ == "__main__":
    main()
