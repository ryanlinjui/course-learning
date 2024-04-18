import numpy as np
from math import (
    cos, pi, e
)
import matplotlib.pyplot as plt

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
        i_array2 = np.zero(int(n / 2) + 1)

    combined_array = np.concatenate((array1, array2))
    combined_array.sort()
    ideal_array =  np.concatenate((i_array1, i_array2))
    ideal_array.sort()

    return np.round(combined_array, 2), np.round(ideal_array, 2)

def MinimaxLowpassFIRfilter():
    
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
    
    # step 1
    k = int((filter_length - 1) / 2)
    extreme_point_num = k + 2
    fn, ideal = generate_random_array(k + 2, pass_band[0], pass_band[1], stop_band[0], stop_band[1])
    print("passband:", pass_band)
    print("stopband:", stop_band)
    print("transition band:", transition_band)
    print("fn:", fn)
    print("ideal:", ideal)

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
        for m in range(k + 2):
            for n in range(k + 1):
                A_m[m][n] = cos(2 * pi * fn[m] * n)
            
            # for n last k
            if fn[m] >= pass_band[0] and fn[m] <= pass_band[1]:
                A_m[m][-1] = ((-1) ** m) / (pass_wf ** fn[m])
            elif fn[m] >= stop_band[0] and fn[m] <= stop_band[1]:
                A_m[m][-1] = ((-1) ** m) / (stop_wf * fn[m])
            else:
                raise ValueError("transition band error")  # Fix the typo in the raise statement

        # R(F) caculation
        S_m = np.matmul(np.linalg.inv(A_m), H_m)   
        R_f = np.zeros(len(fn))
        for i in range(len(fn)):
            for s in S_m:
                R_f[i] += (s * cos(2 * pi * fn[i] * i))
        
        # step 3
        # err(F) caculation
        err_f = np.zeros(k+2)
        for i in range(k+2):
            err_f[i] = R_f[i] - H_m[i]

            if fn[i] >= pass_band[0] and fn[i] <= pass_band[1]:
                err_f[i] *= pass_wf
            elif fn[i] >= stop_band[0] and fn[i] <= stop_band[1]:
                err_f[i] *= stop_wf
            else:
                raise ValueError("transition band error 2")

        # # step 4
        # extreme_points = []
        # max_error = -1
        # previous_error = None
        # current_error = None
        # for i in range(int(0.5 / sampling_frequency) + 2):
        #     if i == 0:
        #         continue
        #     if i == 1:
        #         previous_error = 0
        #         current_error = err_f[0]
        #     if i == int(0.5 / sampling_frequency) + 1:
        #         frequency = 0
        #     else:
        #         frequency = err_f[i]

        #     if (
        #         current_error - frequency > 0
        #         and current_error - previous_error > 0
        #         or current_error - frequency < 0
        #         and current_error - previous_error < 0
        #     ):
        #         extreme_points.append((i - 1) * sampling_frequency)
                
        #         if max_error < abs(current_error):
        #             max_error = abs(current_error)

        #     previous_error = current_error
        #     current_error = frequency
    
        # step 5
        e_list[0] = np.max(np.abs(err_f))
        print(f"maximal error: {e_list[0]}")
        print(f"error matrix:\n{err_f}")

        # case A
        if e_list[1] - e_list[0] > delta or e_list[1] - e_list[0] < 0:
            e_list[0], e_list[1] = e_list[1], e_list[0]
            fn = err_f.copy()
        
        # case B
        if 0 <= e_list[1] - e_list[0] and e_list[1] - e_list[0] <= delta:
           pass
        else:
            raise ValueError("case error")  # Fix the typo in the raise statement

        # step 6
        h = np.zeros(filter_length)
        h[k] = S_m[0]
        for i in range(1, len(S_m)):
            h[k - i] = S_m[i] / 2
            h[k + i] = S_m[i] / 2
        
        print(f"the impulse response h[n]:\n{h}") 
        break

if __name__ == "__main__":
    MinimaxLowpassFIRfilter()
