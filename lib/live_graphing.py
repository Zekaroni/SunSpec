import matplotlib.pyplot as plt
from seabreeze.spectrometers import Spectrometer
import numpy as np

plt.ion()
spec = Spectrometer.from_first_available()
spec.integration_time_micros(20000)

fig, ax = plt.subplots()
line, = ax.plot([], [])
ax.set_xlabel('Wavelength (nm)')
ax.set_ylabel('Intensity')
ax.set_title('Live Spectrometer Data')

annotation = None

def update_plot():
    global annotation
    wavelengths = spec.wavelengths()[48:]
    intensities = spec.intensities()[48:]
    wavelengths = np.delete(wavelengths, [1178])
    intensities = np.delete(intensities, [1178])
    max_index = np.argmax(intensities)
    peak_wavelength = wavelengths[max_index]
    peak_intensity = intensities[max_index]

    line.set_xdata(wavelengths)
    line.set_ydata(intensities)

    if annotation:
        annotation.remove()

    annotation_text = f'Peak: ({peak_wavelength:.2f} nm, {peak_intensity:.2f})'
    annotation = ax.annotate(annotation_text,
                xy=(peak_wavelength, peak_intensity),
                xytext=(peak_wavelength + 20, peak_intensity),
                arrowprops=dict(facecolor='black', arrowstyle='->'))

    ax.relim()
    ax.autoscale_view()
    fig.canvas.draw()
    fig.canvas.flush_events()
try:
    while True:
        update_plot()
except KeyboardInterrupt:
    exit(0)