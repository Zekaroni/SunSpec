import matplotlib.pyplot as plt
import numpy as np

def plot_16bit_values(file_path):
    values = np.fromfile(file_path, dtype=np.uint16)
    
    plt.plot(values)
    plt.show()

file_path = r'.\output\single\1710785453.5301242.spec'
plot_16bit_values(file_path)
