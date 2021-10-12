import os
import subprocess
import matplotlib.pyplot as plt
import math
#code for calculating runtimes





n = 5
while(n<10000):
    proc = subprocess.Popen(["./problem1", str(n)])
    proc.wait()
    n+=2
    
    


n = 5
ns = []
eff = []
naive = []
  
f = open('runtimes.txt','r')
for row in f:
    row = row.split(' ')
    ns.append(n)
    eff.append(float(row[0]))
    naive.append(float(row[1]))
    n+=2
  

plt.figure(figsize=(8, 6), dpi=200)
plt.plot(ns, eff, color = 'y', label='runtime(efficient)')
plt.plot(ns, naive, color = 'g', label="runtime(naive)")

c1 = 5.3*pow(10, 7)
sq = [x*x/c1 for x in ns]
c2 = 1.6* pow(10, 8)
logn = [x*x*math.log(x, 2)/c2 for x in ns]

plt.plot(ns, sq, color = 'b', label=r'$(1.88x10^{-8})n^{2}$')
plt.plot(ns, logn, color = 'r', label=r'$(6.25x10^{-9})n^{2}logn$')

plt.legend()	
plt.xlabel('n') 
plt.ylabel('Time(s)')
# plt.show()
plt.savefig('plot.png')
