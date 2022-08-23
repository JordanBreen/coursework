/**/

#include <stdio.h>
#include <stdlib.h>

void shitty_swap(int x, int y);
void proper_swap(int *px, int *py);

int main(int argc, char *argv[])
{
  char *prog = argv[0];
  
  if(argc == 2){
    fprintf(stderr, "%s: Invalid number of arguments, was expecting (int x, int y)\n", prog);
    exit(1);
  } else {
    
    int x = 0,
        y = 0,
        vals[2];
    
    if((x = atoi(argv[1])) == 0){
      fprintf(stderr, "%s: Invalid argument type in argv[1], was expecting type (int)\n", prog);
      exit(1);
    } else
      vals[0] = x;
    
    if((y = atoi(argv[2])) == 0){
      fprintf(stderr, "%s: Invalid argument type in argv[2], was expecting type (int)\n", prog);
      exit(1);
    } else
      vals[1] = y;
    
    printf("////////////////////////////////////////////////\n");
    printf("//           - Welcome to Swapper! -          //\n");
    printf("////////////////////////////////////////////////\n");
    printf("//   Values Entered:\n");
    printf("//     x = %d\n", x);
    printf("//     y = %d\n", y);
    printf("//   Values Entered: (as array)\n");
    printf("//     [%d, %d]\n", vals[0], vals[1]);
    printf("////////////////////////////////////////////////\n");
    printf("// Performing shitty_swap(int x, int y)...\n");     shitty_swap(x, y);
    printf("//   Values after shitty_swap(x, y)\n");
    printf("//     x = %d\n", x);
    printf("//     y = %d\n", y);
    printf("//----------------------------------------------\n");
    printf("// Performing proper_swap(int *px, int *py)...\n"); proper_swap(&x, &y);
    printf("//   Values after proper_swap(&x, &y)\n");
    printf("//     x = %d\n", x);
    printf("//     y = %d\n", y);
    printf("//----------------------------------------------\n");
    printf("// Performing shitty_swap(int x, int y)...\n");     shitty_swap(vals[0], vals[1]);
    printf("//   Array after shitty_swap(vals[0], vals[1])\n");
    printf("//     [%d, %d]\n", vals[0], vals[1]);
    printf("//\n");
    printf("//-----------------------------------------------\n");
    printf("// Performing proper_swap(int *px, int *py)...\n"); proper_swap(&vals[0], &vals[1]);
    printf("//   Array after proper_swap(&vals[0], &vals[1])\n");
    printf("//     [%d, %d]\n", vals[0], vals[1]);
    printf("//\n");
    printf("/////////////////////////////////////////////////\n");



    return 0;
  }
}

void shitty_swap(int x, int y)
{
  int temp;
  
  temp = x;
  x    = y;
  y    = temp;
}

void proper_swap(int *px, int *py)
{
  int temp;

  temp = *px;
  *px  = *py;
  *py  = temp;
}
