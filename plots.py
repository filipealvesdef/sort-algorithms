import matplotlib.pyplot as plt
import os

benchmarks_dir = 'output'
plots_dir = os.path.join(benchmarks_dir, 'plots')
algorithms_dic = {
    'selection_sort_rand.out': 'Selection sort',
    'insertion_sort_rand.out': 'Insertion sort',
    'merge_sort_rand.out': 'Mergesort',
    'heap_sort_rand.out': 'Heapsort',
    'quicksort_rand.out': 'Quicksort',
}
if __name__ == '__main__':
    if not os.path.exists(plots_dir):
        os.mkdir(plots_dir)
    files = []
    tests = {}
    for f in os.listdir(benchmarks_dir):
        if os.path.isfile(os.path.join(benchmarks_dir, f)):
            files.append(f)
    for f in files:
        file_path = os.path.join(benchmarks_dir, f)
        with open(file_path) as file:
            data = file.readlines()
            x = []
            y = []
            for line in data:
                vals = line.split()
                x.append(float(vals[0]))
                execution_t = list(map(float, vals[1:-1]))
                avg = sum(execution_t) / len(execution_t)
                y.append(avg)
            tests[f] = {'x': x, 'y': y}
    for t in tests:
        plt.figure()
        plt.plot(tests[t]['x'], tests[t]['y'])
        plot_name = t.split('.out')[0] + '.svg'
        plt.savefig(os.path.join(plots_dir, plot_name))
    plt.figure()
    for t in tests:
        if t.find('rand') > 0:
            algorithm_name = algorithms_dic[t]
            plt.plot(tests[t]['x'], tests[t]['y'], label=algorithm_name)
    plt.legend()
    plt.savefig(os.path.join(plots_dir, 'all-algorithms.svg'))
