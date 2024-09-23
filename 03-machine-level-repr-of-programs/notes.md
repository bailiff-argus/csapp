# Loop translation methods

## Do-While:

```c
do {
    body_statement;
} while (test_expression);
```

Structure in assembly:

```
loop:
  body-statements
  test-expr
  cond-jump loop
```

## While

```c
while (test_expression) {
    body_statement;
}
```

*Jump to middle* is a do-while with unconditional jump straight into test:

```
  jmp test
loop:
  body-statements
test:
  test-expr
  cond-jump loop
```

*Guarded do* is a do-while with skipping over the loop if a test fails:

```
  test-expr
  cond-jump done
loop:
  body-statements
  test-expr
  cond-jump loop
done:
```

## For

```c
for (init_expression; test_expression; update_expression) {
    body_statement;
}

// is equivalent to

init_expression;
while (test_expression) {
    body_statement;
    update_expression;
}
```

*Jump to middle* for:

```
  init-expr
  jmp test
loop:
  body-statements
  update-expression
test:
  test-expr
  cond-jump loop
```

*Guarded do* for:
```
  test-expr
  cond-jump done
  init-expr
loop:
  body-statements
  update-expr
  test-expr
  cond-jump loop
done:
```

# Switch statement

Idea: a jump table, i.e. an array of pointers to instructions that you map the input to.

```c
void *jmp_table[] = {
    &&loc_A,   // 101
    &&loc_def, // 102
    &&loc_def, // 103
    &&loc_B, // 104
    &&loc_C, // 105
    &&loc_D, // 106
    &&loc_def, // 107
    &&loc_E, // 108
}

unsigned long idx = val - 101;
if (idx > 7) goto loc_def;
goto *jmp_table[idx];

switch (val):
loc_A:   case 101: /* ... */ break;
loc_B:   case 104: /* ... */ break;
loc_C:   case 105: /* ... */ break;
loc_D:   case 106: /* ... */ break;
loc_E:   case 108: /* ... */ break;
loc_def: default:  /* ... */
```
