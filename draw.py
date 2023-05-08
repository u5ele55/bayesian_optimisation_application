import matplotlib.pyplot as plt
# import gi
# gi.require_version("Gtk", "3.0")


def plot_system(file, step, alpha=1.0, label='', plot_type="plot", color=''):
    count = int(file.readline())
    print(count)
    x = []
    y = []
    for i in range(count):
        value = float(file.readline())
        x.append(step * i)
        y.append(value)
    plt.xlim((x[0], x[-1]))
    if plot_type == "plot":
        if color: plt.plot(x, y, alpha=alpha, label=label, color=color)
        else: plt.plot(x, y, alpha=alpha, label=label) 
    elif plot_type == "scatter":
        plt.scatter(x, y, alpha=alpha, label=label, s=1, c=color)


f = open("test.txt")
s = float(f.readline())
plot_system(f, s, label="original with noise", plot_type="scatter", color="#000000")
plot_system(f, s, label="original")
iterations = 1000
steps = []
for _ in range(iterations):
    if _ == 46:
        break
    try:
        plot_system(f, s, alpha=0.1)
    except:
        print(_)
        break
plot_system(f, s, alpha=0.6, label="returned by BO", color="#FF0000")
plt.legend()
plt.show()
