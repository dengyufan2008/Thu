import sys
import pandas as pd
import matplotlib.pyplot as plt

fn = sys.argv[1] if len(sys.argv)>1 else 'perf_large.csv'
df = pd.read_csv(fn)

# Summary table: pick single-thread times for tasks 1..3 and task4 with threads=1
single = df[(df['threads']==1) & (df['kv_block']==0) & (df['task']<=4)].copy()
single = single.sort_values('task')
base = single[single['task']==1]['avg_ms'].values[0]
single['speedup'] = base / single['avg_ms']

print('\nExecution time and speedup (large dataset)')
print(single[['task','avg_ms','speedup']].to_string(index=False))

# Plot Task4 scaling
task4 = df[df['task']==4].sort_values('threads')
plt.figure(figsize=(6,4))
plt.plot(task4['threads'], base / task4['avg_ms'], marker='o')
plt.xticks([1,2,3,4])
plt.xlabel('Threads')
plt.ylabel('Speedup vs Task1')
plt.title('Task4 Scaling (large dataset)')
plt.grid(True)
plt.savefig('task4_scaling.png', dpi=200)
print('\nSaved plot to task4_scaling.png')
