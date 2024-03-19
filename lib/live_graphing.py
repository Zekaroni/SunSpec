import matplotlib.pyplot as plt
from spectrometer import USB2000P
import numpy as np
from time import time
from os import path, makedirs


def main():
    # Spectrometer Initialization
    spec = USB2000P()
    spec_data = spec.getSpectra()
    wavelengths = list(spec_data.keys())[48:]
    wavelengths = np.delete(wavelengths, [1178])

    # Graph Initialization
    plt.ion()
    fig, ax = plt.subplots()
    line, = ax.plot([], [])
    ax.set_xlabel('Wavelength (nm)')
    ax.set_ylabel('Intensity')
    ax.set_title('Live Spectrometer Data')
    ax.set_ylim([0, 65535])
    annotation = None


    # Output Path Initialization
    output_path = "./output/live"
    if not path.exists(output_path):
        makedirs(output_path)

    while True:
        temp_intensities = spec.getIntensities()
        intensities = temp_intensities[48:]     # Remove optical black pixels
        intensities = np.delete(intensities, [1178]) # Remove a "broken" pixel from GRAPHICAL data
        max_index = np.argmax(intensities)           # Get MAX index
        peak_wavelength = wavelengths[max_index]     # Get MAX x pos
        peak_intensity = intensities[max_index]      # Get MAX y pos

        line.set_ydata(intensities)
        line.set_xdata(wavelengths)


        if annotation:
            annotation.remove()

        annotation_text = f'Peak: ({peak_wavelength:.2f} nm, {peak_intensity:.2f})'
        annotation = ax.annotate(
            annotation_text,
            xy         = (peak_wavelength, peak_intensity),
            xytext     = (peak_wavelength + 20, peak_intensity),
            arrowprops =
                dict(
                    facecolor='black',
                    arrowstyle='->'
                )
        )

        ax.relim()
        ax.autoscale_view()
        fig.canvas.draw()
        fig.canvas.flush_events()

        # timeframe = time()
        # with open(f"{output_path}/{timeframe}.spec", "wb") as output_file:
        #     for intensity in intensities:
        #         output_file.write(np.int16(intensity))


if __name__ == "__main__":
    main()