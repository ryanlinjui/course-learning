import numpy as np
import matplotlib.pyplot as plt

def idft(H_d):
    N = len(H_d)
    r1 = []
    for n in range(len(H_d)):
        temp = 0
        for m in range(len(H_d)):
            temp += (1 / N) * (H_d[m] * np.exp(2j * np.pi * m * n / N))
        r1.append(temp)
    return r1

def FrequencySamplingMethod(k:int):

    # Step 1: Sampling H_d(m/N)
    N = 2 * k + 1
    N_list = np.linspace(0, 1, N)

    H_d = []
    for i in range(len(N_list)):
        if i/N < 0.5 and i/N > 0:
            H_d.append(-1j)
        elif i/N > 0.5 and i/N < 1:
            H_d.append(1j)
        else:
            H_d.append(0)
            
    # add transision band
    H_d[0] = -0.5j
    H_d[k] = -0.5j
    H_d[k+1] = 0.5j
    H_d[-1] = 0.5j
    H_d = np.array(H_d)

    # Step 2: H_d(m/N) inverse discrete Fourier transform (IDFT)
    r1 = idft(H_d)

    # Step 3: Calculate r[n]
    # r[n] = r1[n], for n = 0,1,2,...,k, k = (N-1)/2
    # r[n] += r1[n+N], for n = -k,-k+1,...,-1
    # r[n], n range from -(N-1)/2 to (N-1)/2

    r = np.concatenate((r1[k:], r1[:k]))
    plt.plot(r.real)
    plt.title("Impulse Response")
    plt.xlabel("N")
    plt.ylabel("Amplitude")
    plt.show()

    # Step 4: Calculate R(F) by DTFT
    F = np.linspace(0, 1, 10001)
    R_F = 0
    for n in range(len(r)):
        R_F += r[n] * np.exp(-2j * np.pi * F * (n-k-1))
    R_F = np.array(R_F)

    plt.plot(N_list, H_d.imag, "r--")
    plt.plot(F, R_F.imag)
    plt.legend(["H_d(F)", "R(F)"])
    plt.title("Imaginary Part of the Frequency Response")
    plt.xlabel("F")
    plt.ylabel("Amplitude")
    plt.show()

if __name__ == "__main__":
    k = int(input("Please input the value of k: "))
    FrequencySamplingMethod(k)