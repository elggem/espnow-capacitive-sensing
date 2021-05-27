import matplotlib.pyplot as plt
import numpy as np

data = np.genfromtxt("./swiping.csv", delimiter=",")
remove_indices = []

for i,touches in enumerate(data):
  if 0 in touches:
    remove_indices.append(i)

data = np.delete(data, remove_indices, axis=0)

#plt.ylim(-3,3)
plt.xlim(0,600)

plt.plot(data)

plt.show()
