#include <stdio.h>

int main(void) {

	int a = 270533154;
	char *ptr = (char *) &a;
	
	char *ptr1 = (char *) &a + 0;
	char *ptr2 = (char *) &a + 1;
	char *ptr3 = (char *) &a + 2;
	char *ptr4 = (char *) &a + 3;
	
	
    printf("%p %p %p %p\n", (ptr), (ptr + 1), (ptr + 2), (ptr + 3));
    printf("%d %d %d %d\n", *(ptr), *(ptr + 1), *(ptr + 2), *(ptr + 3));
    
    *(ptr + 2) = 19;
    
	printf("%d %d %d %d\n", *(ptr), *(ptr + 1), *(ptr + 2), *(ptr + 3));
	printf("%d\n", a);
	
	
    printf("\n************************ \n\n");
    
    
    printf("%p %p %p %p\n", ptr1, ptr2, ptr3, ptr4);
    printf("%d %d %d %d\n", *ptr1, *ptr2, *ptr3, *ptr4);
    
    *ptr3 = 25;
    
	printf("%d %d %d %d\n", *ptr1, *ptr2, *ptr3, *ptr4);
	printf("%d\n", a);
	
	
	return 0;
}