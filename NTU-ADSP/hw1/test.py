# Design a Mini-max lowpass FIR filter with the given specifications:
# Filter length: 17
# Sampling frequency: 6000 Hz
# Passband: 0-1200 Hz
# Transition band: 1200-1500 Hz
# Weighting function: W(F) = 1 for passband, W(F) = 0.6 for stop band
# Delta in the weighting function: 0.0001

import numpy as np
from math import (
    cos, pi, e
)
import matplotlib.pyplot as plt

def MinimaxLowpassFIRfilter():
    
    FILTER_ORDER = 17
    SAMPLING_FREQUENCY = 6000
    PASSBAND = [0, 1200]
    TRANSBAND = [1200, 1500]
    WEIGHT = [1, 0.6]
    FREQUENCY_DELTA = 0.0001
    STOP_BAND = [1500, SAMPLING_FREQUENCY / 2]
    
    # step 1
    k = int((FILTER_ORDER - 1) / 2)
    extreme_point_num = k + 2
    fn, ideal = generate_random_array(k + 2, PASSBAND[0], PASSBAND[1], TRANSBAND[0], TRANSBAND[1])
    print(PASSBAND, "\n", TRANSBAND, "\n", STOP_BAND, "\n",fn, "\n",ideal)
    # iteration
    A_m = np.zeros((k + 2, k + 2))
    S_m = np.zeros((k + 1, 1))
    H_m = ideal
    e_list = [0, 1e9]

    iteration_count = 0
    while True:
        iteration_count += 1
        print(f"Iteration: {iteration_count}")

        # step 2
        for i in range(k + 2):
            for j in range(k + 2):
                A_m[i][j] = cos(2 * pi * fn[i] * j / SAMPLING_FREQUENCY)
        # step 3
        A_m_inv = np.linalg.inv(A_m)
        S_m = np.dot(A_m_inv, H_m)
        R_f = np.zeros(len(fn))
        for i in range(len(fn)):
            for s in S_m:
                R_f[i] += (s * cos(2 * pi * fn[i] * i / SAMPLING_FREQUENCY))

        # step 4
        err_f = np.zeros(len(R_f))
        for i in range(len(R_f)):
            err_f[i] = abs(R_f[i] - H_m[i])
        e = max(err_f)
        e_list.append(e)
        if e_list[-2] - e_list[-1] < FREQUENCY_DELTA:
            break
        # step 5
        max_err_idx = np.argmax(err_f)
        fn = np.insert(fn, max_err_idx, fn[max_err_idx])
        ideal = np.insert(ideal, max_err_idx, ideal[max_err_idx])
        H_m = ideal

    print(f"Converged at iteration {iteration_count}")
    print(f"fn: {fn}")
    print(f"ideal: {ideal}")
    print(f"S_m: {S_m}")
    print(f"R(f): {R_f}")
    print(f"Error: {e}")

    plt.plot(fn, R_f, label="R(f)")
    plt.plot(fn, ideal, label="Ideal")
    plt.legend()
    plt.show()


def generate_random_array(n, start1, end1, start2, end2):
    if n % 2 == 0:
        array1 = np.random.uniform(start1+0.01, end1-0.01,  int(n / 2))
        i_array1 = np.ones(int(n / 2))
        array2 = np.random.uniform(start2+0.01, end2-0.01, int(n / 2))
        i_array2 = np.zeros(int(n / 2))
    else:
        array1 = np.random.uniform(start1+0.01, end1-0.01,  int(n / 2))
        i_array1 = np.ones(int(n / 2))
        array2 = np.random.uniform(start2+0.01, end2-0.01, int(n / 2) + 1)
        i_array2 = np.zeros(int(n / 2) + 1)

    combined_array = np.concatenate((array1, array2))
    combined_array.sort()
    ideal_array =  np.concatenate((i_array1, i_array2))
    ideal_array.sort()

    return np.round(combined_array, 2), np.round(ideal_array, 2)



    
        


if __name__ == "__main__":
    MinimaxLowpassFIRfilter()
