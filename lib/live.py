from spectrometer import USB2000P
import numpy as np
from time import time
from os import path, makedirs


def main():
    spec = USB2000P()
    output_path = "./output/live"
    if not path.exists(output_path):
        makedirs(output_path)

    while True:
        timeframe = time()
        with open(f"{output_path}/{timeframe}.spec", "wb") as output_file:
            for intensity in spec.getIntensities():
                output_file.write(np.int16(intensity))


if __name__ == "__main__":
    main()
