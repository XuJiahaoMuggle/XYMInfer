import os
import numpy as np
from pathlib import Path
from typing import *

DATA_PATH = Path(__file__).resolve().parents[1] / "data"

def generateData(m: int, n: int, k: int) -> None:
  a = np.random.randn(m, k).astype(np.float32)
  b = np.random.randn(k, n).astype(np.float32)
  c = np.random.randn(m, n).astype(np.float32)
  data_path = str(DATA_PATH)
  save_paths = [os.path.join(data_path, each) for each in ['a.bin', 'b.bin', 'c.bin']]
  for data, save_path in zip([a, b, c], save_paths):
    with open(save_path, 'wb') as f:
      data.tofile(f)


def loadData(m: int, n: int, k: int) -> List[np.ndarray]:
  data_path = str(DATA_PATH)
  ret = []
  shapes = [[m, k], [k, n], [m, n]]
  save_paths = [os.path.join(data_path, each) for each in ['a.bin', 'b.bin', 'c.bin']]
  for shape, save_path in zip(shapes, save_paths):
    ret.append(np.fromfile(save_path, dtype=np.float32).reshape(shape))
  return ret


if __name__ == "__main__":
  m, n, k = 100, 80, 60
  generateData(m, n, k)
  a, b, c = loadData(m, n, k)
  res = a @ b + c
