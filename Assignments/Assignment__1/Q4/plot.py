import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

df = pd.read_csv(r'D:\\College\\Sem 3\\Design of Algorithm\\2024\\Assignments\\Assignment__1\\Q4\\output\\sorting_performance_4.csv')
plt.figure(figsize=(10, 6))

colors = ['purple', 'g', 'violet', 'c', 'm', 'y', 'k']

for idx,test_case in enumerate(df['Test Case'].unique()):
    subset = df[df['Test Case'] == test_case]
    plt.plot(subset['Array Size'], subset['Time (seconds)'], marker='o', label=test_case, color=colors[idx % len(colors)])

plt.xlabel('Array Size')
plt.ylabel('Time (seconds)')
plt.legend()
plt.grid(True)

plt.savefig('SortingPerformanceGraph_4.png')

plt.show()
