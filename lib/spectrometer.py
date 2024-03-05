from seabreeze.spectrometers import Spectrometer
import numpy as np

class USB2000P:
    def __init__(self, pixel_offset: int = 0, integration_time: int = 20000) -> None:
        self.spec = Spectrometer.from_first_available()
        self.pixel_offset = pixel_offset
        self.itegration_time = integration_time
        self.spec.integration_time_micros(self.itegration_time)

    def getSpectra(self) -> dict:
        waves = self.spec.wavelengths()[self.pixel_offset:]
        ampli = self.spec.intensities()[self.pixel_offset:]
        return {waves[i] : ampli[i] for i in range(len(waves))}
    
    def getIntensities(self) -> np.ndarray:
        return self.spec.intensities()[self.pixel_offset:]

if __name__ == "__main__":
    spec = USB2000P()
