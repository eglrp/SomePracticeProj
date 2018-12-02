import numpy as np
from scipy.spatial import Delaunay
import matplotlib.pyplot as plt

# Triangulation of a set of points:
points = np.array([[0, 0], [0, 1.1], [1, 0.3], [1, 1]]) # 定义三角点
tri = Delaunay(points) # 三角剖分

# We can plot it:
plt.triplot(points[:,0], points[:,1], tri.simplices.copy())
plt.plot(points[:,0], points[:,1], 'o')
plt.show()

# Point indices and coordinates for the two triangles forming the triangulation:
print(tri.simplices) # 每个三角面对应的点的索引index
print(points[tri.simplices]) # 每个三角面所包含的坐标点

# Triangle 0 is the only neighbor of triangle 1, and it’s opposite to vertex 1 of triangle 1:
print(tri.neighbors[1]) # 第一个三角面周围有几个邻居三角形，这里只有 1 个
print(points[tri.simplices[1,0]]) # 第 1 个三角面的 X 坐标
print(points[tri.simplices[1,1]]) # 第 1 个三角面的 Y 坐标
print(points[tri.simplices[1,2]]) # 第 1 个三角面的 Z 坐标

# We can find out which triangle points are in:
p = np.array([(0.1, 0.2), (1.5, 0.5)]) # 判断两个点是都在三角网内部
print(tri.find_simplex(p))

# We can also compute barycentric(重心) coordinates in triangle 1 for these points:
b = tri.transform[1,:2].dot(p - tri.transform[1,2])
print(tri)
print(np.c_[b, 1 - b.sum(axis=1)])
