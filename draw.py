import matplotlib.pyplot as plt
# import gi
# gi.require_version("Gtk", "3.0")


def plot_system(x, y, alpha=1.0, label='', plot_type="plot", color=''):
    plt.xlim((x[0], x[-1]))
    if plot_type == "plot":
        if color:
            plt.plot(x, y, alpha=alpha, label=label, color=color)
        else:
            plt.plot(x, y, alpha=alpha, label=label)
    elif plot_type == "scatter":
        plt.scatter(x, y, alpha=alpha, label=label, s=2, c=color)


f = open("test.txt")
step = float(f.readline())
lines = f.readlines()
X = []
Y = []
i = 0
while i < len(lines):
    x = []
    y = []
    count = int(lines[i])+1
    for j in range(1, count):
        x.append(step * (j-1))
        y.append(float(lines[i+j]))
    X.append(x)
    Y.append(y)
    i += count

plot_system(X[0], Y[0], label="original with noise", plot_type="scatter", color="#000000")
plot_system(X[1], Y[1], label="original")
plot_system(X[-1], Y[-1], alpha=0.6, label="returned by BO", color="#FF0000")

for i in range(2, len(X) - 1):
    plot_system(X[i], Y[i], alpha=0.05)

plt.legend()
plt.show()
