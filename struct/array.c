#include <stdio.h>
#include <string.h>
 
struct Books
{
   char  title[50];
   char  author[50];
   char  subject[100];
   int   book_id;
}Book[16];
 
int main( )
{
   int i,j;

   // struct Books Book[16];        // Declare Book[0] of type Books
 
   strcpy( Book[0].title, "C Programming");
   strcpy( Book[0].author, "Nuha Ali"); 
   strcpy( Book[0].subject, "C Programming Tutorial");
   Book[0].book_id = 6495407;

   /* book 2 specification */
   strcpy( Book[1].title, "Telecom Billing");
   strcpy( Book[1].author, "Zara Ali");
   strcpy( Book[1].subject, "Telecom Billing Tutorial");
   Book[1].book_id = 6495700;
 
   // print Book[i] info
   for(i=0;i<2;i++)
   {
      printf( "Book[%d] title : %s\n",i, Book[i].title);
      printf( "Book[%d] author : %s\n",i, Book[i].author);
      printf( "Book[%d] subject : %s\n",i, Book[i].subject);
      printf( "Book[%d] book_id : %d\n\n",i, Book[i].book_id);
   }

   return 0;
}