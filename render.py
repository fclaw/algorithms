import networkx as nx
import matplotlib.pyplot as plt

# Define the edges (from, to, weight)
edges = [
    (5, 3, 54), (5, 17, 52), (3, 16, 22), (16, 8, 76),
    (8, 4, 70), (4, 2, 70), (2, 18, 85), (3, 10, 88),
    (17, 6, 91), (3, 14, 45), (18, 15, 61), (5, 1, 68),
    (16, 13, 82), (18, 7, 64), (5, 12, 33), (1, 11, 23), (7, 9, 1)
]

# Create graph
G = nx.Graph()
for u, v, w in edges:
    G.add_edge(u, v, weight=w)

# Position using spring layout for better spacing
pos = nx.spring_layout(G, seed=42)

# Draw nodes and edges
plt.figure(figsize=(12, 8))
nx.draw(G, pos, with_labels=True, node_color='lightblue', node_size=700, font_size=10, font_weight='bold')
edge_labels = nx.get_edge_attributes(G, 'weight')
nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels)

plt.title("Rendered Graph with Weights")
plt.axis('off')
plt.tight_layout()
plt.show()