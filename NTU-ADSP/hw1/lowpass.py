# Design a Mini-max lowpass FIR filter with the given specifications:
# Filter length: 17
# Sampling frequency: 6000 Hz
# Passband: 0-1200 Hz
# Transition band: 1200-1500 Hz
# Weighting function: W(F) = 1 for passband, W(F) = 0.6 for stop band
# Delta in the weighting function: 0.0001
from math import cos, pi
import numpy as np
import matplotlib.pyplot as plt

FILTER_ORDER = 17
SAMPLING_FREQUENCY = 6000
PASSBAND = [0, 1200]
TRANSBAND = [1200, 1500]
WEIGHT = [1, 0.6]
FREQUENCY_DELTA = 0.0001


class FIRFilter:
    def __init__(
        self,
        filter_order: int,
        frequency_delta: float,
        passband: tuple[int, int],
        transband: tuple[int, int],
        sampling_frequency: int,
        weight: tuple[int, int],
    ):
        self.filter_order = filter_order
        self.frequency_delta = frequency_delta
        self.sampling_frequency = sampling_frequency
        self.desired_passband = [
            passband[0] / sampling_frequency,
            sum(transband) / 2 / sampling_frequency,
        ]
        self.weight_range = [
            [
                passband[0] / sampling_frequency,
                passband[1] / sampling_frequency,
                weight[0],
            ],
            [transband[1] / sampling_frequency, 0.5, weight[1]],
        ]

        self.k = int((self.filter_order - 1) / 2)
        self.expansion_length = self.k + 2

    def weight(self, x):
        if self.weight_range[0][0] <= x <= self.weight_range[0][1]:
            return self.weight_range[0][2]
        elif self.weight_range[1][0] <= x <= self.weight_range[1][1]:
            return self.weight_range[1][2]
        else:
            return 0

    def desired_response(self, x):
        if self.desired_passband[0] <= x <= self.desired_passband[1]:
            return 1
        else:
            return 0

    def error(self, frequency, samples):
        return (
            self.filtered_response(frequency, samples)
            - self.desired_response(frequency)
        ) * self.weight(frequency)

    def filtered_response(self, frequency, samples):
        response = 0
        for n in range(self.k + 1):
            response += samples[n] * cos(2 * pi * n * frequency)
        return response

    def optimize(self):
        current_max_error = int(1e9)
        frequency_samples = [i * 0.05 for i in range(20)]
        while True:
            A = []
            for m in range(self.expansion_length):
                row = []
                for n in range(self.expansion_length):
                    if n == 0:
                        row.append(1)
                    elif n == self.expansion_length - 1:
                        row.append(((-1) ** m) / self.weight(frequency_samples[m]))
                    else:
                        row.append(cos(2 * n * pi * frequency_samples[m]))
                A.append(row)

            A = np.array(A)
            A_inv = np.linalg.inv(A)

            b = []
            for m in range(self.expansion_length):
                b.append(self.desired_response(frequency_samples[m]))
            b = np.array(b)

            samples = np.matmul(A_inv, b)

            new_extreme = []
            max_error = -1
            previous_error = None
            current_error = None
            for i in range(int(0.5 / self.frequency_delta) + 2):
                if i == 0:
                    continue
                if i == 1:
                    previous_error = 0
                    current_error = self.error(0 * self.frequency_delta, samples)
                if i == int(0.5 / self.frequency_delta) + 1:
                    frequency = 0
                else:
                    frequency = self.error(i * self.frequency_delta, samples)

                if (
                    current_error - frequency > 0
                    and current_error - previous_error > 0
                    or current_error - frequency < 0
                    and current_error - previous_error < 0
                ):
                    new_extreme.append((i - 1) * self.frequency_delta)
                    if max_error < abs(current_error):
                        max_error = abs(current_error)

                previous_error = current_error
                current_error = frequency

            if 0 <= current_max_error - max_error <= self.frequency_delta:
                self.max_error = max_error
                self.samples = samples
                break

            current_max_error = max_error
            frequency_samples = new_extreme[: self.expansion_length]
            print(f"Current max error: {current_max_error}")

    def get_impulse_response(self):
        impulse_response = []
        for i in range(self.filter_order):
            if i < self.k:
                impulse_response.append(self.samples[self.k - i] / 2)
            elif i == self.k:
                impulse_response.append(self.samples[0])
            else:
                impulse_response.append(self.samples[i - self.k] / 2)
        return impulse_response

    def plot_frequency_response(self):
        t = np.arange(0.0, 0.5, self.frequency_delta)
        plt.plot(
            t,
            np.array(
                [self.filtered_response(t[i], self.samples) for i in range(len(t))]
            ),
            lw=2,
        )
        plt.plot(
            t, np.array([self.desired_response(t[i]) for i in range(len(t))]), lw=2
        )
        plt.title("Frequency Response")
        plt.savefig("frequency_response.png")
        plt.close()

    def plot_impulse_response(self):
        t = np.arange(0, self.filter_order)
        plt.stem(t, np.array([self.get_impulse_response()[i] for i in range(len(t))]))
        plt.title("Impulse Response")
        plt.savefig("impulse_response.png")
        plt.close()


fir_filter = FIRFilter(
    FILTER_ORDER,
    FREQUENCY_DELTA,
    PASSBAND,
    TRANSBAND,
    SAMPLING_FREQUENCY,
    WEIGHT,
)

fir_filter.optimize()
fir_filter.plot_frequency_response()
fir_filter.plot_impulse_response()
