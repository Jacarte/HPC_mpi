import matplotlib.pyplot as plt

blocking = [0.168, 0.0821, 0.0474, 0.0287, 0.0184]
non_blocking_data = [0.077699, 0.044840, 0.022413, 0.012153, 0.009659]
gather = [0.0714, 0.0380, 0.0271, 0.0124, 0.0082]
collective = [0.080, 0.0455, 0.0197, 0.0116, 0.0087]

plt.title("Blocking communication")
plt.grid(True)
plt.xlabel("processes")
plt.ylabel("execution time(s)")
plt.plot([8, 16, 32, 64, 128], blocking, 'o-')
plt.savefig("graph-pi-blocking.png", dpi=800)
plt.cla()

plt.title("Non blocking communication")
plt.grid(True)
plt.xlabel("processes")
plt.ylabel("execution time(s)")
plt.plot([8, 16, 32, 64, 128], non_blocking_data, 'o-')
plt.savefig("graph-pi-non-blocking.png", dpi=800)
plt.cla()

plt.title("MPI_Gather")
plt.grid(True)
plt.xlabel("processes")
plt.ylabel("execution time(s)")
plt.plot([8, 16, 32, 64, 128], gather, 'o-')
plt.savefig("graph-pi-mpi-gather.png", dpi=800)
plt.cla()

plt.title("MPI_Reduce")
plt.grid(True)
plt.xlabel("processes")
plt.ylabel("execution time(s)")
plt.plot([8, 16, 32, 64, 128], collective, 'o-')
plt.savefig("graph-pi-mpi-reduce.png", dpi=800)
plt.cla()


plt.yscale("log")
plt.xscale("log")
plt.grid(True)
plt.xlabel("processes")
plt.ylabel("execution time(s)")
plt.plot([8, 16, 32, 64, 128], blocking, 'o-')
plt.plot([8, 16, 32, 64, 128], non_blocking_data, 'o-')
plt.plot([8, 16, 32, 64, 128], gather, 'o-')
plt.plot([8, 16, 32, 64, 128], collective, 'o-')

plt.legend(["Blocking communication", "Non blocking communication", "MPI_Gather", "MPI_Reduce"])
plt.savefig("all.png", dpi=800)

#plt.xticks([8,16,32,64,128])
