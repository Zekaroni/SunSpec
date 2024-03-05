import matplotlib.pyplot as plt
from spectrometer import USB2000P
import numpy as np
from time import time


spec = USB2000P()
fig, ax = plt.subplots()

spec_data = spec.getSpectra()

wavelengths = list(spec_data.keys())[48:]
intensities = list(spec_data.values())[48:]


wavelengths = np.delete(wavelengths, [1178])
intensities = np.delete(intensities, [1178])
max_index = np.argmax(intensities)
peak_wavelength = wavelengths[max_index]
peak_intensity = intensities[max_index]

ax.plot(wavelengths, intensities)
ax.set_xlabel('Wavelength (nm)')
ax.set_ylabel('Intensity')
ax.set_title('Spectrometer Data')

annotation_text = f'Peak: ({peak_wavelength:.2f} nm, {peak_intensity:.2f})'
ax.annotate(annotation_text,
            xy=(peak_wavelength, peak_intensity),
            xytext=(peak_wavelength + 20, peak_intensity),
            arrowprops=dict(facecolor='black', arrowstyle='->'))

plt.savefig(f"{time()}.jpg")
