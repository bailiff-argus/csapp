int main(void) {
  int     P[5];
  short   Q[2];
  int   **R[9];
  double *S[10];
  short  *T[2];
}

// Array        Element size          Total size           Start address           Element i
//   P               4                    20                    Xp                  Xp + i*4
//   Q               2                     4                    Xq                  Xq + i*2
//   R               8                    72                    Xr                  Xr + i*8
//   S               8                    80                    Xs                  Xs + i*8
//   T               8                    16                    Xt                  Xt + i*8
