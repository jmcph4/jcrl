# JCRL #
---

JCRL is a library of fundamental algorithms and data structures written in C. JCRL is designed as a purely educational resource and should not be used for production. 

JCRL is not versioned currently as it is incredibly unstable. After the core API has been settled versioning will start.

JCRL implements the model of Abstract Data Types (ADTs) defined [here](https://gist.github.com/jmcph4/683238e6236ed0b5f90457f7eb8c767a "Definitions of various ADTs · GitHub") and also below:

![ADT Hierarchy Graph](https://gist.githubusercontent.com/jmcph4/3a429b9478e9bdd7ed25cb3b6aa07acf/raw/bdf21f776de04cb54dea4d921a58a04b01e1f51e/ADT_graph_image.PNG)

JCRL aims to be as close as practically possible to this mathematical model.

Currently, JCRL implements:

 - lists
 - stacks
 - queues
 - bubblesort
 - sets
 - insertion sort
 - multisets

Obviously, many more are on the way.

## Workflow ##

To build the library:

    make

To build tests:

    make debug

