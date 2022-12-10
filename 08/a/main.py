import numpy as np

with open("../input.txt") as f:
    grid_list = [list(r.strip()) for r in f]

grid = np.array(grid_list, dtype=np.uint8)

print(
    (
        (np.roll(np.maximum.accumulate(grid, axis=0), shift=1, axis=0) < grid)
        | (np.roll(np.maximum.accumulate(grid, axis=1), shift=1, axis=1) < grid)
        | (
            (np.roll(np.maximum.accumulate(grid[::-1,:], axis=0), shift=1, axis=0) < grid[::-1,:])[::-1,:]
            | (np.roll(np.maximum.accumulate(grid[:,::-1], axis=1), shift=1, axis=1) < grid[:,::-1])[:, ::-1]
        )
    )[1:-1, 1:-1].sum()
  + sum(2 * s for s in grid.shape) - 4
)
