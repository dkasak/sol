# Sol

Sol is a simple renderer that I wrote for my bachelor's thesis. It currently
supports ray casting and a basic ray tracing algorithm.

## Build instructions

```
make
```

## Usage

To render your own scene:

1. Write a new world file and put it into `worlds/`. Check the other files
   there for an example on how to do that.
2. Replace the world `#include` directive in `sol.cpp` with your own.
3. Rebuild by running `make`.
3. `sol -H <hres> -V <vres> -s <num_supersamples> -S jittered`

The output image will be saved as `output.bmp`.

There's also `sol --help` to see all supported flags.

## Example renderings

![four_boxes](http://i.imgur.com/WINzq7u.png "Four boxes")
![not_nothing](https://i.imgur.com/lJLdDZV.png)
![coloured_shadows](https://i.imgur.com/MrDUYgN.png "Coloured shadows")
