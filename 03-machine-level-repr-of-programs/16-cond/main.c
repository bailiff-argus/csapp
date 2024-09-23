void cond(short a, short *p) {
  if (a && *p < a)
    *p = a;
}

// 0000000000000000 <cond>:
//    0:   66 85 ff                test   %di,%di
//    3:   74 08                   je     d <cond+0xd>
//    5:   66 39 3e                cmp    %di,(%rsi)
//    8:   7d 03                   jge    d <cond+0xd>
//    a:   66 89 3e                mov    %di,(%rsi)
//    d:   c3                      ret

// A. goto-code version

void cond_goto(short a, short *p) {
  if (!a)
    goto exit;
  if (*p >= a)
    goto exit;
  *p = a;
exit:
  return;
}

// B. The code contains two conditional branches, because there are actually two
// conditions to check in the c version, and either of them being false would
// mean both are false
