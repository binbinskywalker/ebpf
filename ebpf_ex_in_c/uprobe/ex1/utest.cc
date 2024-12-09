#include <stdio.h>
#include <unistd.h>
#include <iostream>


int utest_add(int a, int b)
{
    return a + b;
}

int utest_sub(int a, int b)
{
    return a - b;
}

int main()
{
   int err;

   for(int i = 0; ;i++)
   {
       utest_add(i, i+1);

       utest_sub(i*i,i);

       std::cout << "i = " << i << std::endl;
       sleep(1);
   }
}
