#include <stdio.h>
typedef enum  {sunday, monday, tuesday, wednesday, thursday, friday, saturday} day_t ;

int main()
{
    day_t d = thursday;
    printf("The day number stored in d is %d\n", d);
    return 0;
}