import matplotlib.pyplot as plt
import gi
gi.require_version("Gtk", "3.0")


def plot_system(file, alpha=1.0, label='', plot_type="plot", color=''):
    initializer = list(map(float, file.readline().split(' ')))
    step, count = map(float, file.readline().split(' '))
    x = []
    y = []
    for i in range(int(count)):
        value = float(file.readline())
        x.append(step * i)
        y.append(value)
    plt.xlim((x[0], x[-1]))
    if plot_type == "plot":
        plt.plot(x, y, alpha=alpha, label=label)
    elif plot_type == "scatter":
        plt.scatter(x, y, alpha=alpha, label=label, s=0.5, c=color)


f = open("output.txt")
plot_system(f, label="original with noise", plot_type="scatter", color="#000000")
plot_system(f, label="original")
iterations = int(f.readline())
steps = []
for _ in range(iterations):
    plot_system(f, 0.1)
plot_system(f, alpha=0.8, label="returned by BO")
plt.legend()
plt.show()
