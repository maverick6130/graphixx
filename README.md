# FMX Modelling

- Dhruv Arora 190050034
- Raj Aryan Agrawal 190050097

### Declaration
The assignment is our own work, and we have not copied from anywhere

## Input and Movement
At a given point in the scene, one of the objects will be active, noticed by a red and yellow colored shape. We can switch between the active objects by using the keys
- <mark>KEY_1</mark>: Previous object
- <mark>KEY_2</mark>: Next object

By default, the selected object in this case is the Rider, and the order is Rider -> Bike -> Track in a cycle.

For rotating objects about their pivots, the red highlighted shape is the active component in the heirarchy of object about which rotation will occur. For rotating about the pivot (these axes rotate with object in question)
- <mark>KEY_O</mark> and <mark>KEY_P</mark>: Rotate around X axis
- <mark>KEY_K</mark> and <mark>KEY_L</mark>: Rotate around Y axis
- <mark>KEY_N</mark> and <mark>KEY_M</mark>: Rotate around Z axis

The yellow highlighted shape shows the next shape to move to as the new pivot. This rotates around all the children connected to the current pivot in the heirarchy. The controls are
- <mark>KEY_LEFT</mark> and <mark>KEY_RIGHT</mark>: Choose between children of pivot
- <mark>KEY_DOWN</mark>: Move to selected child as new pivot
- <mark>KEY_UP</mark>: Move to parent as new pivot

For global rotation, move to the original default location of the pivot (middle torso for rider and engine for bike) and the same keys act for global rotation.

For translation of object
- <mark>KEY_Q</mark> and <mark>KEY_W</mark>: Translate along X axis
- <mark>KEY_A</mark> and <mark>KEY_S</mark>: Translate along Y axis
- <mark>KEY_Z</mark> and <mark>KEY_X</mark>: Translate along Z axis
\end{itemize}