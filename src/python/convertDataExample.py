import matplotlib.pyplot as plt
import numpy as np

x_values = np.linspace(200, 1100, 2048)
num_small_waves = 200
num_big_waves = 1
y_values = np.zeros_like(x_values)
for _ in range(num_small_waves):
    frequency = np.random.uniform(0.5, 2.0)
    amplitude = np.random.uniform(0.1, 0.5)
    phase = np.random.uniform(0, 2 * np.pi)
    noise = np.random.uniform(-0.05, 0.05, size=len(x_values))
    y_values += amplitude * np.sin(2 * np.pi * frequency * x_values / 1100 + phase) + noise
big_frequency = np.random.uniform(0.5, 2.0)
big_amplitude = np.random.uniform(0.2, 0.3)
big_phase = np.random.uniform(0, 2 * np.pi)
big_noise = np.random.uniform(-0.1, 0.1, size=len(x_values))
y_values += big_amplitude * np.sin(2 * np.pi * big_frequency * x_values / 1100 + big_phase) + big_noise
y_values = np.abs(y_values)
y_values = 0.5 * y_values
y_values = 32767 * (y_values / np.max(y_values))

plt.plot(x_values, y_values, label='Spectra')
plt.title('SunSpec Spectra Results')
plt.xlabel('Wavelength')
plt.ylabel('Amplitude')
plt.legend()
plt.show()
