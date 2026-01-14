import numpy as np
import matplotlib.pyplot as plt
from pybind11testwin import *


objet =np.array([0,1.,0.])



print(pow1(2.0,3))
print(add1(4,3))

q1 = Quaternion(1,0,0,0)
q2 = Quaternion(1,1,0,0)
print(q1)


q2.normalisation()
print(q2)
fig = plt.figure()
ax = fig.add_subplot(projection='3d')
ax.scatter3D(objet[0],objet[1],objet[2])


N = 10
for i in range(N+1):
    t = i/N
    qinterp = q1.slerp(q2,t)
    print(qinterp)

    qinterp.normalisation()
    # application de la rotation donnee par qinterp
    quaternion_objet = Quaternion(0,objet[0],objet[1],objet[2])
    quaternion_apres_rotation = qinterp*quaternion_objet*(qinterp.conj())
    objet_apres_rotation = np.array([quaternion_apres_rotation._x,quaternion_apres_rotation._y,quaternion_apres_rotation._z])
    print(objet_apres_rotation)

    ax.scatter3D(objet_apres_rotation[0],objet_apres_rotation[1],objet_apres_rotation[2])

plt.show()


