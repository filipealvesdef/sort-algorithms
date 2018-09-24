import matplotlib.pyplot as plt
import os

benchmarks_dir = 'output'
plots_dir = os.path.join(benchmarks_dir, 'plots')
if __name__ == '__main__':
    if not os.path.exists(plots_dir):
        os.mkdir(plots_dir)
    file_path = os.path.join(benchmarks_dir, 'quicksort_reversed.out')
    with open(file_path) as file:
        data = file.readlines()
        x = []
        y = []
        plt.figure()
        for line in data:
            vals = line.split()
            execution_t = list(map(float, vals[1:-1]))
            sample_len = float(vals[0])
            x.append(sample_len)
            avg = sum(execution_t) / len(execution_t)
            y.append(avg)
            for e in execution_t:
                plt.scatter(sample_len, e, 1, 'r')
        plt.plot(x, y)
        plt.savefig(os.path.join(plots_dir, 'quicksort_reversed_all_exec.svg'))
