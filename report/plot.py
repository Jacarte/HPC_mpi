import matplotlib.pyplot as plt


non_blocking_data = [0.077699, 0.044840, 0.022413, 0.012153, 0.009659]

plt.plot([8, 16, 32, 64, 128], non_blocking_data, 'o-')

plt.grid(True)
plt.title("MPI Non Blocking communication")
plt.xlabel("processes")
plt.ylabel("execution time(s)")
#plt.xticks([8,16,32,64,128])
plt.savefig("graph-pi-non-blocking.png", dpi=800)