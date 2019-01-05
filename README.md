![](https://img.shields.io/github/tag/jmcph4/jcrl.svg)
# JCRL #
---

JCRL is a library of fundamental algorithms and data structures written in C. JCRL is designed as a purely educational resource and should not be used for production. 

## Developent Status ##

~~JCRL is not versioned currently as it is incredibly unstable. After the core API has been settled versioning will start.~~ JCRL is currently versioned according to Semantic Versioning 2.0. Previous commits have been tagged accordingly to retroactively version previous releases. Technically, the library itself should still not be considered stable; however, it is unlikely at this point that the public API will undergo drastic, breaking changes.

Furthermore, an official list of algorithms and data structures to qualify for a 1.0.0 release is underway, but still not complete. One this list is complete and has been fully implemented, JCRL 1.0.0 will be released.

### Current Progress ###
For a list of ADTs and algorithms implemented by the library, check the header files under `src/`.

### A Word on Completeness ###
This list is intended to represent the basic computer science canon (somewhat more content than what might be taught in an undergraduate algorithms and data structures course).

JCRL implements the model of Abstract Data Types (ADTs) defined [here](https://gist.github.com/jmcph4/683238e6236ed0b5f90457f7eb8c767a "Definitions of various ADTs · GitHub") and also below:

## Workflow ##

To build the library:

    $ make

To build tests and add debugging symbols:

    $ make debug

Each module gets its own executable under `build/`; however, you can run all tests by using the provided utility scripts (under `tools/`):

    $ ./tools/run_tests.sh


    
