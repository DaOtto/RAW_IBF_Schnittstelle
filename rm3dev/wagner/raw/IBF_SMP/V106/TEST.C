/*  */
/*   This program performs a series of tests on a C compiler */
#ifndef PSOS
  #include <string.h>
  #include <stdlib.h>
#endif
#include <stdio.h>
#include "test.h"


/* a function which is define global in this modul
   use it without a strict type deklaration (int, double, char) */
#define max(A,B) ((A) > (B) ? (A) : (B))  

/* the global variable which are declareded in the main modul */
extern char *hallo_main;
extern char *hallo_modul; 
extern char *hallo;

       char array_1[15] = "old world",
            array_2[15] = "new world",
            array_3[15] = "future world",
            *var1       = array_1,
            *var2       = array_2,
            *var3       = array_3;

/* Array with 16 fields*/
void array_test()

{
/*go with the mouse to the symbol to evaluate the array_4 then open
  a window to the array. Now write in the commando-windows
  while 1 then step end
  then press return to see then change in the array_4-windows */
  

   int 	array_4[4][4];
   int 	i,j,
	n = 0,
	a = 0,
	b = 0,
	c = 0,
	d = 0,
	var=0,
	help,
	stop;


   for (i = 0; i < 4; i++)
   {
    for (j = 0; j < 4; j++)
    {
    array_4[i][j] = rand()%100;
    }
   }
   stop = 10;   /* you see unsorted array {5,..6,..34,.....,99}*/

   /* sort an array like bubble-sort */

   for (a = 0; a < 4; a++)
   {
     for (b = 0; b < 4; b++)
     {

       for (c = a; c < 4; c++)
       {
	 if (c == a) var = b;
	 else var = 0;

	 for (d = var; d < 4; d++)
	 {
	 if (array_4[a][b] > array_4[c][d])
	   {
	     help          = array_4[a][b]; /* exchange the numbers */
	     array_4[a][b] = array_4[c][d]; /* to sort the array */
	     array_4[c][d] = help;          /* set breakpoint to look */
	   }
	 }
       }
     }
   }
     stop = 100;  /* see the sorted array */
     stop = 100;
}

void bitfield()
  {

/* Bitfield for a 16 bit length 
   to see the Bitfield on the debugger, take them mem-button
   and select binary for showing bit for bit.
   Then take browse and select Test\bitfield\muster for 16_bit
			       Test\bitfield\bitfield_27 for 27_bit
			       Test\bitfield\muster_cadul	
   Take the step button to see the change in the bitfield. You can
   see how C is using the memory from your system.
*/
   struct {
	    unsigned bit16  : 16;   /* 00000000 00000000 00000000 000 */
	    unsigned bit4   :  4;
	    unsigned bit7   :  7;
	   } bitfield_27[10];


   struct {
	    unsigned field1  : 2;   /* 00000000 00000000 */
	    unsigned field2  : 1;
	    unsigned field3  : 7;
	    unsigned field4  : 4;
	    unsigned field5  : 2;
	   } muster[10];

/* write the Name CAD-UL in the memory with 0 and 1 */
   struct {
	    unsigned field1  : 8;   /* 00000000 */
	    unsigned field2  : 8;
	    unsigned field3  : 8; 
	    unsigned field4  : 8;
	    unsigned field5  : 8;
	    unsigned field6  : 8;   
	    unsigned field7  : 8;
	    unsigned field8  : 8;
	   } muster_cadul[15];


   int stop=10;
   unsigned a=0;

   muster[a].field1  = 0  ;
   muster[a].field2  = 0  ;
   muster[a].field3  = 0  ;
   muster[a].field4  = 0  ;
   muster[a].field5  = 0  ;
			     /* think! by optimizing the code
				you can't see the single steps */ 
   muster[a].field1  = 3  ;    /* 00000011  */
   muster[a].field2  = 1  ;    /* 00000111  */
   muster[a].field3  = 127;    /* 11111111 00000011 */
   muster[a].field4  = 15 ;    /* 11111111 00111111 */
   muster[a].field5  = 3  ;    /* 11111111 11111111 */

   a= 0;
   bitfield_27[a].bit16 =   0;
   bitfield_27[a].bit4  =   0;
   bitfield_27[a].bit7  =   0;
   a= 0;
   bitfield_27[a].bit16 = 170; /* 10101010 00000000*/ 
   bitfield_27[a].bit4  =  16;  
   bitfield_27[a].bit7  =  44;
   a=1;
   bitfield_27[a].bit16 = 170; /* 10101010 00000000*/
   bitfield_27[a].bit4  =  16;
   bitfield_27[a].bit7  =  44;

   for(a = 0 ; a <= 14 ; a++)
   {
   muster_cadul[a].field1  =   0;
   muster_cadul[a].field2  =   0;
   muster_cadul[a].field3  =   0;
   muster_cadul[a].field4  =   0;
   muster_cadul[a].field5  =   0;
   muster_cadul[a].field6  =   0;
   muster_cadul[a].field7  =   0;
   muster_cadul[a].field8  =   0;
   }

/* write cad-ul in the to memory show muster_cadul with binary and 150 bits */ 
   a=0;
   muster_cadul[a].field1  =  15;
   muster_cadul[a].field2  = 126;
   muster_cadul[a].field3  = 252;
   muster_cadul[a].field4  =   0;
   muster_cadul[a].field5  = 195;
   muster_cadul[a].field6  = 192;
   muster_cadul[a].field7  = 255;
   muster_cadul[a].field8  = 255;
   a=1;
   muster_cadul[a].field1  =  31;
   muster_cadul[a].field2  = 255;
   muster_cadul[a].field3  = 254;
   muster_cadul[a].field4  =   0;
   muster_cadul[a].field5  = 195;
   muster_cadul[a].field6  = 192;
   muster_cadul[a].field7  = 255;
   muster_cadul[a].field8  = 255;
   a=2;
   muster_cadul[a].field1  =  48;
   muster_cadul[a].field2  = 195;
   muster_cadul[a].field3  = 195;
   muster_cadul[a].field4  =   0;
   muster_cadul[a].field5  = 195;
   muster_cadul[a].field6  = 192;
   muster_cadul[a].field7  = 255;
   muster_cadul[a].field8  = 255;
   a=3;
   muster_cadul[a].field1  =  96;
   muster_cadul[a].field2  = 195;
   muster_cadul[a].field3  = 195;
   muster_cadul[a].field4  =   0;
   muster_cadul[a].field5  = 195;
   muster_cadul[a].field6  = 192;
   muster_cadul[a].field7  = 255;
   muster_cadul[a].field8  = 255;
   a=4;
   muster_cadul[a].field1  = 192;
   muster_cadul[a].field2  = 195;
   muster_cadul[a].field3  = 195;
   muster_cadul[a].field4  =   0;
   muster_cadul[a].field5  = 195;
   muster_cadul[a].field6  = 192;
   muster_cadul[a].field7  = 255;
   muster_cadul[a].field8  = 199;
   a=5;
   muster_cadul[a].field1  = 192;
   muster_cadul[a].field2  = 255;
   muster_cadul[a].field3  = 195;
   muster_cadul[a].field4  = 255;
   muster_cadul[a].field5  = 195;
   muster_cadul[a].field6  = 192;
   muster_cadul[a].field7  = 255;
   muster_cadul[a].field8  = 199;
   a=6;
   muster_cadul[a].field1  =  96;
   muster_cadul[a].field2  = 255;
   muster_cadul[a].field3  = 195;
   muster_cadul[a].field4  = 255;
   muster_cadul[a].field5  = 195;
   muster_cadul[a].field6  = 192;
   muster_cadul[a].field7  = 255;
   muster_cadul[a].field8  = 199;
   a=7;
   muster_cadul[a].field1  =  48;
   muster_cadul[a].field2  = 195;
   muster_cadul[a].field3  = 199;
   muster_cadul[a].field4  =   0;
   muster_cadul[a].field5  = 195;
   muster_cadul[a].field6  = 192;
   muster_cadul[a].field7  = 255;
   muster_cadul[a].field8  = 255;
   a=8;
   muster_cadul[a].field1  =  31;
   muster_cadul[a].field2  = 195;
   muster_cadul[a].field3  = 254;
   muster_cadul[a].field4  =   0;
   muster_cadul[a].field5  = 255;
   muster_cadul[a].field6  = 255;
   muster_cadul[a].field7  = 255;
   muster_cadul[a].field8  = 254;
   a=9;
   muster_cadul[a].field1  =  15;
   muster_cadul[a].field2  = 195;
   muster_cadul[a].field3  = 252;
   muster_cadul[a].field4  =   0;
   muster_cadul[a].field5  = 255;
   muster_cadul[a].field6  = 255;
   muster_cadul[a].field7  = 255;
   muster_cadul[a].field8  = 252;

   a=10;
   muster_cadul[a].field1  =   0;
   muster_cadul[a].field2  =   0;
   muster_cadul[a].field3  =   0;
   muster_cadul[a].field4  =   0;
   muster_cadul[a].field5  =   0;
   muster_cadul[a].field6  =   0;
   muster_cadul[a].field7  =   0;
   muster_cadul[a].field8  =   0;

   stop = 100;
   stop = 100;
  }



 
void dec_oct_hex_test()
{

   int stop;
   short int d[20], 
	     o[20],
	     x[20];


   d[0]  = 0;                o[0] = 00;               x[0] = 0x0;
   d[1]  = 1;                o[1] = 01;               x[1] = 0x1;
   d[2]  = 2;                o[2] = 02;               x[2] = 0x2;
   d[3]  = 3;                o[3] = 03;               x[3] = 0x3;
   d[4]  = 4;                o[4] = 04;               x[4] = 0x4;
   d[5]  = 5;                o[5] = 05;               x[5] = 0x5;
   d[6]  = 6;                o[6] = 06;               x[6] = 0x6;
   d[7]  = 7;                o[7] = 07;               x[7] = 0x7;
   d[8]  = 8;                o[8] = 010;              x[8] = 0x8;
   d[9]  = 9;                o[9] = 011;              x[9] = 0x9;
   d[10] = 10;              o[10] = 012;             x[10] = 0xa;
   d[11] = 11;              o[11] = 013;             x[11] = 0xb;
   d[12] = 12;              o[12] = 014;             x[12] = 0xc;
   d[13] = 13;              o[13] = 015;             x[13] = 0xd;
   d[14] = 14;              o[14] = 016;             x[14] = 0xe;
   d[15] = 15;              o[15] = 017;             x[15] = 0xf;
   d[16] = 16;              o[16] = 020;             x[16] = 0x10;
   d[17] = 63;              o[17] = 077;             x[17] = 0x3f;
   d[18] = 64;              o[18] = 0100;            x[18] = 0x40;
   d[19] = 255;             o[19] = 0377;            x[19] = 0xff;
   
   /* see an overflow   d[19] */
   d[19] = o[19] * x[19];  /* short int */

   /* the result 2 is not corret for a math-professor */ 
   d[19] = d[19] + 513;

   stop = 100;

}


void array_of_double()

{
   /* Unfortunately, there's not a lot we can do with floating constants.
      We can check to see that the various representations can be com-
      piled, that the conversion is such that they yield the same hard-
      ware representations in all cases, and that all representations
      thus checked are double precision.              */


   int stop;
   double a[8];

   a[0] = .1250E+04;
   a[1] = 1.250E3;
   a[2] = 12.50E02;
   a[3] = 125.0e+1;
   a[4] = 1250e00;
   a[5] = 12500.e-01;
   a[6] = 125000e-2;
   a[7] = 1250.;

   stop =100;

}


void string_test()
  {
   int stop,i, maxlen = 60;
   char *s,
        *s1,
        true[20]        = "true",
        false[20]       = "false",
        string_s[20]    = "string",
	string_array[20]= "hallo"; 
   char s_array;

   /* A string is a sequence of characters surrounded by double
      quotes, as in "...".                         */

   s  = string_s;
   s1 = string_array;

   /* A string has type "array of characters" and storage class
      static and is initialized with the given characters.  */

   s = "CAD-UL Germany";
   if(    s[0] == 'C'
       || s[1] == 'A'
       || s[2] == 'D'
       || s[3] == '-'
       || s[4] == 'U'
       || s[5] == 'L')
     {                          
       s = true;
     }
     else
     {
       s = false;
     }
       s_array = s[0];
       s_array = s[1];
       s_array = s[2];
       s_array = s[3];
       s_array = s[4];

/* copy the string from s to string_array */

       strcpy(s1,s);

       stop = 100;

  }



void call_by_reference(char **name)
  {   

/* see the change from 'name' in the main function check() */

     int Nullnix;
 
     int choice=2,
	 stop;

   switch (choice) {
			case 1   : *name =   var1;
			break ;
			case 2   : *name =   var2;
			break;
			case 3   : *name =   var3;
			break;
		    }
    stop = 100;
  }

void call_by_reference_1(char *name)
  {   

/* see the change from 'name' in the main function check() */

     int choice=3, 
	 stop;
     char array_1[15] = "old world",
          array_2[15] = "new world",
          array_3[15] = "future world",
          *local1     = array_1,
          *local2     = array_2,
          *local3     = array_3;

   switch (choice) {
			case 1   : strcpy(name,local1);
			break;
			case 2   : strcpy(name,local2);
			break;
			case 3   : strcpy(name,local3);
			break;
		    }
    stop = 100;
  }

void call_by_value(char *name)
  {   

/* the variable 'name' is not change in the main function check() */

     int choice=2,
         stop;
     char array_1[15] = "old world",
          array_2[15] = "new world",
          array_3[15] = "future world",
          *var1       = array_1,
          *var2       = array_2,
          *var3       = array_3;

   switch (choice) {
			case 1   : name =  var1;
			break ;
			case 2   : name =  var2;
			break;
			case 3   : name =  var3;
			break;
		    }
   stop = 100;
  }

void register_test()
  {
    int stop;
    register int i;
    register char reg_char='a';
    char reg_string[10];
    for (i = 0;i <= 10;i++) 
    {
      reg_string[i] = reg_char;
      stop = 100; 
    }
  }

/* make a new type with the enum construct */
void enum_day_test()
  {

    enum days {monday,tuesday,wednesday,thursday,friday,saturday,sunday};
    enum days week_days;
    char *string_days;
    int  i, 
	 stop;

    for (week_days = monday ; week_days <= sunday ; week_days++) 
       { 
     switch(week_days) 
         {
             case monday:  string_days = "monday";
                           break;
            case tuesday:  string_days = "tuesday";
                           break;
          case wednesday:  string_days = "wednesday";
                           break;
           case thursday:  string_days = "thursday";
                           break;
             case friday:  string_days = "friday";
                           break;
           case saturday:  string_days = "saturday";
                           break;
             case sunday:  string_days = "sunday";
                           break;
              week_days++; 
         }                
       }
    stop = 100;
  }

/* function which is define, you can use it with all types */
void define_max()
  {
    int stop, int_number1, int_number2, int_result;
    float float_number1=0.0, float_number2=0.0, float_result=0.0;

    int_number1   = 12;
    int_number2   = 22;
    float_number1 = 25.25;
    float_number2 = 15.15;
    int_result    = max(int_number1,int_number2);
    float_result  = max(float_number1,float_number2);

    stop =100;
  }


/* function for the diffrence between the global or local variables */

void extern_variable_test()
  { 
    char *variable_hallo, 
	 *variable_hallo_main,
	 *variable_hallo_modul;
    int   stop; 
    
    hallo_modul          = "in modul test.c"; 
    hallo                = "function variable_test";
    variable_hallo       = hallo;
    variable_hallo_modul = hallo_modul;
    variable_hallo_main  = hallo_main;
   
    stop = 100;

  }


void function_depth_1(char *sentence)
  {
    int   stop; 
    char *word = " Hallo user !";  

    strcpy(sentence,word);
    function_depth_2(sentence);
  }


void function_depth_2(char *sentence)
  {
    int   stop; 
    char *word = " Isn't it";  

    strcat(sentence,word);
    function_depth_3(sentence);
  }




void function_depth_3(char *sentence)
  {
    int   stop; 
    char *word = " beautiful";  

    strcat(sentence,word);
    function_depth_4(sentence);
  }




void function_depth_4(char *sentence)
  {
    int   stop; 
    char *word = " to work";  

    strcat(sentence,word);
    function_depth_5(sentence);
  }




void function_depth_5(char *sentence)
  {
    int   stop; 
    char *word  = " with the Organon XDB",
	 *empty = "                                                           ";  

    strcat(sentence,word);
    stop = 100;
    strcpy(sentence,empty);
  }

