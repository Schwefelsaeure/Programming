from matplotlib import pyplot as plt

import numpy as np

# Data
x = np.linspace(0, 2*np.pi, 50)

# Style
plt.style.use("seaborn")

# Figure and Axes Setup
figure = plt.figure(1)

gridsize = (2, 2)
ax1 = plt.subplot2grid(gridsize, (0, 0))
ax2 = plt.subplot2grid(gridsize, (0, 1))
ax3 = plt.subplot2grid(gridsize, (1, 0))
ax4 = plt.subplot2grid(gridsize, (1, 1))

axes = [ax1, ax2, ax3, ax4]

# Plots
for i in range(len(axes)):
    y = np.sin(i * x)

    color = "C{}".format(i)
    axes[i].plot(x, y, color=color, label="plot")
    axes[i].scatter(x, y, color=color, label="scatter")

    axes[i].set_title("$sin({}*x)$".format(i))
    axes[i].set_xlabel("x")
    axes[i].set_ylabel("f(x)")
    axes[i].legend()

plt.show()
