import matplotlib.pyplot as plt
import numpy as np

data = np.genfromtxt("./swiping.csv", delimiter=",")

#plt.ylim(-3,3)
plt.xlim(0,600)

plt.plot(data)

plt.show()
