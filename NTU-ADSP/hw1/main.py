# fix version

import numpy as np
from math import (
    cos, pi, e
)
import matplotlib.pyplot as plt

filter_length = 17
sampling_frequency = 6000

# Normalize 0 ~ 6000 to 0 ~ 1
# => but is to be 0 ~ 0.5
pass_band = [0, 1200/sampling_frequency]
transition_band = [1200/sampling_frequency, 1500/sampling_frequency]
stop_band = [1500/sampling_frequency, 0.5]

pass_wf = 1
stop_wf = 0.6

delta = 0.0001

def H_d(x: float):
    if pass_band[0] <= x <= pass_band[1]:
        return 1
    else:
        return 0

def weight(x: float):
    if pass_band[0] <= x <= pass_band[1]:
        return pass_wf
    elif stop_band[0] <= x <= stop_band[1]:
        return stop_wf
    else:
        return 0

def R_F(F: float, S_m: np.ndarray):
    ans = 0
    for n in range(int((filter_length - 1) / 2) + 1):
        ans += S_m[n] * cos(2 * pi * n * F)
    return ans

def err(F: float, S_m: np.ndarray):
    return (R_F(F, S_m) - H_d(F)) * weight(F)

def generate_random_array(n: int, start1: float, end1: float, start2: float, end2: float) -> np.ndarray:
    unique_values = set()
    while len(unique_values) < n:
        
        new_value1 = np.round(np.random.uniform(start1, end1), 2)
        if new_value1 not in unique_values:
            unique_values.add(new_value1)

        if len(unique_values) < n:
            new_value2 = np.round(np.random.uniform(start2, end2), 2)
            if new_value2 not in unique_values:
                unique_values.add(new_value2)

    combined_array = np.array(list(unique_values))
    combined_array.sort()

    return combined_array

def MinimaxLowpassFIRfilter():
    
    # step 1
    k = int((filter_length - 1) / 2)
    extreme_point_num = k + 2
    fn = generate_random_array(k + 2, pass_band[0], pass_band[1], stop_band[0], stop_band[1])
    
    print("passband:", pass_band)
    print("stopband:", stop_band)
    print("transition band:", transition_band)
    print("fn:", fn)
    print("======== Start Iteration ========")

    # iteration
    A_m = np.zeros((k + 2, k + 2))
    S_m = np.zeros((k + 1, 1))
    
    e_list = [0, 1e9]

    iteration_count = 0
    
    current_max_error = 1e9
    
    while True:
        iteration_count += 1
        print(f"Iteration: {iteration_count}")

        # step 2
        for m in range(k + 2):
            for n in range(k + 1):
                A_m[m][n] = cos(2 * pi * fn[m] * n)
            
            # for loop n the last k
            A_m[m][-1] = (-1) ** m / weight(fn[m])

        H_m = []
        for i in range(k + 2):
            H_m.append(H_d(fn[i]))

        H_m = np.array(H_m)
        S_m = np.matmul(np.linalg.inv(A_m), H_m)
        
        # step 3 and 4
        new_extreme = []
        max_error = -1
        previous_error = None
        current_error = None
        for i in range(int(0.5 / delta) + 2):
            if i == 0:
                continue
            if i == 1:
                previous_error = 0
                current_error = err(0 * delta, S_m)
            if i == int(0.5 / delta) + 1:
                frequency = 0
            else:
                frequency = err(i * delta, S_m)

            if (
                current_error - frequency > 0 and current_error - previous_error > 0 or
                current_error - frequency < 0 and current_error - previous_error < 0
            ):
                new_extreme.append((i - 1) * delta)
                if max_error < abs(current_error):
                    max_error = abs(current_error)

            previous_error = current_error
            current_error = frequency

        # Show (c) the maximal error for each iteration
        print(f"Maximal error: {max_error}")

        # step 5
        if 0 <= current_max_error - max_error <= delta:
            # case b
            break
        
        # case a
        current_max_error = max_error
        fn = new_extreme[: k + 2]

    # step 6
    h = []
    for i in range(filter_length):
        if i < k:
            h.append(S_m[k-i]/2)
        elif i == k:
            h.append(S_m[0])
        else:
            h.append(S_m[i-k]/2)
    
    # Show (a) the frequency response
    frequency_response = []
    for i in range(int(0.5 / delta) + 1):
        frequency_response.append(R_F(i * delta, S_m))

    plt.plot([i * delta for i in range(int(0.5 / delta) + 1)], frequency_response)
    plt.plot([i * delta for i in range(int(0.5 / delta) + 1)], [H_d(i * delta) for i in range(int(0.5 / delta) + 1)])
    plt.xlabel("Frequency")
    plt.ylabel("Amplitude")
    plt.title("Frequency Response")
    plt.show()

    # Show (b) the impulse response h[n]
    plt.stem([i for i in range(filter_length)], h)
    plt.xlabel("n")
    plt.ylabel("h[n]")
    plt.title("Impulse Response")
    plt.show()
    
if __name__ == "__main__":
    MinimaxLowpassFIRfilter()