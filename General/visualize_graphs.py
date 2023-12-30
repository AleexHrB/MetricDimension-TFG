import networkx as nx
import numpy as np
import matplotlib.pyplot as plt




def main():

    num_nodes = int(input())
    am = np.zeros((num_nodes, num_nodes), dtype=int)

    upper = input()

    for i in range(num_nodes):
        am[i, i] = 0

    k = 0

    for i in range(num_nodes):

        for j in range(i+1, num_nodes):

            am[i, j] = upper[k]
            k = k + 1

            am[j,i] = not am[i, j]




    G = nx.DiGraph(am, nodetype=int)

    pos = nx.spring_layout(G)

    nx.draw(G, pos, with_labels=True)
    plt.show()








main()
