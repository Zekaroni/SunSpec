import matplotlib.pyplot as plt
import numpy as np

def plot_16bit_values(file_path):
    values = np.fromfile(file_path, dtype=np.uint16)
    
    plt.plot(values)
    plt.show()

file_path = r'.\output\1710642424.3499076.spec'
plot_16bit_values(file_path)
