import matplotlib as mpl
mpl.use('Agg')
import matplotlib.pyplot as plt
import numpy as np

x = []
for i in range(3, 31):
  x.append(2**i)

time_intra = [0.000000608, 0.000000653, 0.000000682, 0.000000734, 0.000000770, 0.000000751, 0.000000815, 0.000000978, 0.000001161, 0.000001707, 0.000003898, 0.000004125, 0.000007594, 0.000011530, 0.000024257, 0.000045474, 0.000088394, 0.000173810, 0.000345354, 0.000689859, 0.001377771, 0.002741075, 0.005612578, 0.011531770, 0.023308010, 0.046876423, 0.094284530, 0.193143849]
time_inter = [0.000001717, 0.000001941, 0.000001702, 0.000001564, 0.000001600, 0.000001712, 0.000001829, 0.000001943, 0.000002546, 0.000003426, 0.000006628, 0.000006628, 0.000008008, 0.000013492, 0.000021279, 0.000032403, 0.000058684, 0.000116324, 0.000225928, 0.000471337, 0.000999577, 0.002077246, 0.004228852, 0.008591294, 0.017421808, 0.034961929, 0.071018376, 0.143390267]

# Latency, bandwdith calculations

fit_intra = np.polyfit(x, time_intra, 1)
print("polyfit for inter-communication:", fit_intra)
print("Bandwidth intra", (1/fit_intra[0])/10**9)
print("Latency intra", fit_intra[1]/10**-6)

fit_inter = np.polyfit(x, time_inter, 1)
print("polyfit for inter-communication:", fit_inter)
print("Bandwidth inter", (1/fit_inter[0])/10**9)
print("Latency inter", fit_inter[1]/10**-6)

fig = plt.figure(figsize=(10, 8))

plt.title("Message size Vs Time")
plt.grid(True)
plt.xlabel("Size")
plt.ylabel("Time(s)")
plt.plot(x, time_intra, 'o-', label='intra-node')
plt.plot(x, time_inter, 'o-', label='inter-node')
plt.legend(loc='lower right')
plt.savefig("graph-ping-pong.png", dpi=800)

