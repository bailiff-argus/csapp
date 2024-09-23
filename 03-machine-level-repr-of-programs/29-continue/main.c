int main(void) {
  long sum = 0;
  long i;

  for (i = 0; i < 10; i++) {
    if (i & 1)
      continue;
    sum += i;
  }

  return 0;
}

int main_goto(void) {
  long sum = 0;
  long i;

  i = 0;
loop:
  if (i & 1)
    goto update;

  sum += i;

update:
  i++;

test:
  if (i < 10)
    goto loop;

  return 0;
}
