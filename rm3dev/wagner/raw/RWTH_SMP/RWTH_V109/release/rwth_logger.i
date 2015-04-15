#line 1 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\source\\rwth_logger.cpp"
#line 1 "c:\\rm3dev\\inc\\setjmp.h"






















 




#line 1 "c:\\rm3dev\\inc\\prot.h"























 




#line 35 "c:\\rm3dev\\inc\\prot.h"

#line 30 "c:\\rm3dev\\inc\\setjmp.h"
#line 1 "c:\\rm3dev\\inc\\rmcomp.h"





















 






            
#line 38 "c:\\rm3dev\\inc\\rmcomp.h"



            
            











#line 61 "c:\\rm3dev\\inc\\rmcomp.h"

#line 69 "c:\\rm3dev\\inc\\rmcomp.h"












#line 131 "c:\\rm3dev\\inc\\rmcomp.h"


#line 179 "c:\\rm3dev\\inc\\rmcomp.h"


#line 33 "c:\\rm3dev\\inc\\setjmp.h"



            
            
#pragma fixedparams ( "setjmp", "longjmp")

#pragma align (_jmp_buf = 4)

















 
typedef struct _jmp_buf {
    unsigned    esp;
    unsigned    ss;
    unsigned    eflag;
    unsigned    cs;
    unsigned    eip;
    unsigned    ebp;





    unsigned    edi;
    unsigned    es;
    unsigned    esi;
    unsigned    ds;




}   jmp_buf[1];
#line 95 "c:\\rm3dev\\inc\\setjmp.h"



extern "C" {


extern void  far longjmp (jmp_buf env, int val);
extern int   far setjmp  (jmp_buf env);


}













#line 1 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\source\\rwth_logger.cpp"













 




 
 
 
 
 
#line 1 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\rmos_inc.h"













 




 





#line 1 "c:\\rm3dev\\inc\\stdio.h"





















 









            
            
#pragma fixedparams("fopen","fduopen", "freopen", "tmpfile", "ftell", "rewind")
#pragma fixedparams("setbuf", "fread", "fwrite", "fgetc", "ungetc")
#pragma fixedparams("fseek", "fflush", "setvbuf", "fclose", "fgetpos")
#pragma fixedparams("fsetpos", "_getc", "_putc", "puts", "fputs", "fputc")
#pragma fixedparams("putw", "rename", "remove", "gets", "fgets", "tmpnam")
#pragma fixedparams("_xstream", "getw", "fdureopen")
#pragma varparams("fprintf", "fscanf", "printf", "scanf", "sprintf", "sscanf")
#pragma varparams("vprintf", "vfprintf", "vsprintf")
#pragma varparams("perror")
#pragma varparams("x_cr_flushall")



#line 1 "c:\\rm3dev\\inc\\stddef.h"





















 












extern "C" {




 
typedef	unsigned amap_t;		 
typedef	unsigned aold_t;		 
typedef unsigned bmap_t;		 
typedef unsigned bold_t;		 
typedef unsigned cmap_t;		 
typedef unsigned cold_t;		 
typedef unsigned dmap_t;		 
typedef unsigned dold_t;		 



 
typedef	unsigned comp_t;		 
typedef	long	 daddr_t;		 
typedef unsigned dev_t;			 
typedef unsigned ino_t;			 
typedef long	 paddr_t;		 
typedef unsigned saddr_t;		 

typedef int 	 sig_t;			 




#line 71 "c:\\rm3dev\\inc\\stddef.h"
typedef unsigned int size_t;		 




 
#line 84 "c:\\rm3dev\\inc\\stddef.h"
 
typedef int	 ptrdiff_t;		 









typedef unsigned int vaddr_t;
typedef	unsigned int uaddr_t;		 











 
#line 124 "c:\\rm3dev\\inc\\stddef.h"


}



#line 49 "c:\\rm3dev\\inc\\stdio.h"
#line 1 "c:\\rm3dev\\inc\\stdarg.h"





















 




#line 33 "c:\\rm3dev\\inc\\stdarg.h"



typedef char *va_list;



 
#line 51 "c:\\rm3dev\\inc\\stdarg.h"

#line 52 "c:\\rm3dev\\inc\\stdio.h"
#line 1 "c:\\rm3dev\\inc\\stdiodep.h"






















 













 




#pragma align (_fid_t  = 4)
#pragma align (_modetb = 4)














 
typedef struct _fid_t {
       int              fildes;      
       char             *fname;      



       } fid_t;


 
struct _modetb {
       int              sysflag;    
       char             *usermode; 
 



       int              strmflag;  
 
       };











 
typedef long fpos_t;

#line 55 "c:\\rm3dev\\inc\\stdio.h"



 








 


#pragma align (_file = 4)













typedef struct _file {
    size_t         _cnt;        
 
    unsigned char  *_bufpos;     



    unsigned char  *_bufbas;     



    unsigned char  *_bufungetc;  



    int            _flag;        
    size_t         _bufsiz;      
    fid_t          _fid;         
    int            device;      
 
    int            unit;         
} FILE;














 




















 
#line 153 "c:\\rm3dev\\inc\\stdio.h"

#line 163 "c:\\rm3dev\\inc\\stdio.h"











 






extern "C" {


extern int     far fclose    (FILE *stream);
extern FILE *  far fduopen   (unsigned int device, unsigned int unit, const char *mode);
extern FILE *  far fdureopen (unsigned device, unsigned unit, const char *mode, FILE *ostream);
extern int     far fflush    (FILE *stream);
extern int     far fgetc     (FILE *stream);
extern int     far fgetpos   (FILE *stream, fpos_t *pos);
extern char *  far fgets     (char *s, int n, FILE *stream);
extern FILE *  far fopen     (const char *filename, const char *mode);
extern int       far fprintf   (FILE *stream, const char *fmtstr,...);
extern int     far fputc     (int c, FILE *stream);
extern int     far fputs     (const char *s, FILE *stream);
extern size_t  far fread     (void *ptr, size_t size, size_t nmemb, FILE *stream);
extern FILE *  far freopen   (const char *filename, const char *mode, FILE *stream);
extern int       far fscanf    (FILE *stream, const char *fmtptr,...);
extern int     far fseek     (FILE *stream, long offset, int ptofref);
extern int     far fsetpos   (FILE *stream, const fpos_t *pos);
extern long    far ftell     (FILE *stream);
extern size_t  far fwrite    (const void *ptr, size_t size, size_t nmemb, FILE *stream);
extern char *  far gets      (char *s);
extern int     far getw      (FILE *stream);
extern void      far perror    (const char *s);
extern int       far printf    (const char *fmtstr,...);
extern int     far puts      (const char *s);
extern int     far putw      (int w, FILE *stream);
extern int     far remove    (const char *filename);
extern int     far rename    (const char *oldname, const char *newname);
extern void    far rewind    (FILE *stream);
extern int       far scanf     (const char *fmtstr,...);
extern void    far setbuf    (FILE *stream, char *buf);
extern int     far setvbuf   (FILE *stream, char *buf, int mode, size_t size);
extern int       far sprintf   (char *s, const char *fmtstr,...);
extern int       far sscanf    (const char *s, const char *fmtptr,...);
extern FILE *  far tmpfile   (void );
extern char *  far tmpnam    (char *s);
extern int     far ungetc    (int c, FILE *stream);
extern int       far vfprintf  (FILE *stream, const char *fmtstr, va_list ap);
extern int       far vprintf   (const char *fmtstr, va_list ap);
extern int       far vsprintf  (char *s, const char *fmtstr, va_list ap);
extern int     far _getc     (FILE *stream);
extern int     far _putc     (unsigned char c, FILE *stream);
extern FILE *  far _xstream  (int);
extern int       far x_cr_flushall (void);


}


#line 26 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\rmos_inc.h"
#line 1 "c:\\rm3dev\\inc\\stdlib.h"





















 









            
            
#pragma fixedparams("atof", "atoi", "atol", "strtod", "strtol")
#pragma fixedparams("strtoul", "rand", "srand", "abort", "atexit")
#pragma fixedparams("exit", "qsort", "x_abs", "div")
#pragma fixedparams("labs", "ldiv", "bsearch" )
#pragma fixedparams("putenv", "getenv")

#pragma align (_div_t  = 4)
#pragma align (_ldiv_t = 4)





























typedef struct _div_t  { int quot;  
                         int rem;   
                       } div_t;
typedef struct _ldiv_t { long quot;  
                         long rem;   
                       } ldiv_t;



extern "C" {


extern void           far abort   (void);
extern int            far atexit  (void ( far * func) (void));
extern double         far atof    (const char *nptr);
extern int            far atoi    (const char *nptr);
extern long           far atol    (const char *nptr);
extern void *         far bsearch (const void *key, const void *base,
                                          size_t nel, size_t width,
                                          int ( far *compar)
                                          (const void *p0, const void *p1));

extern div_t          far div     (int numer, int denom);




extern void           far exit    (int status);
extern char *         far getenv  (const char *name);
extern long           far labs    (long j);
extern ldiv_t         far ldiv    (long numer, long denom);
extern int            far putenv  (const char *name);
extern void           far qsort   (void *base, size_t nel, size_t width,
                                          int ( far *compar)
                                          (const void *p0, const void *p1));
extern int            far rand    (void);
extern void           far srand   (unsigned int seed);
extern double         far strtod  (const char *nptr, char **endptr);
extern long           far strtol  (const char *nptr, char **endptr, int base);
extern unsigned long  far strtoul (const char *nptr, char **endptr, int base);
extern int            far x_abs   (int j);



}












#line 1 "c:\\rm3dev\\inc\\malloc.h"





















 




#line 33 "c:\\rm3dev\\inc\\malloc.h"


            
            
#pragma fixedparams("malloc", "realloc", "calloc", "free", "x_cr_lmalloc" )




extern "C" {


extern void *  far calloc       (size_t nmemb, size_t size);
extern void    far free         (void *ptr);
extern void *  far malloc       (size_t size);
extern void *  far realloc      (void *ptr, size_t size);

extern void *  far x_cr_lmalloc (unsigned long size);


}



#line 130 "c:\\rm3dev\\inc\\stdlib.h"


#line 27 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\rmos_inc.h"
#line 1 "c:\\rm3dev\\incplus\\exception.h"
 


 



 




  


 
#line 28 "c:\\rm3dev\\incplus\\exception.h"

#pragma noarguments_in_registers(push)

#line 1 "c:\\rm3dev\\incplus\\stdexcept.h"
 


 



#pragma noarguments_in_registers(push)

 


  


 
#line 31 "c:\\rm3dev\\incplus\\stdexcept.h"

#line 1 "c:\\rm3dev\\incplus\\libcxx.h"











 





#pragma noarguments_in_registers(push)

extern	"C" {

 




#pragma	align	(__user_cxxtls=4)

struct	__user_cxxtls	{
	 
	long				__magic_number1;
	int				__eh_curr_region;
	int				__catch_clause_number;
	

 
	void	*			__curr_eh_stack_entry;	
	void	*			__caught_object_address;
	


 
	};
extern	__user_cxxtls	*	__cxxtls;

 
#line 58 "c:\\rm3dev\\incplus\\libcxx.h"




 



 
extern	void 	__cxx_tls_free_hook(void *,bool);
extern	void *	__cxx_tls_alloc_hook(size_t,bool);
extern	void 	__cxx_tls_delete_hook(void *);
extern	void 	__cxx_tls_delete_root_hook(void *);
extern	void 	__cxx_tls_set_hook(void *,int *);
extern	struct __user_cxxtls* 
			__cxx_tls_get_hook(void);
extern	int 	__cxx_tls_init_hook(void *);
extern	int 	__cxx_tls_exit_hook(void);



 
extern	size_t 	__cxx_tls_size(void);
extern	void 	__cxx_tls_init(void *,void *,void *,void *);
extern	void* 	__cxx_tls_set(void *,int *);
extern	void 	__cxx_tls_delete(void);
extern	void* 	__cxx_tls_get_root(void);
extern	void 	__cxx_tls_free_hook(void *,bool);



 






 
typedef	unsigned long	_IOS_SEM;	 

extern	"C"	void	__cadul_enter_critical_section(void *);
extern	"C"	void	__cadul_exit_critical_section(void *);
extern	"C"	void	__cadul_enable_critical_section_lock(void *);
extern	"C"	void	__cadul_disable_critical_section_lock(void *);
extern	"C"	void	__cadul_share_critical_section_lock(void *,void *);

}

#pragma arguments_in_registers(pop)



#line 33 "c:\\rm3dev\\incplus\\stdexcept.h"
class	exception;
typedef void ( * raise_hanlder)(const exception&);

extern	raise_hanlder	_Raise_handler;













#pragma	align	(exception=4)		

  class exception {
  public:
    static raise_hanlder  _Set_raise_handler(raise_hanlder);

    explicit exception(const char *message = "unknown") throw();

    exception(const exception& copyfrom) throw();

    exception&  operator=(const exception& copyfrom) throw();

    virtual ~exception() throw();

    virtual const char*  what() const throw();

    void  _Raise(void) const;
  protected:

    void _Doraise() const
                {}

    const char *_message;
  };
#line 84 "c:\\rm3dev\\incplus\\stdexcept.h"



#pragma arguments_in_registers(pop)



#line 32 "c:\\rm3dev\\incplus\\exception.h"





  

 

  typedef bool _bool;









#pragma       align(bad_exception=4)	

  class bad_exception : public exception {
  public:
    bad_exception(const char *message = "bad exception") throw();
	
    bad_exception(const bad_exception& copyfrom) throw();

    bad_exception&  operator=(const bad_exception& copyfrom)
							throw();
    virtual ~bad_exception() throw();
    virtual const char*  what() const throw();
  };

  typedef void ( *terminate_handler)();
  extern terminate_handler set_terminate(terminate_handler);

  typedef void ( *unexpected_handler)();
  extern unexpected_handler set_unexpected(unexpected_handler);

  
 
  void  terminate();
  void  unexpected();

  extern _bool uncaught_exception();

#line 88 "c:\\rm3dev\\incplus\\exception.h"





#pragma arguments_in_registers(pop)



#line 28 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\rmos_inc.h"
#line 1 "c:\\rm3dev\\inc\\new.h"
 


 






#pragma noarguments_in_registers(push)

#line 38 "c:\\rm3dev\\inc\\new.h"

typedef unsigned int size_t;		 



 
#line 50 "c:\\rm3dev\\inc\\new.h"






  


 
#line 71 "c:\\rm3dev\\inc\\new.h"

 







#pragma	align(bad_alloc=4)	

  class bad_alloc : public exception {
  public:
    bad_alloc(const char *message = "bad_allocation") throw();

    bad_alloc(const bad_alloc& copyfrom) throw();

    bad_alloc&  operator=(const bad_alloc& copyfrom) throw();

    virtual ~bad_alloc() throw();

    virtual const char*  what() const throw();
  };



  typedef void ( * new_handler)();
  new_handler set_new_handler(new_handler);
  struct nothrow_t { };
  
  
  const nothrow_t nothrow = {};

#line 114 "c:\\rm3dev\\inc\\new.h"



 
void *operator new(size_t) throw(::bad_alloc);



 
void *operator new(size_t, const ::nothrow_t&) throw();




 
void *operator new(size_t, void*) throw();



 

void operator delete(void*, void*);





 
void *operator new[](size_t) throw(::bad_alloc);



 
void *operator new[](size_t, void*) throw();



 

void operator delete[](void*, void*);




 
void *operator new[](size_t,
                     const ::nothrow_t&) throw();


#pragma arguments_in_registers(pop)

#line 29 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\rmos_inc.h"
#line 1 "c:\\rm3dev\\incplus\\typeinfo.h"
 


 



#pragma noarguments_in_registers(push)







  

 

  typedef bool _bool;




  


 
#line 40 "c:\\rm3dev\\incplus\\typeinfo.h"

 







 
#pragma define_type_info



#pragma	align(type_info=4)		

  class type_info {
  public:
    virtual ~type_info();
    _bool  operator==(const type_info&) const;
    _bool  operator!=(const type_info&) const;
    _bool  before(const type_info&) const;
    const char*  name() const;
  private:
    type_info&  operator=(const type_info&);  


  protected:
    
    

    type_info(const type_info&);  
  };





#pragma	align(bad_cast=4)		

  class bad_cast : public exception {
  public:
    bad_cast(const char *message = "bad cast") throw();
    bad_cast(const bad_cast&) throw();
    bad_cast&  operator=(const bad_cast&) throw();
    virtual ~bad_cast() throw();
    virtual const char*  what() const throw();
  };





#pragma	align(bad_typeid=4)		

  class bad_typeid : public exception {
  public:
    bad_typeid(const char *message = "bad typeid") throw();
    bad_typeid(const bad_typeid&) throw();
    bad_typeid&  operator=(const bad_typeid&) throw();
    virtual ~bad_typeid() throw();
    virtual const char*  what() const throw();
  };

#line 114 "c:\\rm3dev\\incplus\\typeinfo.h"

#pragma arguments_in_registers(pop)

#line 30 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\rmos_inc.h"
#line 1 "c:\\rm3dev\\incplus\\iostream.h"
 



















  





#pragma noarguments_in_registers(push)

#line 1 "c:\\rm3dev\\incplus\\istream"
 



















  





#pragma noarguments_in_registers(push)

#line 1 "c:\\rm3dev\\incplus\\ostream"
 



















  





#pragma noarguments_in_registers(push)

#line 1 "c:\\rm3dev\\incplus\\ios"
 



















  





#pragma noarguments_in_registers(push)

#line 1 "c:\\rm3dev\\incplus\\xstddef"
 



















  





#pragma noarguments_in_registers(push)

#line 1 "c:\\rm3dev\\incplus\\yvals.h"
 



















  

 



#pragma noarguments_in_registers(push)


#line 37 "c:\\rm3dev\\incplus\\yvals.h"

 




		 
#line 60 "c:\\rm3dev\\incplus\\yvals.h"

		 

typedef bool _Bool;

		 



		 






		 
#line 87 "c:\\rm3dev\\incplus\\yvals.h"
		



		



 




#line 108 "c:\\rm3dev\\incplus\\yvals.h"
 

class _Lockit
	{	
public:
	explicit _Lockit(int kind ,_IOS_SEM *sem)
		{
		




 
		if(kind == 2) {
			if(sem != 0)
				_sem = *sem;
			else
				_sem = 0;
			__cadul_enter_critical_section((void *)sem);
			}
		}
	~_Lockit()
		{
		


 
		__cadul_exit_critical_section((_sem != 0) ? ((void *)&_sem) : 0);
		}
private:
	_IOS_SEM	_sem;	 
	};

		 









#pragma arguments_in_registers(pop)






 
#line 31 "c:\\rm3dev\\incplus\\xstddef"
#line 1 "c:\\rm3dev\\incplus\\cstddef"
 



















  





#pragma noarguments_in_registers(push)

#line 37 "c:\\rm3dev\\incplus\\cstddef"

#pragma arguments_in_registers(pop)






 
#line 33 "c:\\rm3dev\\incplus\\xstddef"

		
#line 56 "c:\\rm3dev\\incplus\\xstddef"
		
		
#line 66 "c:\\rm3dev\\incplus\\xstddef"
		


		
#line 78 "c:\\rm3dev\\incplus\\xstddef"
		
enum _Uninitialized {_Noinit};
		
void _Nomemory();


#pragma arguments_in_registers(pop)






 
#line 30 "c:\\rm3dev\\incplus\\ios"
#line 1 "c:\\rm3dev\\incplus\\xlocnum"
 



















  





#pragma noarguments_in_registers(push)

#line 1 "c:\\rm3dev\\incplus\\cerrno"
 



















  





#pragma noarguments_in_registers(push)

#line 1 "c:\\rm3dev\\inc\\errno.h"
























 









            
            
#pragma fixedparams("_xerrno", "_xerrno2" )
#pragma fixedparams("_xsys_errlist", "_xsys_nerr")




extern "C" {


extern int  *   far _xerrno       (void);
extern int  *   far _xerrno2      (void);
extern char **  far _xsys_errlist (void);
extern int  *   far _xsys_nerr    (void);


}








 


 

#line 83 "c:\\rm3dev\\inc\\errno.h"






 

#line 117 "c:\\rm3dev\\inc\\errno.h"



 








 

#line 137 "c:\\rm3dev\\inc\\errno.h"


#line 30 "c:\\rm3dev\\incplus\\cerrno"

#pragma arguments_in_registers(pop)






 
#line 30 "c:\\rm3dev\\incplus\\xlocnum"
#line 1 "c:\\rm3dev\\incplus\\climits"
 



















  





#pragma noarguments_in_registers(push)

#line 1 "c:\\rm3dev\\inc\\limits.h"





















 










            
            
#line 52 "c:\\rm3dev\\inc\\limits.h"


 
#line 65 "c:\\rm3dev\\inc\\limits.h"


#line 91 "c:\\rm3dev\\inc\\limits.h"


#line 128 "c:\\rm3dev\\inc\\limits.h"


				 
				 


#line 30 "c:\\rm3dev\\incplus\\climits"

#pragma arguments_in_registers(pop)






 
#line 31 "c:\\rm3dev\\incplus\\xlocnum"
#line 1 "c:\\rm3dev\\incplus\\clocale"
 



















  





#pragma noarguments_in_registers(push)

#line 1 "c:\\rm3dev\\inc\\locale.h"





















 









            
            
#pragma fixedparams ( "setlocale" )



#pragma align (lconv)




#line 49 "c:\\rm3dev\\inc\\locale.h"






extern "C" {




struct lconv {
    char *decimal_point;         
    char *thousands_sep;         
    char *grouping;              
    char *int_curr_symbol;       
    char *currency_symbol;       
    char *mon_decimal_point;     
    char *mon_thousands_sep;     
    char *mon_grouping;          
    char *positive_sign;         
    char *negative_sign;         
    char int_frac_digits;        
    char frac_digits;            
    char p_cs_precedes;          
    char p_sep_by_space;         
    char n_cs_precedes;          
    char n_sep_by_space;         
    char p_sign_posn;            
    char n_sign_posn;            
};


#line 90 "c:\\rm3dev\\inc\\locale.h"



#line 104 "c:\\rm3dev\\inc\\locale.h"






#pragma fixedparams(setlocale,localeconv)







extern char *  far setlocale (int category, const  char *locale);
struct lconv *localeconv (void); 





#line 136 "c:\\rm3dev\\inc\\locale.h"

#line 147 "c:\\rm3dev\\inc\\locale.h"


}


#line 30 "c:\\rm3dev\\incplus\\clocale"
#line 37 "c:\\rm3dev\\incplus\\clocale"

#pragma arguments_in_registers(pop)






 
#line 32 "c:\\rm3dev\\incplus\\xlocnum"
#line 1 "c:\\rm3dev\\incplus\\cstdio"
 



















  





#pragma noarguments_in_registers(push)

#line 52 "c:\\rm3dev\\incplus\\cstdio"

#line 73 "c:\\rm3dev\\incplus\\cstdio"

#pragma arguments_in_registers(pop)






 
#line 33 "c:\\rm3dev\\incplus\\xlocnum"
#line 1 "c:\\rm3dev\\incplus\\cstdlib"
 



















  





#pragma noarguments_in_registers(push)
#line 64 "c:\\rm3dev\\incplus\\cstdlib"

#pragma arguments_in_registers(pop)






 
#line 34 "c:\\rm3dev\\incplus\\xlocnum"
#line 1 "c:\\rm3dev\\incplus\\streambuf"
 



















  





#pragma noarguments_in_registers(push)

#line 1 "c:\\rm3dev\\incplus\\xiosbase"
 



















  





#pragma noarguments_in_registers(push)

#line 1 "c:\\rm3dev\\incplus\\cctype"
 



















  





#pragma noarguments_in_registers(push)

#line 1 "c:\\rm3dev\\inc\\ctype.h"





























 









            
#pragma fixedparams("tolower", "toupper")
#pragma fixedparams("__chattr")







#line 58 "c:\\rm3dev\\inc\\ctype.h"


#line 72 "c:\\rm3dev\\inc\\ctype.h"








extern "C" {


extern int        far tolower  (int c);
extern int        far toupper  (int c);
extern short int  far __chattr (char c);


}



#line 30 "c:\\rm3dev\\incplus\\cctype"
#line 49 "c:\\rm3dev\\incplus\\cctype"


#pragma arguments_in_registers(pop)






 
#line 30 "c:\\rm3dev\\incplus\\xiosbase"
#line 1 "c:\\rm3dev\\incplus\\stdexcept"
 



















  





#pragma noarguments_in_registers(push)

#line 1 "c:\\rm3dev\\incplus\\xstring"
 



















  





#pragma noarguments_in_registers(push)

#line 1 "c:\\rm3dev\\incplus\\iosfwd"
 



















  





#pragma noarguments_in_registers(push)

#line 1 "c:\\rm3dev\\incplus\\cstring"
 



















  





#pragma noarguments_in_registers(push)

#line 1 "c:\\rm3dev\\inc\\string.h"





















 




#line 33 "c:\\rm3dev\\inc\\string.h"


            
            
#pragma fixedparams("strcat", "strchr", "strcpy", "strncat", "strncpy")
#pragma fixedparams("strpbrk", "strrchr", "strtok", "strstr", "strerror")
#pragma fixedparams("strlen", "strcmp", "strncmp", "strspn", "strcspn")
#pragma fixedparams("strcoll")




extern "C" {


extern char *  far strcat   (char *s1, const char *s2);
extern char *  far strchr   (const char *s, int c);
extern int     far strcmp   (const char *s1, const char *s2);
extern int     far strcoll  (const char *s1, const char *s2);
extern char *  far strcpy   (char *s1, const char *s2);
extern size_t  far strcspn  (const char *s1, const char *s2);
extern char *  far strerror (int errnum);
extern size_t  far strlen   (const char *s);
extern char *  far strncat  (char *s1, const char *s2, size_t n);
extern int     far strncmp  (const char *s1, const char *s2, size_t n);
extern char *  far strncpy  (char *s1, const char *s2, size_t n);
extern char *  far strpbrk  (const char *s1, const char *s2);
extern char *  far strrchr  (const char *s, int c);
extern size_t  far strspn   (const char *s1, const char *s2);
extern char *  far strstr   (const char *s1, const char *s2);
extern char *  far strtok   (char *s1, const char *s2);


}



#line 1 "c:\\rm3dev\\inc\\memory.h"




















 





#line 33 "c:\\rm3dev\\inc\\memory.h"


            
            
#pragma fixedparams("memcmp", "memset", "memchr", "memcpy", "memccpy")
#pragma fixedparams("memmove")




extern "C" {


extern void *  far memccpy (void *s1, const void *s2, int c, size_t n);
extern void *  far memchr  (const void *s, int c, size_t n);
extern int     far memcmp  (const void *s1, const void *s2, size_t n);
extern void *  far memcpy  (void *s1, const void *s2, size_t n);
extern void *  far memmove (void *dest, const void *s2, size_t n);
extern void *  far memset  (void *s, int c, size_t n);


}





 
#line 74 "c:\\rm3dev\\inc\\memory.h"


#line 72 "c:\\rm3dev\\inc\\string.h"




 
#line 86 "c:\\rm3dev\\inc\\string.h"


#line 30 "c:\\rm3dev\\incplus\\cstring"
#line 55 "c:\\rm3dev\\incplus\\cstring"

#pragma arguments_in_registers(pop)






 
#line 31 "c:\\rm3dev\\incplus\\iosfwd"


		
typedef long streamoff;
typedef int streamsize;
extern fpos_t _Fpz;
extern const streamoff _BADOFF;
typedef int mbstate_t;
		



#pragma       align   (fpos=4)                

class fpos {
	typedef mbstate_t _St;
	typedef fpos _Myt;
public:
	fpos(streamoff _O = 0)
		: _Off(_O), _Fpos(_Fpz), _State(_Stz) {}
	fpos(_St __S, fpos_t _F)
		: _Off(0), _Fpos(_F), _State(__S) {}
	_St state() const
		{return (_State); }
	void state(_St __S)
		{_State = __S; }
	fpos_t seekpos() const
		{return (_Fpos); }
	operator streamoff() const
		{return (_Off + ((long)(_Fpos))); }
	streamoff operator-(const _Myt& _R) const
		{return ((streamoff)*this - (streamoff)_R); }
	_Myt& operator+=(streamoff _O)
		{_Off += _O;
		return (*this); }
	_Myt& operator-=(streamoff _O)
		{_Off -= _O;
		return (*this); }
	_Myt operator+(streamoff _O) const
		{_Myt _Tmp = *this;
		return (_Tmp += _O); }
	_Myt operator-(streamoff _O) const
		{_Myt _Tmp = *this;
		return (_Tmp -= _O); }
	bool operator==(const _Myt& _R) const
		{return ((streamoff)*this == (streamoff)_R); }
	bool operator!=(const _Myt& _R) const
		{return (!(*this == _R)); }
private:
	static _St _Stz;
	streamoff _Off;
	fpos_t _Fpos;
	_St _State;
	};
typedef fpos streampos;
		



#pragma       align   (char_traits=4)         

struct char_traits {
	typedef char _E;
	typedef _E char_type;
	typedef int int_type;
	typedef streampos pos_type;
	typedef streamoff off_type;
	typedef mbstate_t state_type;
	static void assign(_E& __X, const _E& _Y)
		{__X = _Y; }
	static bool eq(const _E& __X, const _E& _Y)
		{return (__X == _Y); }
	static bool lt(const _E& __X, const _E& _Y)
		{return (__X < _Y); }
	static int compare(const _E *__U, const _E *_V,
		size_t __N)
		{return (memcmp(__U, _V, __N)); }
	static size_t length(const _E *__U)
		{return (strlen(__U)); }
	static _E *copy(_E *__U, const _E *_V, size_t __N)
		{return ((_E *)memcpy(__U, _V, __N)); }
	static const _E *find(const _E *__U, size_t __N,
		const _E& __C)
		{return ((const _E *)memchr(__U, __C, __N)); }
	static _E *move(_E *__U, const _E *_V, size_t __N)
		{return ((_E *)memmove(__U, _V, __N)); }
	static _E *assign(_E *__U, size_t __N, _E __C)
		{return ((_E *)memset(__U, __C, __N)); }
	static _E to_char_type(const int_type& __C)
		{return (__C); }
	static int_type to_int_type(const _E& __C)
		{return ((unsigned char)__C); }
	static bool eq_int_type(const int_type& __X,
		const int_type& _Y)
		{return (__X == _Y); }
	static int_type eof()
		{return ((-1)); }
	static int_type not_eof(const int_type& __C)
		{return (__C != eof() ? __C : !eof()); }
	};
		
class char_allocator;
class ios_base;
class ios;
class streambuf;
class istream;
class ostream;
class stringbuf;
class istringstream;
class ostringstream;
class filebuf;
class ifstream;
class ofstream;


#pragma arguments_in_registers(pop)






 
#line 30 "c:\\rm3dev\\incplus\\xstring"

		



#pragma       align   (_String_base=4)                

class _String_base {
public:
	void _Xlen() const;
	void _Xran() const;
	};

		



#pragma       align   (char_allocator=4)              

class char_allocator {
public:
	char_allocator() {}
	static char *allocate(size_t __N, const void *)
		{return ((char *)operator new(__N)); }
	static void deallocate(void *__P, size_t)
		{operator delete(__P); }
	static size_t max_size()
		{return ((size_t)(-1)); }
	bool operator==(const char_allocator&) const
		{return (true); }
	};

		



#pragma       align   (_String_val=4)                 

class _String_val : public _String_base {
protected:
	_String_val(char_allocator _Al = char_allocator())
		: _Alval(_Al) {}
	char_allocator _Alval;
	};

		



#pragma       align   (string=4)                      

class string : public _String_val {
public:
	typedef string _Myt;
	typedef _String_val _Mybase;
	typedef char _E;
	typedef char_traits _Tr;
	typedef char_allocator _A;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef char *pointer;
	typedef const char *const_pointer;
	typedef char& reference;
	typedef const char& const_reference;
	typedef char value_type;
	typedef pointer iterator;
	typedef const_pointer const_iterator;
		
	class reverse_iterator {
	public:
		typedef reverse_iterator _Myt;
		typedef char *iter_type;
		typedef char value_type;
		typedef char& reference;
		typedef char *pointer;
		typedef ptrdiff_t difference_type;
			
		reverse_iterator()
			{}
		explicit reverse_iterator(iter_type __X)
			: current(__X) {}
		iter_type base() const
			{return (current); }
		reference operator*() const
			{return (*(current - 1)); }
		_Myt& operator++()
			{--current;
			return (*this); }
		_Myt operator++(int)
			{_Myt _Tmp = *this;
			--current;
			return (_Tmp); }
		_Myt& operator--()
			{++current;
			return (*this); }
		_Myt operator--(int)
			{_Myt _Tmp = *this;
			++current;
			return (_Tmp); }
		_Myt& operator+=(difference_type __N)
			{current -= __N;
			return (*this); }
		_Myt operator+(difference_type __N) const
			{return (_Myt(current - __N)); }
		_Myt& operator-=(difference_type __N)
			{current += __N;
			return (*this); }
		_Myt operator-(difference_type __N) const
			{return (_Myt(current + __N)); }
		difference_type operator-(const _Myt _Y) const
			{return (_Y.current - current); }
		reference operator[](difference_type __N) const
			{return (*(*this + __N)); }
		bool operator==(const _Myt _Y) const
			{return (current == _Y.current); }
		bool operator!=(const _Myt _Y) const
			{return (!(*this == _Y)); }
		bool operator<(const _Myt _Y) const
			{return (_Y.current < current); }
		bool operator>(const _Myt _Y) const
			{return (_Y < *this); }
		bool operator<=(const _Myt _Y) const
			{return (!(_Y < *this)); }
		bool operator>=(const _Myt _Y) const
			{return (!(*this < _Y)); }
		friend _Myt operator+(ptrdiff_t __N, const _Myt& _Y)
			{return (_Myt(_Y.current - __N)); }
	protected:
		iter_type current;
		};
			
	class const_reverse_iterator {
	public:
		typedef const_reverse_iterator _Myt;
		typedef const char *iter_type;
		typedef const char value_type;
		typedef const char& reference;
		typedef const char *pointer;
		typedef ptrdiff_t difference_type;
		const_reverse_iterator()
			{}
		explicit const_reverse_iterator(iter_type __X)
			: current(__X) {}
		iter_type base() const
			{return (current); }
		reference operator*() const
			{return (*(current - 1)); }
		_Myt& operator++()
			{--current;
			return (*this); }
		_Myt operator++(int)
			{_Myt _Tmp = *this;
			--current;
			return (_Tmp); }
		_Myt& operator--()
			{++current;
			return (*this); }
		_Myt operator--(int)
			{_Myt _Tmp = *this;
			++current;
			return (_Tmp); }
		_Myt& operator+=(difference_type __N)
			{current -= __N;
			return (*this); }
		_Myt operator+(difference_type __N) const
			{return (_Myt(current - __N)); }
		_Myt& operator-=(difference_type __N)
			{current += __N;
			return (*this); }
		_Myt operator-(difference_type __N) const
			{return (_Myt(current + __N)); }
		difference_type operator-(const _Myt _Y) const
			{return (_Y.current - current); }
		reference operator[](difference_type __N) const
			{return (*(*this + __N)); }
		bool operator==(const _Myt _Y) const
			{return (current == _Y.current); }
		bool operator!=(const _Myt _Y) const
			{return (!(*this == _Y)); }
		bool operator<(const _Myt _Y) const
			{return (_Y.current < current); }
		bool operator>(const _Myt _Y) const
			{return (_Y < *this); }
		bool operator<=(const _Myt _Y) const
			{return (!(_Y < *this)); }
		bool operator>=(const _Myt _Y) const
			{return (!(*this < _Y)); }
		friend _Myt operator+(ptrdiff_t __N, const _Myt& _Y)
			{return (_Myt(_Y.current - __N)); }
	protected:
		iter_type current;
		};

	string()
		: _Mybase()
		{_Tidy(); }
	explicit string(const _A& _Al)
		: _Mybase(_Al)
		{_Tidy(); }
	string(const _Myt& __X)
		: _Mybase(__X._Alval)
		{_Tidy(), assign(__X, 0, npos); }
	string(const _Myt& __X, size_type __P,
		size_type _M = npos)
		: _Mybase()
		{_Tidy(), assign(__X, __P, _M); }
	string(const _Myt& __X, size_type __P, size_type _M,
		const _A& _Al)
		: _Mybase(_Al)
		{_Tidy(), assign(__X, __P, _M); }
	string(const _E *__S, size_type __N)
		: _Mybase()
		{_Tidy(), assign(__S, __N); }
	string(const _E *__S, size_type __N, const _A& _Al)
		: _Mybase(_Al)
		{_Tidy(), assign(__S, __N); }
	string(const _E *__S)
		: _Mybase()
		{_Tidy(), assign(__S); }
	string(const _E *__S, const _A& _Al)
		: _Mybase(_Al)
		{_Tidy(), assign(__S); }
	string(size_type __N, _E __C)
		: _Mybase()
		{_Tidy(), assign(__N, __C); }
	string(size_type __N, _E __C, const _A& _Al)
		: _Mybase(_Al)
		{_Tidy(), assign(__N, __C); }
	typedef const_pointer _It;
	string(_It _F, _It __L)
		: _Mybase()
		{_Tidy();
		if (_F != __L)
			assign(&*_F, __L - _F); }
	string(_It _F, _It __L, const _A& _Al)
		: _Mybase(_Al)
		{_Tidy();
		if (_F != __L)
			assign(&*_F, __L - _F); }
	~string()
		{_Tidy(true); }
	typedef _Tr traits_type;
	typedef _A allocator_type;
	enum _Mref {_FROZEN = 255};
	static const size_type npos;
	_Myt& operator=(const _Myt& __X)
		{return (assign(__X)); }
	_Myt& operator=(const _E *__S)
		{return (assign(__S)); }
	_Myt& operator=(_E __C)
		{return (assign(1, __C)); }
	_Myt& operator+=(const _Myt& __X)
		{return (append(__X)); }
	_Myt& operator+=(const _E *__S)
		{return (append(__S)); }
	_Myt& operator+=(_E __C)
		{return (append((size_type)1, __C)); }
	_Myt& append(const _Myt& __X)
		{return (append(__X, 0, npos)); }
	_Myt& append(const _Myt& __X, size_type __P, size_type _M)
		{if (__X.size() < __P)
			_Xran();
		size_type __N = __X.size() - __P;
		if (__N < _M)
			_M = __N;
		if (npos - _Len <= _M)
			_Xlen();
		if (0 < _M && _Grow(__N = _Len + _M))
			{_Tr::copy(_Ptr + _Len, &__X.c_str()[__P], _M);
			_Eos(__N); }
		return (*this); }
	_Myt& append(const _E *__S, size_type _M)
		{if (_Inside(__S))
			return (append(*this, __S - _Ptr, _M));
		if (npos - _Len <= _M)
			_Xlen();
		size_type __N;
		if (0 < _M && _Grow(__N = _Len + _M))
			{_Tr::copy(_Ptr + _Len, __S, _M);
			_Eos(__N); }
		return (*this); }
	_Myt& append(const _E *__S)
		{return (append(__S, _Tr::length(__S))); }
	_Myt& append(size_type _M, _E __C)
		{if (npos - _Len <= _M)
			_Xlen();
		size_type __N;
		if (0 < _M && _Grow(__N = _Len + _M))
			{_Tr::assign(_Ptr + _Len, _M, __C);
			_Eos(__N); }
		return (*this); }
	_Myt& append(_It _F, _It __L)
		{return (replace(end(), end(), _F, __L)); }
	_Myt& assign(const _Myt& __X)
		{return (assign(__X, 0, npos)); }
	_Myt& assign(const _Myt& __X, size_type __P, size_type _M)
		{if (__X.size() < __P)
			_Xran();
		size_type __N = __X.size() - __P;
		if (_M < __N)
			__N = _M;
		if (this == &__X)
			erase((size_type)(__P + __N)), erase(0, __P);
		else if (0 < __N && __N == __X.size()
			&& _Refcnt(__X.c_str()) < _FROZEN - 1
			&& _Alval == __X._Alval)
			{_Tidy(true);
			_Ptr = (_E *)__X.c_str();
			_Len = __X.size();
			_Res = __X.capacity();
			++_Refcnt(_Ptr); }
		else if (_Grow(__N, true))
			{_Tr::copy(_Ptr, &__X.c_str()[__P], __N);
			_Eos(__N); }
		return (*this); }
	_Myt& assign(const _E *__S, size_type __N)
		{if (_Inside(__S))
			return (assign(*this, __S - _Ptr, __N));
		if (_Grow(__N, true))
			{_Tr::copy(_Ptr, __S, __N);
			_Eos(__N); }
		return (*this); }
	_Myt& assign(const _E *__S)
		{return (assign(__S, _Tr::length(__S))); }
	_Myt& assign(size_type __N, _E __C)
		{if (__N == npos)
			_Xlen();
		if (_Grow(__N, true))
			{_Tr::assign(_Ptr, __N, __C);
			_Eos(__N); }
		return (*this); }
	_Myt& assign(_It _F, _It __L)
		{return (replace(begin(), end(), _F, __L)); }
	_Myt& insert(size_type _P0, const _Myt& __X)
		{return (insert(_P0, __X, 0, npos)); }
	_Myt& insert(size_type _P0, const _Myt& __X, size_type __P,
		size_type _M)
		{if (_Len < _P0 || __X.size() < __P)
			_Xran();
		size_type __N = __X.size() - __P;
		if (__N < _M)
			_M = __N;
		if (npos - _Len <= _M)
			_Xlen();
		if (0 < _M && _Grow(__N = _Len + _M))
			{_Tr::move(_Ptr + _P0 + _M, _Ptr + _P0, _Len - _P0);
			if (this == &__X)
				_Tr::move(_Ptr + _P0,
					_Ptr + (_P0 < __P ? __P + _M : __P), _M);
			else
				_Tr::copy(_Ptr + _P0, &__X.c_str()[__P], _M);
			_Eos(__N); }
		return (*this); }
	_Myt& insert(size_type _P0, const _E *__S, size_type _M)
		{if (_Inside(__S))
			return (insert(_P0, *this, __S - _Ptr, _M));
		if (_Len < _P0)
			_Xran();
		if (npos - _Len <= _M)
			_Xlen();
		size_type __N;
		if (0 < _M && _Grow(__N = _Len + _M))
			{_Tr::move(_Ptr + _P0 + _M, _Ptr + _P0, _Len - _P0);
			_Tr::copy(_Ptr + _P0, __S, _M);
			_Eos(__N); }
		return (*this); }
	_Myt& insert(size_type _P0, const _E *__S)
		{return (insert(_P0, __S, _Tr::length(__S))); }
	_Myt& insert(size_type _P0, size_type _M, _E __C)
		{if (_Len < _P0)
			_Xran();
		if (npos - _Len <= _M)
			_Xlen();
		size_type __N;
		if (0 < _M && _Grow(__N = _Len + _M))
			{_Tr::move(_Ptr + _P0 + _M, _Ptr + _P0, _Len - _P0);
			_Tr::assign(_Ptr + _P0, _M, __C);
			_Eos(__N); }
		return (*this); }
	iterator insert(iterator __P)
		{return (insert(__P, _E())); }
	iterator insert(iterator __P, _E __C)
		{size_type _P0 = _Pdif(__P, begin());
		insert(_P0, 1, __C);
		return (begin() + _P0); }
	void insert(iterator __P, size_type _M, _E __C)
		{size_type _P0 = _Pdif(__P, begin());
		insert(_P0, _M, __C); }
	void insert(iterator __P, _It _F, _It __L)
		{replace(__P, __P, _F, __L); }
	_Myt& erase(size_type _P0 = 0, size_type _M = npos)
		{if (_Len < _P0)
			_Xran();
		if (_Len - _P0 < _M)
			_M = _Len - _P0;
		if (0 < _M)
			{_Freeze();
			_Tr::move(_Ptr + _P0, _Ptr + _P0 + _M,
				_Len - _P0 - _M);
			size_type __N = _Len - _M;
			if (_Grow(__N))
				_Eos(__N); }
		return (*this); }
	iterator erase(iterator __P)
		{size_type _M = _Pdif(__P, begin());
		erase(_M, 1);
		return (iterator(_Psum(_Ptr, _M))); }
	iterator erase(iterator _F, iterator __L)
		{size_type _M = _Pdif(_F, begin());
		erase(_M, _Pdif(__L, _F));
		return (iterator(_Psum(_Ptr, _M))); }
	void clear()
		{erase(begin(), end()); }
	_Myt& replace(size_type _P0, size_type _N0, const _Myt& __X)
		{return (replace(_P0, _N0, __X, 0, npos)); }
	_Myt& replace(size_type _P0, size_type _N0, const _Myt& __X,
		size_type __P, size_type _M)
		{if (_Len < _P0 || __X.size() < __P)
			_Xran();
		if (_Len - _P0 < _N0)
			_N0 = _Len - _P0;
		size_type __N = __X.size() - __P;
		if (__N < _M)
			_M = __N;
		if (npos - _M <= _Len - _N0)
			_Xlen();
		size_type _Nm = _Len - _N0 - _P0;
		__N = _Len + _M - _N0;
		if (_Len < __N)
			_Grow(__N);
		else if (0 < _M || 0 < _N0)
			_Freeze();
		if (this != &__X)
			{_Tr::move(_Ptr + _P0 + _M, _Ptr + _P0 + _N0, _Nm);
			_Tr::copy(_Ptr + _P0, &__X.c_str()[__P], _M); }
		else if (_M <= _N0)
			{_Tr::move(_Ptr + _P0, _Ptr + __P, _M);
			_Tr::move(_Ptr + _P0 + _M, _Ptr + _P0 + _N0, _Nm); }
		else if (__P <= _P0)
			{_Tr::move(_Ptr + _P0 + _M, _Ptr + _P0 + _N0, _Nm);
			_Tr::move(_Ptr + _P0, _Ptr + __P, _M); }
		else if (_P0 + _N0 <= __P)
			{_Tr::move(_Ptr + _P0 + _M, _Ptr + _P0 + _N0, _Nm);
			_Tr::move(_Ptr + _P0, _Ptr + (__P + _M - _N0), _M); }
		else
			{_Tr::move(_Ptr + _P0, _Ptr + __P, _N0);
			_Tr::move(_Ptr + _P0 + _M, _Ptr + _P0 + _N0, _Nm);
			_Tr::move(_Ptr + _P0 + _N0, _Ptr + __P + _M,
				_M - _N0); }
		if (_Len < __N || _Grow(__N))
			_Eos(__N);
		return (*this); }
	_Myt& replace(size_type _P0, size_type _N0, const _E *__S,
		size_type _M)
		{if (_Inside(__S))
			return (replace(_P0, _N0, *this, __S - _Ptr, _M));
		if (_Len < _P0)
			_Xran();
		if (_Len - _P0 < _N0)
			_N0 = _Len - _P0;
		if (npos - _M <= _Len - _N0)
			_Xlen();
		size_type _Nm = _Len - _N0 - _P0;
		if (_M < _N0)
			{_Freeze();
			_Tr::move(_Ptr + _P0 + _M, _Ptr + _P0 + _N0, _Nm); }
		size_type __N;
		if ((0 < _M || 0 < _N0) && _Grow(__N = _Len + _M - _N0))
			{if (_N0 < _M)
				_Tr::move(_Ptr + _P0 + _M, _Ptr + _P0 + _N0, _Nm);
			_Tr::copy(_Ptr + _P0, __S, _M);
			_Eos(__N); }
		return (*this); }
	_Myt& replace(size_type _P0, size_type _N0, const _E *__S)
		{return (replace(_P0, _N0, __S, _Tr::length(__S))); }
	_Myt& replace(size_type _P0, size_type _N0,
		size_type _M, _E __C)
		{if (_Len < _P0)
			_Xran();
		if (_Len - _P0 < _N0)
			_N0 = _Len - _P0;
		if (npos - _M <= _Len - _N0)
			_Xlen();
		size_type _Nm = _Len - _N0 - _P0;
		if (_M < _N0)
			{_Freeze();
			_Tr::move(_Ptr + _P0 + _M, _Ptr + _P0 + _N0, _Nm); }
		size_type __N;
		if ((0 < _M || 0 < _N0) && _Grow(__N = _Len + _M - _N0))
			{if (_N0 < _M)
				_Tr::move(_Ptr + _P0 + _M, _Ptr + _P0 + _N0, _Nm);
			_Tr::assign(_Ptr + _P0, _M, __C);
			_Eos(__N); }
		return (*this); }
	_Myt& replace(iterator _F, iterator __L, const _Myt& __X)
		{return (replace(
			_Pdif(_F, begin()), _Pdif(__L, _F), __X)); }
	_Myt& replace(iterator _F, iterator __L, const _E *__S,
		size_type _M)
		{return (replace(
			_Pdif(_F, begin()), _Pdif(__L, _F), __S, _M)); }
	_Myt& replace(iterator _F, iterator __L, const _E *__S)
		{return (replace(
			_Pdif(_F, begin()), _Pdif(__L, _F), __S)); }
	_Myt& replace(iterator _F, iterator __L,	size_type _M, _E __C)
		{return (replace(
			_Pdif(_F, begin()), _Pdif(__L, _F), _M, __C)); }
	_Myt& replace(iterator _F1, iterator _L1,
		_It _F2, _It _L2)
		{if (_F2 == _L2)
			erase(_Pdif(_F1, begin()), _Pdif(_L1, _F1));
		else
			replace(_Pdif(_F1, begin()), _Pdif(_L1, _F1),
				&*_F2, _L2 - _F2);
		return (*this); }
	iterator begin()
		{_Freeze();
		return (iterator(_Ptr)); }
	const_iterator begin() const
		{return (const_iterator(_Ptr)); }
	iterator end()
		{_Freeze();
		return (iterator(_Psum(_Ptr, _Len))); }
	const_iterator end() const
		{return (const_iterator(_Psum(_Ptr, _Len))); }
	reverse_iterator rbegin()
		{return (reverse_iterator(end())); }
	const_reverse_iterator rbegin() const
		{return (const_reverse_iterator(end())); }
	reverse_iterator rend()
		{return (reverse_iterator(begin())); }
	const_reverse_iterator rend() const
		{return (const_reverse_iterator(begin())); }
	reference at(size_type _P0)
		{if (_Len <= _P0)
			_Xran();
		_Freeze();
		return (_Ptr[_P0]); }
	const_reference at(size_type _P0) const
		{if (_Len <= _P0)
			_Xran();
		return (_Ptr[_P0]); }
	reference operator[](size_type _P0)
		{if (_Len < _P0 || _Ptr == 0)
			return ((reference)*_Nullstr());
		_Freeze();
		return (_Ptr[_P0]); }
	const_reference operator[](size_type _P0) const
		{if (_Ptr == 0)
			return (*_Nullstr());
		else
			return (_Ptr[_P0]); }
	void push_back(_E __C)
		{insert(end(), __C); }
	const _E *c_str() const
		{return (_Ptr == 0 ? _Nullstr() : _Ptr); }
	const _E *data() const
		{return (c_str()); }
	size_type length() const
		{return (_Len); }
	size_type size() const
		{return (_Len); }
	size_type max_size() const
		{size_type __N = _Alval.max_size();
		return (__N <= 2 ? 1 : __N - 2); }
	void resize(size_type __N)
		{resize(__N, _E()); }
	void resize(size_type __N, _E __C)
		{__N <= _Len ? erase(__N) : append(__N - _Len, __C); }
	size_type capacity() const
		{return (_Res); }
	void reserve(size_type __N = 0)
		{if (_Res < __N)
			_Grow(__N); }
	bool empty() const
		{return (_Len == 0); }
	size_type copy(_E *__S, size_type __N, size_type _P0 = 0) const
		{if (_Len < _P0)
			_Xran();
		if (_Len - _P0 < __N)
			__N = _Len - _P0;
		if (0 < __N)
			_Tr::copy(__S, _Ptr + _P0, __N);
		return (__N); }
	void swap(_Myt& __X)
		{if (_Alval == __X._Alval)
			{_E *_Tptr = _Ptr;
			_Ptr = __X._Ptr, __X._Ptr = _Tptr;
			size_type _Tlen = _Len;
			_Len = __X._Len, __X._Len = _Tlen;
			size_type _Tres = _Res;
			_Res = __X._Res, __X._Res = _Tres; }
		else
			{_Myt _Ts = *this; *this = __X, __X = _Ts; }}
	friend void swap(_Myt& __X, _Myt& _Y)
		{__X.swap(_Y); }
	size_type find(const _Myt& __X, size_type __P = 0) const
		{return (find(__X.c_str(), __P, __X.size())); }
	size_type find(const _E *__S, size_type __P,
		size_type __N) const
		{if (__N == 0 && __P <= _Len)
			return (__P);
		size_type _Nm;
		if (__P < _Len && __N <= (_Nm = _Len - __P))
			{const _E *__U, *_V;
			for (_Nm -= __N - 1, _V = _Ptr + __P;
				(__U = _Tr::find(_V, _Nm, *__S)) != 0;
				_Nm -= __U - _V + 1, _V = __U + 1)
				if (_Tr::compare(__U, __S, __N) == 0)
					return (__U - _Ptr); }
		return (npos); }
	size_type find(const _E *__S, size_type __P = 0) const
		{return (find(__S, __P, _Tr::length(__S))); }
	size_type find(_E __C, size_type __P = 0) const
		{return (find((const _E *)&__C, __P, 1)); }
	size_type rfind(const _Myt& __X, size_type __P = npos) const
		{return (rfind(__X.c_str(), __P, __X.size())); }
	size_type rfind(const _E *__S, size_type __P,
		size_type __N) const
		{if (__N == 0)
			return (__P < _Len ? __P : _Len);
		if (__N <= _Len)
			for (const _E *__U = _Ptr +
				+ (__P < _Len - __N ? __P : _Len - __N); ; --__U)
				if (_Tr::eq(*__U, *__S)
					&& _Tr::compare(__U, __S, __N) == 0)
					return (__U - _Ptr);
				else if (__U == _Ptr)
					break;
		return (npos); }
	size_type rfind(const _E *__S, size_type __P = npos) const
		{return (rfind(__S, __P, _Tr::length(__S))); }
	size_type rfind(_E __C, size_type __P = npos) const
		{return (rfind((const _E *)&__C, __P, 1)); }
	size_type find_first_of(const _Myt& __X,
		size_type __P = 0) const
		{return (find_first_of(__X.c_str(), __P, __X.size())); }
	size_type find_first_of(const _E *__S, size_type __P,
		size_type __N) const
		{if (0 < __N && __P < _Len)
			{const _E *const _V = _Ptr + _Len;
			for (const _E *__U = _Ptr + __P; __U < _V; ++__U)
				if (_Tr::find(__S, __N, *__U) != 0)
					return (__U - _Ptr); }
		return (npos); }
	size_type find_first_of(const _E *__S, size_type __P = 0) const
		{return (find_first_of(__S, __P, _Tr::length(__S))); }
	size_type find_first_of(_E __C, size_type __P = 0) const
		{return (find((const _E *)&__C, __P, 1)); }
	size_type find_last_of(const _Myt& __X,
		size_type __P = npos) const
		{return (find_last_of(__X.c_str(), __P, __X.size())); }
	size_type find_last_of(const _E *__S, size_type __P,
		size_type __N) const
		{if (0 < __N && 0 < _Len)
			for (const _E *__U = _Ptr
				+ (__P < _Len ? __P : _Len - 1); ; --__U)
				if (_Tr::find(__S, __N, *__U) != 0)
					return (__U - _Ptr);
				else if (__U == _Ptr)
					break;
		return (npos); }
	size_type find_last_of(const _E *__S,
		size_type __P = npos) const
		{return (find_last_of(__S, __P, _Tr::length(__S))); }
	size_type find_last_of(_E __C, size_type __P = npos) const
		{return (rfind((const _E *)&__C, __P, 1)); }
	size_type find_first_not_of(const _Myt& __X,
		size_type __P = 0) const
		{return (find_first_not_of(__X.c_str(), __P,
			__X.size())); }
	size_type find_first_not_of(const _E *__S, size_type __P,
		size_type __N) const
		{if (__P < _Len)
			{const _E *const _V = _Ptr + _Len;
			for (const _E *__U = _Ptr + __P; __U < _V; ++__U)
				if (_Tr::find(__S, __N, *__U) == 0)
					return (__U - _Ptr); }
		return (npos); }
	size_type find_first_not_of(const _E *__S,
		size_type __P = 0) const
		{return (find_first_not_of(__S, __P, _Tr::length(__S))); }
	size_type find_first_not_of(_E __C, size_type __P = 0) const
		{return (find_first_not_of((const _E *)&__C, __P, 1)); }
	size_type find_last_not_of(const _Myt& __X,
		size_type __P = npos) const
		{return (find_last_not_of(__X.c_str(), __P, __X.size())); }
	size_type find_last_not_of(const _E *__S, size_type __P,
		 size_type __N) const
		{if (0 < _Len)
			for (const _E *__U = _Ptr
				+ (__P < _Len ? __P : _Len - 1); ; --__U)
				if (_Tr::find(__S, __N, *__U) == 0)
					return (__U - _Ptr);
				else if (__U == _Ptr)
					break;
		return (npos); }
	size_type find_last_not_of(const _E *__S,
		size_type __P = npos) const
		{return (find_last_not_of(__S, __P, _Tr::length(__S))); }
	size_type find_last_not_of(_E __C, size_type __P = npos) const
		{return (find_last_not_of((const _E *)&__C, __P, 1)); }
	_Myt substr(size_type __P = 0, size_type _M = npos) const
		{return (_Myt(*this, __P, _M)); }
	int compare(const _Myt& __X) const
		{return (compare(0, _Len, __X.c_str(), __X.size())); }
	int compare(size_type _P0, size_type _N0,
		const _Myt& __X) const
		{return (compare(_P0, _N0, __X, 0, npos)); }
	int compare(size_type _P0, size_type _N0, const _Myt& __X,
		size_type __P, size_type _M) const
		{if (__X.size() < __P)
			_Xran();
		if (__X._Len - __P < _M)
			_M = __X._Len - __P;
		return (compare(_P0, _N0, __X.c_str() + __P, _M)); }
	int compare(const _E *__S) const
		{return (compare(0, _Len, __S, _Tr::length(__S))); }
	int compare(size_type _P0, size_type _N0, const _E *__S) const
		{return (compare(_P0, _N0, __S, _Tr::length(__S))); }
	int compare(size_type _P0, size_type _N0, const _E *__S,
		size_type _M) const
		{if (_Len < _P0)
			_Xran();
		if (_Len - _P0 < _N0)
			_N0 = _Len - _P0;
		size_type _Ans = _N0 == 0 ? 0
			: _Tr::compare(_Psum(_Ptr, _P0), __S,
				_N0 < _M ? _N0 : _M);
		return (_Ans != 0 ? _Ans : _N0 < _M ? -1
			: _N0 == _M ? 0 : +1); }
	allocator_type get_allocator() const
		{return (_Alval); }
private:
	enum {_MIN_SIZE = sizeof (_E) <= 32 ? 31 : 7};
	void _Copy(size_type __N)
		{size_type _Ns = __N | _MIN_SIZE;
		if (max_size() < _Ns)
			_Ns = __N;
		_E *__S;
		try {
			__S = _Alval.allocate(_Ns + 2, (void *)0);
		} catch (...) {
			_Ns = __N;
			__S = _Alval.allocate(_Ns + 2, (void *)0);
		}
		if (0 < _Len)
			_Tr::copy(__S + 1, _Ptr, _Len);
		size_type _Olen = _Len;
		_Tidy(true);
		_Ptr = __S + 1;
		_Refcnt(_Ptr) = 0;
		_Res = _Ns;
		_Eos(_Olen); }
	void _Eos(size_type __N)
		{_Tr::assign(_Ptr[_Len = __N], _E()); }
	void _Freeze()
		{if (_Ptr != 0
			&& _Refcnt(_Ptr) != 0 && _Refcnt(_Ptr) != _FROZEN)
			_Grow(_Len);
		if (_Ptr != 0)
			_Refcnt(_Ptr) = _FROZEN; }
	bool _Grow(size_type __N, bool _Trim = false)
		{if (max_size() < __N)
			_Xlen();
		if (_Trim)
			_Len = 0;
		else if (__N < _Len)
			_Len = __N;
		if (_Ptr != 0
			&& _Refcnt(_Ptr) != 0 && _Refcnt(_Ptr) != _FROZEN)
			if (__N == 0)
				{_Tidy(true);
				return (false); }
			else
				{_Copy(__N);
				return (true); }
		if (__N == 0)
			{if (_Trim)
				_Tidy(true);
			else if (_Ptr != 0)
				_Eos(0);
			return (false); }
		else
			{if (_Trim && (_MIN_SIZE < _Res || _Res < __N))
				{_Tidy(true);
				_Copy(__N); }
			else if (!_Trim && _Res < __N)
				_Copy(__N);
			return (true); }}
	bool _Inside(const _E *__S)
		{return (_Ptr != 0 && _Ptr <= __S && __S <= _Ptr + _Len); }
	static const _E *_Nullstr()
		{static _E __C;
		__C = _E();
		return (&__C); }
	static size_type _Pdif(const_iterator _P2,
		const_iterator _P1)
		{return (_P2 == 0 ? 0 : _P2 - _P1); }
	static const_pointer _Psum(const_pointer __P, size_type __N)
		{return (__P == 0 ? 0 : __P + __N); }
	static pointer _Psum(pointer __P, size_type __N)
		{return (__P == 0 ? 0 : __P + __N); }
	unsigned char& _Refcnt(const _E *__U)
		{return (((unsigned char *)__U)[-1]); }
	void _Tidy(bool _Built = false)
		{if (!_Built || _Ptr == 0)
			;
		else if (_Refcnt(_Ptr) == 0 || _Refcnt(_Ptr) == _FROZEN)
			_Alval.deallocate(_Ptr - 1, _Res + 2);
		else
			--_Refcnt(_Ptr);
		_Ptr = 0, _Len = 0, _Res = 0; }
	_E *_Ptr;
	size_type _Len, _Res;
	};


#pragma arguments_in_registers(pop)






 
#line 30 "c:\\rm3dev\\incplus\\stdexcept"
#line 1 "c:\\rm3dev\\incplus\\exception"
 



















  





#pragma noarguments_in_registers(push)



extern  void _Throw(const exception& ex);       


#pragma arguments_in_registers(pop)






 
#line 32 "c:\\rm3dev\\incplus\\stdexcept"

		



#pragma       align   (logic_error=4)         

class logic_error : public exception {
public:
	explicit logic_error(const string& __S)
		: exception(""), _Str(__S) {}
	virtual ~logic_error()
		{}
	virtual const char *what() const throw ()
		{return (_Str.c_str()); }
protected:
	virtual void _Doraise() const
		{throw (*this); }
private:
	string _Str;
	};
		



#pragma       align   (domain_error=4)                

class domain_error : public logic_error {
public:
	explicit domain_error(const string& __S)
		: logic_error(__S) {}
	virtual ~domain_error()
		{}
protected:
	virtual void _Doraise() const
		{throw (*this); }
	};
		



#pragma       align   (invalid_argument=4)            

class invalid_argument : public logic_error {
public:
	explicit invalid_argument(const string& __S)
		: logic_error(__S) {}
	virtual ~invalid_argument()
		{}
protected:
	virtual void _Doraise() const
		{throw (*this); }
	};
		



#pragma       align   (length_error=4)                

class length_error : public logic_error {
public:
	explicit length_error(const string& __S)
		: logic_error(__S) {}
	virtual ~length_error()
		{}
protected:
	virtual void _Doraise() const
		{throw (*this); }
	};
		



#pragma       align   (out_of_range=4)                

class out_of_range : public logic_error {
public:
	explicit out_of_range(const string& __S)
		: logic_error(__S) {}
	virtual ~out_of_range()
		{}
protected:
	virtual void _Doraise() const
		{throw (*this); }
	};
		



#pragma       align   (runtime_error=4)               

class runtime_error : public exception {
public:
	explicit runtime_error(const string& __S)
		: exception(""), _Str(__S) {}
	virtual ~runtime_error()
		{}
	virtual const char *what() const throw ()
		{return (_Str.c_str()); }
protected:
	virtual void _Doraise() const
		{throw (*this); }
private:
	string _Str;
	};
		



#pragma       align   (overflow_error=4)              

class overflow_error : public runtime_error {
public:
	explicit overflow_error(const string& __S)
		: runtime_error(__S) {}
	virtual ~overflow_error()
		{}
protected:
	virtual void _Doraise() const
		{throw (*this); }
	};
		



#pragma       align   (underflow_error=4)             

class underflow_error : public runtime_error {
public:
	explicit underflow_error(const string& __S)
		: runtime_error(__S) {}
	virtual ~underflow_error()
		{}
protected:
	virtual void _Doraise() const
		{throw (*this); }
	};
		



#pragma       align   (range_error=4)         

class range_error : public runtime_error {
public:
	explicit range_error(const string& __S)
		: runtime_error(__S) {}
	virtual ~range_error()
		{}
protected:
	virtual void _Doraise() const
		{throw (*this); }
	};


#pragma arguments_in_registers(pop)






 
#line 31 "c:\\rm3dev\\incplus\\xiosbase"



		



#pragma       align   (locale=4)              

class locale {
public:
	locale()
		{}
	locale(_Uninitialized)
		{}
	locale(const char *)
		{}
	bool operator==(const locale&)
		{return (true); }
	bool operator!=(const locale&)
		{return (false); }
	};
		



#pragma       align   (ctype=4)               

class ctype {
public:
	enum mask {space};
	static bool is(mask, char __C)
		{return (( __chattr((char)((__C) & 0xFF)) & (0x0010) )); }
	static char widen(char __X)
		{return (__X); }
	static char narrow(char __C, char = '\0')
		{return (__C); }
	};
		



#pragma       align   (ios_base=4)            

class ios_base {
public:
			
	class failure : public runtime_error {
	public:
		explicit failure(const string &__S)
			: runtime_error(__S) {}
		virtual ~failure()
			{}
	protected:
		virtual void _Doraise() const
			{throw (*this); }
	};
	enum _Fmtflags {skipws = 0x0001, unitbuf = 0x0002,
		uppercase = 0x0004, showbase = 0x0008,
		showpoint = 0x0010, showpos = 0x0020,
		left = 0x0040, right = 0x0080, internal = 0x0100,
		dec = 0x0200, oct = 0x0400, hex = 0x0800,
		scientific = 0x1000, fixed = 0x2000, boolalpha = 0x4000,
		adjustfield = 0x01c0, basefield = 0x0e00,
		floatfield = 0x3000, _Fmtmask = 0x7fff, _Fmtzero = 0};
	enum _Iostate {goodbit = 0x0, eofbit = 0x1,
		failbit = 0x2, badbit = 0x4, _Statmask = 0x7};
	enum _Openmode {in = 0x01, out = 0x02, ate = 0x04,
		app = 0x08, trunc = 0x10, binary = 0x20};
	enum seekdir {beg = 0, cur = 1, end = 2};
	enum event {erase_event, imbue_event, copyfmt_event};
	typedef void (*event_callback)(event, ios_base&, int);
	typedef int fmtflags;
	typedef int iostate;
	typedef int openmode;
	typedef short io_state, open_mode, seek_dir;
			
	class Init {
	public:
		Init();
		~Init();
	private:
		static int _Init_cnt;
		};
	ios_base& operator=(const ios_base& _R)
		{if (this != &_R)
			{_State = _R._State;
			copyfmt(_R); }
		return (*this); }
	operator void *() const
		{return (fail() ? 0 : (void *)this); }
	bool operator!() const
		{return (fail()); }
	void clear(iostate = goodbit, bool = false);
	void clear(io_state _St)
		{clear((iostate)_St); }
	iostate rdstate() const
		{return (_State); }
	void setstate(iostate _St, bool _Ex = false)
		{if (_St != goodbit)
			clear((iostate)((int)rdstate() | (int)_St), _Ex); }
	void setstate(io_state _St)
		{setstate((iostate)_St); }
	bool good() const
		{return (rdstate() == goodbit); }
	bool eof() const
		{return ((int)rdstate() & (int)eofbit); }
	bool fail() const
		{return (((int)rdstate()
			& ((int)badbit | (int)failbit)) != 0); }
	bool bad() const
		{return (((int)rdstate() & (int)badbit) != 0); }
	iostate exceptions() const
		{return (_Except); }
	void exceptions(iostate _Ne)
		{_Except = (iostate)((int)_Ne & (int)_Statmask);
		clear(_State); }
	void exceptions(io_state _St)
		{exceptions((iostate)_St); }
	fmtflags flags() const
		{return (_Fmtfl); }
	fmtflags flags(fmtflags _Nf)
		{fmtflags _Of = _Fmtfl;
		_Fmtfl = (fmtflags)((int)_Nf & (int)_Fmtmask);
		return (_Of); }
	fmtflags setf(fmtflags _Nf)
		{ios_base::fmtflags _Of = _Fmtfl;
		_Fmtfl = (fmtflags)((int)_Fmtfl
			| (int)_Nf & (int)_Fmtmask);
		return (_Of); }
	fmtflags setf(fmtflags _Nf, fmtflags _M)
		{ios_base::fmtflags _Of = _Fmtfl;
		_Fmtfl = (fmtflags)(((int)_Fmtfl & (int)~_M)
			| ((int)_Nf & (int)_M & (int)_Fmtmask));
		return (_Of); }
	void unsetf(fmtflags _M)
		{_Fmtfl = (fmtflags)((int)_Fmtfl & (int)~_M); }
	streamsize precision() const
		{return (_Prec); }
	streamsize precision(int _Np)
		{streamsize _Op = _Prec;
		_Prec = _Np;
		return (_Op); }
	streamsize width() const
		{return (_Wide); }
	streamsize width(streamsize _Nw)
		{streamsize _Ow = _Wide;
		_Wide = _Nw;
		return (_Ow); }
	locale getloc() const
		{return (_Loc); }
	locale imbue(const locale&);
	static int xalloc()
		{return (_Index++); }
	long& iword(int _Idx)
		{return (_Findarr(_Idx)._Lo); }
	void *& pword(int _Idx)
		{return (_Findarr(_Idx)._Vp); }
	void register_callback(event_callback, int);
	ios_base& copyfmt(const ios_base&);
	virtual ~ios_base();
	static bool sync_with_stdio(bool _Sfl = true)
		{const bool _Osfl = _Sync;
		_Sync = _Sfl;
		return (_Osfl); }
protected:
	ios_base()
		: _Loc(_Noinit), _Stdstr(0) { 
		


 
		__cadul_enable_critical_section_lock((void *)&_ios_sem);
		}
	void _Addstd();
	void _Init();
private:
			
	struct _Iosarray {
	public:
		_Iosarray(int _Idx, _Iosarray *_Link)
			: _Next(_Link), _Index(_Idx), _Lo(0), _Vp(0) {}
		_Iosarray *_Next;
		int _Index;
		long _Lo;
		void *_Vp;
		};
			
	struct _Fnarray {
		_Fnarray(int _Idx, event_callback __P, _Fnarray *_Link)
			: _Next(_Link), _Index(_Idx), _Pfn(__P) {}
		_Fnarray *_Next;
		int _Index;
		event_callback _Pfn;
		};
	void _Callfns(event);
	_Iosarray& _Findarr(int);
	void _Tidy();
	iostate _State, _Except;
	fmtflags _Fmtfl;
	int _Prec, _Wide;
	_Iosarray *_Arr;
	_Fnarray *_Calls;
	locale _Loc;
	size_t _Stdstr;
	static int _Index;
	static bool _Sync;
        


 
        public:
        _IOS_SEM _ios_sem;

	};





#pragma arguments_in_registers(pop)






 
#line 30 "c:\\rm3dev\\incplus\\streambuf"



		



#pragma       align   (streambuf=4)           

class streambuf {
	streambuf(const streambuf&);	
	streambuf& operator=(const streambuf&);
protected:
	streambuf()
		: _Loc() {_Init(); }
	streambuf(_Uninitialized)
		: _Loc(_Noinit) {}
public:
	typedef char _E;
	typedef char_traits _Tr;
	typedef streambuf _Myt;
	typedef _E char_type;
	typedef _Tr traits_type;
	virtual ~streambuf()
		{}
	typedef _Tr::int_type int_type;
	typedef _Tr::pos_type pos_type;
	typedef _Tr::off_type off_type;
	pos_type pubseekoff(off_type _O, ios_base::seekdir _W,
		ios_base::openmode _M = ios_base::in | ios_base::out)
		{return (seekoff(_O, _W, _M)); }
	pos_type pubseekoff(off_type _O, ios_base::seek_dir _W,
		ios_base::open_mode _M)
		{return (pubseekoff(_O, (ios_base::seekdir)_W,
			(ios_base::openmode)_M)); }
	pos_type pubseekpos(pos_type __P,
		ios_base::openmode _M = ios_base::in | ios_base::out)
		{return (seekpos(__P, _M)); }
	pos_type pubseekpos(pos_type __P, ios_base::open_mode _M)
		{return (seekpos(__P, (ios_base::openmode)_M)); }
	_Myt *pubsetbuf(_E *__S, streamsize __N)
		{return (setbuf(__S, __N)); }
	locale pubimbue(const locale &_Ln)
		{locale _Lo = _Loc;
		imbue(_Ln);
		_Loc = _Ln;
		return (_Lo); }
	locale getloc()
		{return (_Loc); }
	streamsize in_avail()
		{return (gptr() != 0 && gptr() < egptr()
			? egptr() - gptr() : showmanyc()); }
	int pubsync()
		{return (sync()); }
	int_type sbumpc()
		{return (gptr() != 0 && gptr() < egptr()
			? _Tr::to_int_type(*_Gninc()) : uflow()); }
	int_type sgetc()
		{return (gptr() != 0 && gptr() < egptr()
			? _Tr::to_int_type(*gptr()) : underflow()); }
	streamsize sgetn(_E *__S, streamsize __N)
		{return (xsgetn(__S, __N)); }
	int_type snextc()
		{return (_Tr::eq_int_type(_Tr::eof(), sbumpc())
			? _Tr::eof() : sgetc()); }
	int_type sputbackc(_E __C)
		{return (gptr() != 0 && eback() < gptr()
			&& _Tr::eq(__C, gptr()[-1])
			? _Tr::to_int_type(*_Gndec())
			: pbackfail(_Tr::to_int_type(__C))); }
	void stossc()
		{if (gptr() != 0 && gptr() < egptr())
			_Gninc();
		else
			uflow(); }
	int_type sungetc()
		{return (gptr() != 0 && eback() < gptr()
			? _Tr::to_int_type(*_Gndec()) : pbackfail()); }
	int_type sputc(_E __C)
		{return (pptr() != 0 && pptr() < epptr()
			? _Tr::to_int_type(*_Pninc() = __C)
			: overflow(_Tr::to_int_type(__C))); }
	streamsize sputn(const _E *__S, streamsize __N)
		{return (xsputn(__S, __N)); }
protected:
	_E *eback() const
		{return (*_IGbeg); }
	_E *gptr() const
		{return (*_IGnext); }
	_E *pbase() const
		{return (*_IPbeg); }
	_E *pptr() const
		{return (*_IPnext); }
	_E *egptr() const
		{return (*_IGend); }
	void gbump(int __N)
		{*_IGnext += __N; }
	void setg(_E *__B, _E *__N, _E *__L)
		{*_IGbeg = __B, *_IGnext = __N, *_IGend = __L; }
	_E *epptr() const
		{return (*_IPend); }
	_E *_Gndec()
		{return (--*_IGnext); }
	_E *_Gninc()
		{return ((*_IGnext)++); }
	void pbump(int __N)
		{*_IPnext += __N; }
	void setp(_E *__B, _E *__L)
		{*_IPbeg = __B, *_IPnext = __B, *_IPend = __L; }
	void setp(_E *__B, _E *__N, _E *__L)
		{*_IPbeg = __B, *_IPnext = __N, *_IPend = __L; }
	_E *_Pninc()
		{return ((*_IPnext)++); }
	void _Init()
		{_IGbeg = &_Gbeg, _IPbeg = &_Pbeg;
		_IGnext = &_Gnext, _IPnext = &_Pnext;
		_IGend = &_Gend, _IPend = &_Pend;
		setp(0, 0), setg(0, 0, 0); }
	void _Init(_E **_Gb, _E **_Gn, _E **_Ge,
		_E **_Pb, _E **_Pn, _E **_Pe)
		{_IGbeg = _Gb, _IPbeg = _Pb;
		_IGnext = _Gn, _IPnext = _Pn;
		_IGend = _Ge, _IPend = _Pe; }
	virtual int_type overflow(int_type = _Tr::eof())
		{return (_Tr::eof()); }
	virtual int_type pbackfail(int_type = _Tr::eof())
		{return (_Tr::eof()); }
	virtual streamsize showmanyc()
		{return (0); }
	virtual int_type underflow()
		{return (_Tr::eof()); }
	virtual int_type uflow()
		{return (_Tr::eq_int_type(_Tr::eof(), underflow())
			? _Tr::eof() : _Tr::to_int_type(*_Gninc())); }
	virtual streamsize xsgetn(_E * __S, streamsize __N)
		{int_type __C;
		streamsize _M, _Ns;
		for (_Ns = 0; 0 < __N; )
			if (gptr() != 0 && 0 < (_M = egptr() - gptr()))
				{if (__N < _M)
					_M = __N;
				_Tr::copy(__S, gptr(), _M);
				__S += _M, _Ns += _M, __N -= _M, gbump(_M); }
			else if (_Tr::eq_int_type(_Tr::eof(), __C = uflow()))
				break;
			else
				*__S++ = _Tr::to_char_type(__C), ++_Ns, --__N;
		return (_Ns); }
	virtual streamsize xsputn(const _E *__S, streamsize __N)
		{streamsize _M, _Ns;
		for (_Ns = 0; 0 < __N; )
			if (pptr() != 0 && 0 < (_M = epptr() - pptr()))
				{if (__N < _M)
					_M = __N;
				_Tr::copy(pptr(), __S, _M);
				__S += _M, _Ns += _M, __N -= _M, pbump(_M); }
			else if (_Tr::eq_int_type(_Tr::eof(),
				overflow(_Tr::to_int_type(*__S))))
				break;
			else
				++__S, ++_Ns, --__N;
		return (_Ns); }
	virtual pos_type seekoff(off_type, ios_base::seekdir,
		ios_base::openmode = ios_base::in | ios_base::out)
		{return (streampos(_BADOFF)); }
	virtual pos_type seekpos(pos_type,
		ios_base::openmode = ios_base::in | ios_base::out)
		{return (streampos(_BADOFF)); }
	virtual _Myt *setbuf(_E *, streamsize)
		{return (this); }
	virtual int sync()
		{return (0); }
	virtual void imbue(const locale& _Loc)
		{}
private:
	_E *_Gbeg, *_Pbeg;
	_E **_IGbeg, **_IPbeg;
	_E *_Gnext, *_Pnext;
	_E **_IGnext, **_IPnext;
	_E *_Gend, *_Pend;
	_E **_IGend, **_IPend;
	locale _Loc;
	};


#pragma arguments_in_registers(pop)






 
#line 35 "c:\\rm3dev\\incplus\\xlocnum"

extern "C" {
extern float _Stof(const char *, char **, long);
extern double _Stod(const char *, char **, long);
extern long double _Stold(const char *, char **, long);
}
		



#pragma       align   (_Istrit=4)             

class _Istrit {
public:
	typedef _Istrit _Myt;
	typedef char char_type;
	typedef char_traits traits_type;
	typedef traits_type::int_type int_type;
	typedef streambuf streambuf_type;
	_Istrit(streambuf_type *_Sb = 0) throw ()
		: _Sbuf(_Sb), _Got(_Sb == 0) {}
	const char_type& operator*() const
		{if (!_Got)
			((_Myt *)this)->_Peek();
		return (_Val); }
	_Myt& operator++()
		{_Inc();
		return (*this); }
	_Myt operator++(int)
		{if (!_Got)
			_Peek();
		_Myt _Tmp = *this;
		_Inc();
		return (_Tmp); }
	bool equal(const _Myt& __X) const
		{if (!_Got)
			((_Myt *)this)->_Peek();
		if (!__X._Got)
			((_Myt *)&__X)->_Peek();
		return (_Sbuf == 0 && __X._Sbuf == 0
			|| _Sbuf != 0 && __X._Sbuf != 0); }
private:
	void _Inc()
		{if (_Sbuf == 0
			|| traits_type::eq_int_type(traits_type::eof(),
				_Sbuf->sbumpc()))
			_Sbuf = 0, _Got = true;
		else
			_Got = false; }
	char_type _Peek()
		{int_type __C;
		if (_Sbuf == 0
			|| traits_type::eq_int_type(traits_type::eof(),
				__C = _Sbuf->sgetc()))
			_Sbuf = 0;
		else
			_Val = traits_type::to_char_type(__C);
		_Got = true;
		return (_Val); }
	streambuf_type *_Sbuf;
	bool _Got;
	char_type _Val;
	};
inline bool operator==(const _Istrit& __X, const _Istrit& _Y)
	{return (__X.equal(_Y)); }
inline bool operator!=(const _Istrit& __X, const _Istrit& _Y)
	{return (!(__X == _Y)); }
		



#pragma       align   (_Ostrit=4)             

class _Ostrit {
public:
	typedef _Ostrit _Myt;
	typedef char char_type;
	typedef char_traits traits_type;
	typedef streambuf streambuf_type;
	_Ostrit(streambuf_type *_Sb) throw ()
		: _Failed(false), _Sbuf(_Sb) {}
	_Myt& operator=(char_type __X)
		{if (_Sbuf == 0
			|| traits_type::eq_int_type(traits_type::eof(),
				_Sbuf->sputc(__X)))
			_Failed = true;
		return (*this); }
	_Myt& operator*()
		{return (*this); }
	_Myt& operator++()
		{return (*this); }
	_Myt& operator++(int)
		{return (*this); }
	bool failed() const throw ()
		{return (_Failed); }
private:
	bool _Failed;
	streambuf_type *_Sbuf;
	};

inline int _Getloctxt(_Istrit& _F, _Istrit& __L, size_t __N,
	const char *__S)
	{for (size_t _I = 0; __S[_I] != (char)0; ++_I)
		if (__S[_I] == __S[0])
			++__N;
	string _Str(__N, '\0');
	int _Ans = -2;
	for (size_t _J = 1; ; ++_J, ++_F, _Ans = -1)
		{bool  _Pfx;
		size_t _I, _K;
		for (_I = 0, _K = 0, _Pfx = false; _K < __N; ++_K)
			{for (; __S[_I] != (char)0 && __S[_I] != __S[0]; ++_I)
				;
			if (_Str[_K] != '\0')
				_I += _Str[_K];
			else if (__S[_I += _J] == __S[0] || __S[_I] == (char)0)
				{_Str[_K] = _J < 127 ? _J : 127;
				_Ans = _K; }
			else if (_F == __L || __S[_I] != *_F)
				_Str[_K] = _J < 127 ? _J : 127;
			else
				_Pfx = true; }
		if (!_Pfx || _F == __L)
			break; }
	return (_Ans); }
		



#pragma       align   (numpunct=4)            

class numpunct {
public:
	typedef string string_type;
	static char decimal_point()
		{return ('.'); }
	static char thousands_sep()
		{return ('\0'); }
	static string grouping()
		{return (""); }
	static string_type falsename()
		{return ("false"); }
	static string_type truename()
		{return ("true"); }
	};

		



#pragma       align   (num_get=4)             

class num_get {
public:
	typedef char _E;
	typedef _Istrit _II;
	typedef numpunct _Mypunct;
	typedef string _Mystr;
	typedef _E char_type;
	typedef _II iter_type;
	_II get(_II _F, _II __L, ios_base& __X, ios_base::iostate& _St,
		_Bool& _V) const
		{return (do_get(_F, __L, __X, _St, _V)); }
	_II get(_II _F, _II __L, ios_base& __X, ios_base::iostate& _St,
		unsigned short& _V) const
		{return (do_get(_F, __L, __X, _St, _V)); }
	_II get(_II _F, _II __L, ios_base& __X, ios_base::iostate& _St,
		unsigned int& _V) const
		{return (do_get(_F, __L, __X, _St, _V)); }
	_II get(_II _F, _II __L, ios_base& __X, ios_base::iostate& _St,
		long& _V) const
		{return (do_get(_F, __L, __X, _St, _V)); }
	_II get(_II _F, _II __L, ios_base& __X, ios_base::iostate& _St,
		unsigned long& _V) const
		{return (do_get(_F, __L, __X, _St, _V)); }
	_II get(_II _F, _II __L, ios_base& __X, ios_base::iostate& _St,
		float& _V) const
		{return (do_get(_F, __L, __X, _St, _V)); }
	_II get(_II _F, _II __L, ios_base& __X, ios_base::iostate& _St,
		double& _V) const
		{return (do_get(_F, __L, __X, _St, _V)); }
	_II get(_II _F, _II __L, ios_base& __X, ios_base::iostate& _St,
		long double& _V) const
		{return (do_get(_F, __L, __X, _St, _V)); }
	_II get(_II _F, _II __L, ios_base& __X, ios_base::iostate& _St,
		void *& _V) const
		{return (do_get(_F, __L, __X, _St, _V)); }
protected:
	 _II do_get(_II _F, _II __L, ios_base& __X,
		ios_base::iostate& _St, _Bool& _V) const
		{int _Ans = -1;
		if (__X.flags() & ios_base::boolalpha)
			{const _Mypunct& _Fac = _Mypunct();
			_Mystr _Str((_Mystr::size_type)1,
				(char_type)0);
			_Str += _Fac.falsename();
			_Str += (char_type)0;
			_Str += _Fac.truename();
			_Ans = _Getloctxt(_F, __L, (size_t)2, _Str.c_str()); }
		else
			{char _Ac[32], *_Ep;
			(*_xerrno()) = 0;
			const unsigned long _Ulo = strtoul(_Ac, &_Ep,
				_Getifld(_Ac, _F, __L, __X.flags(), __X.getloc()));
			if (_Ep != _Ac && (*_xerrno()) == 0 && _Ulo <= 1)
				_Ans = _Ulo; }
		if (_F == __L)
			_St |= ios_base::eofbit;
		if (_Ans < 0)
			_St |= ios_base::failbit;
		else
			_V = _Ans != 0;
		return (_F); }
	 _II do_get(_II _F, _II __L, ios_base& __X,
		ios_base::iostate& _St, unsigned short& _V) const
		{char _Ac[32], *_Ep;
		(*_xerrno()) = 0;
		int _Base =
			_Getifld(_Ac, _F, __L, __X.flags(), __X.getloc());
		char *__S = _Ac[0] == '-' ? _Ac + 1 : _Ac;
		const unsigned long _Ans = strtoul(__S, &_Ep, _Base);
		if (_F == __L)
			_St |= ios_base::eofbit;
		if (_Ep == __S || (*_xerrno()) != 0 || 65535u < _Ans)
			_St |= ios_base::failbit;
		else
			_V = _Ac[0] == '-' ? -_Ans : _Ans;
		return (_F); }
	 _II do_get(_II _F, _II __L, ios_base& __X,
		ios_base::iostate& _St, unsigned int& _V) const
		{char _Ac[32], *_Ep;
		(*_xerrno()) = 0;
		int _Base =
			_Getifld(_Ac, _F, __L, __X.flags(), __X.getloc());
		char *__S = _Ac[0] == '-' ? _Ac + 1 : _Ac;
		const unsigned long _Ans = strtoul(__S, &_Ep, _Base);
		if (_F == __L)
			_St |= ios_base::eofbit;
		if (_Ep == __S || (*_xerrno()) != 0 || 4294967295u < _Ans)
			_St |= ios_base::failbit;
		else
			_V = _Ac[0] == '-' ? -_Ans : _Ans;
		return (_F); }
	 _II do_get(_II _F, _II __L, ios_base& __X,
		ios_base::iostate& _St, long& _V) const
		{char _Ac[32], *_Ep;
		(*_xerrno()) = 0;
		const long _Ans = strtol(_Ac, &_Ep,
			_Getifld(_Ac, _F, __L, __X.flags(), __X.getloc()));
		if (_F == __L)
			_St |= ios_base::eofbit;
		if (_Ep == _Ac || (*_xerrno()) != 0)
			_St |= ios_base::failbit;
		else
			_V = _Ans;
		return (_F); }
	 _II do_get(_II _F, _II __L, ios_base& __X,
		ios_base::iostate& _St, unsigned long& _V) const
		{char _Ac[32], *_Ep;
		(*_xerrno()) = 0;
		const unsigned long _Ans = strtoul(_Ac, &_Ep,
			_Getifld(_Ac, _F, __L, __X.flags(), __X.getloc()));
		if (_F == __L)
			_St |= ios_base::eofbit;
		if (_Ep == _Ac || (*_xerrno()) != 0)
			_St |= ios_base::failbit;
		else
			_V = _Ans;
		return (_F); }
	 _II do_get(_II _F, _II __L, ios_base& __X,
		ios_base::iostate& _St, float& _V) const
		{char _Ac[8 + 36 + 16], *_Ep;
		(*_xerrno()) = 0;
		const float _Ans = _Stof(_Ac, &_Ep,
			_Getffld(_Ac, _F, __L, __X.getloc()));
		if (_F == __L)
			_St |= ios_base::eofbit;
		if (_Ep == _Ac || (*_xerrno()) != 0)
			_St |= ios_base::failbit;
		else
			_V = _Ans;
		return (_F); }
	 _II do_get(_II _F, _II __L, ios_base& __X,
		ios_base::iostate& _St, double& _V) const
		{char _Ac[8 + 36 + 16], *_Ep;
		(*_xerrno()) = 0;
		const double _Ans = _Stod(_Ac, &_Ep,
			_Getffld(_Ac, _F, __L, __X.getloc()));
		if (_F == __L)
			_St |= ios_base::eofbit;
		if (_Ep == _Ac || (*_xerrno()) != 0)
			_St |= ios_base::failbit;
		else
			_V = _Ans;
		return (_F); }
	 _II do_get(_II _F, _II __L, ios_base& __X,
		ios_base::iostate& _St, long double& _V) const
		{char _Ac[8 + 36 + 16], *_Ep;
		(*_xerrno()) = 0;
		const long double _Ans = _Stold(_Ac, &_Ep,
			_Getffld(_Ac, _F, __L, __X.getloc()));
		if (_F == __L)
			_St |= ios_base::eofbit;
		if (_Ep == _Ac || (*_xerrno()) != 0)
			_St |= ios_base::failbit;
		else
			_V = _Ans;
		return (_F); }
	 _II do_get(_II _F, _II __L, ios_base& __X,
		ios_base::iostate& _St, void *& _V) const
		{union _Pvlo {
			void *_Pv;
			unsigned long _Lo[1 +
				(sizeof (void *) - 1) / sizeof (unsigned long)];
			} __U;
		const int _NL = sizeof (__U._Lo) / sizeof (unsigned long);
		for (int _I = 0; ; ++_F)
			{char _Ac[32], *_Ep;
			(*_xerrno()) = 0;
			__U._Lo[_I] = strtoul(_Ac, &_Ep,
				_Getifld(_Ac, _F, __L,
					ios_base::hex, __X.getloc()));
			if (_F == __L)
				_St |= ios_base::eofbit;
			if (_Ep == _Ac || (*_xerrno()) != 0)
				{_St |= ios_base::failbit;
				break; }
			if (_NL <= ++_I)
				break;
			if (_F == __L || *_F != ((_E)(':')))
				{_St |= ios_base::failbit;
				break; }}
		if (!(_St & ios_base::failbit))
			_V = __U._Pv;
		return (_F); }
private:
	static int _Getifld(char *_Ac, _II& _F, _II& __L,
		ios_base::fmtflags _Bfl, const locale& _Loc)
		{const _E _E0 = ((_E)('0'));
		const _Mypunct& _Fac = _Mypunct();
		const string _Gr = _Fac.grouping();
		const _E _Ks = _Fac.thousands_sep();
		char *__P = _Ac;
		if (_F == __L)
			;
		else if (*_F == ((_E)('+')))
			*__P++ = '+', ++_F;
		else if (*_F == ((_E)('-')))
			*__P++ = '-', ++_F;
		_Bfl &= ios_base::basefield;
		int _Base = _Bfl == ios_base::oct ? 8
			: _Bfl == ios_base::hex ? 16
			: _Bfl == ios_base::_Fmtzero ? 0 : 10;
		bool _Sd = false, _Snz = false;
		if (_F != __L && *_F == _E0)
			{_Sd = true, ++_F;
			if (_F != __L && (*_F == ((_E)('x'))
					|| *_F == ((_E)('X')))
				&& (_Base == 0 || _Base == 16))
				_Base = 16, _Sd = false, ++_F;
			else if (_Base == 0)
				_Base = 8; }
		int _Dlen = _Base == 0 || _Base == 10 ? 10
			: _Base == 8 ? 8 : 16 + 6;
		string _Grin((size_t)1, (char)(_Sd ? '\1' : '\0'));
		size_t _I = 0;
		for (char *const _Pe = &_Ac[32 - 1];
			_F != __L; ++_F)
			if (memchr("0123456789abcdefABCDEF",
				*__P = ((_E)(*_F)), _Dlen) != 0)
				{if ((_Snz || *__P != '0') && __P < _Pe)
					++__P, _Snz = true;
				_Sd = true;
				if (_Grin[_I] != 127)
					++_Grin[_I]; }
			else if (_Grin[_I] == '\0' || _Ks == (_E)0
				|| *_F != _Ks)
				break;
			else
				_Grin.append((string::size_type)1, '\0'), ++_I;
		if (_I == 0)
			;
		else if ('\0' < _Grin[_I])
			++_I;
		else
			_Sd = false;
		for (const char *_Pg = _Gr.c_str(); _Sd && 0 < _I; )
			if (*_Pg == 127)
				break;
			else if (0 < --_I && *_Pg != _Grin[_I]
				|| 0 == _I && *_Pg < _Grin[_I])
				_Sd = false;
			else if ('\0' < _Pg[1])
				++_Pg;
		if (_Sd && !_Snz)
			*__P++ = '0';
		else if (!_Sd)
			__P = _Ac;
		*__P = '\0';
		return (_Base);
		}
	static int _Getffld(char *_Ac, _II& _F, _II &__L,
		const locale& _Loc)
		{const _E _E0 = ((_E)('0'));
		const _Mypunct& _Fac = _Mypunct();
		char *__P = _Ac;
		if (_F == __L)
			;
		else if (*_F == ((_E)('+')))
			*__P++ = '+', ++_F;
		else if (*_F == ((_E)('-')))
			*__P++ = '-', ++_F;
		bool _Sd = false;
		for (; _F != __L && *_F == _E0; _Sd = true, ++_F)
			;
		if (_Sd)
			*__P++ = '0';
		int _Ns = 0;
		int _Pten = 0;
		for (; _F != __L && ( __chattr((char)((*__P = ((_E)(*_F))) & 0xFF)) & (0x0002) );
			_Sd = true, ++_F)
			if (_Ns < 36)
				++__P, ++_Ns;
			else
				++_Pten;
		if (_F != __L && *_F == _Fac.decimal_point())
			*__P++ = localeconv()->decimal_point[0], ++_F;
		if (_Ns == 0)
			{for (; _F != __L && *_F == _E0; _Sd = true, ++_F)
				--_Pten;
			if (_Pten < 0)
				*__P++ = '0', ++_Pten; }
		for (; _F != __L && ( __chattr((char)((*__P = ((_E)(*_F))) & 0xFF)) & (0x0002) );
			_Sd = true, ++_F)
			if (_Ns < 36)
				++__P, ++_Ns;
		if (_Sd && _F != __L
			&& (*_F == ((_E)('e')) || *_F == ((_E)('E'))))
			{*__P++ = 'e', ++_F;
			_Sd = false, _Ns = 0;
			if (_F == __L)
				;
			else if (*_F == ((_E)('+')))
				*__P++ = '+', ++_F;
			else if (*_F == ((_E)('-')))
				*__P++ = '-', ++_F;
			for (; _F != __L && *_F == _E0; _Sd = true, ++_F)
				;
			if (_Sd)
				*__P++ = '0';
			for (; _F != __L
				&& ( __chattr((char)((*__P = ((_E)(*_F))) & 0xFF)) & (0x0002) );
				_Sd = true, ++_F)
				if (_Ns < 8)
					++__P, ++_Ns; }
		if (!_Sd)
			__P = _Ac;
		*__P = '\0';
		return (_Pten);
		};
	};
		



#pragma       align   (num_put=4)                     

class num_put {
public:
	typedef char _E;
	typedef _Ostrit _OI;
	typedef numpunct _Mypunct;
	typedef string _Mystr;
	typedef _E char_type;
	typedef _OI iter_type;
	_OI put(_OI _F, ios_base& __X, _E _Fill,
		_Bool _V) const
		{return (do_put(_F, __X, _Fill, _V)); }
	_OI put(_OI _F, ios_base& __X, _E _Fill,
		long _V) const
		{return (do_put(_F, __X, _Fill, _V)); }
	_OI put(_OI _F, ios_base& __X, _E _Fill,
		unsigned long _V) const
		{return (do_put(_F, __X, _Fill, _V)); }
	_OI put(_OI _F, ios_base& __X, _E _Fill,
		double _V) const
		{return (do_put(_F, __X, _Fill, _V)); }
	_OI put(_OI _F, ios_base& __X, _E _Fill,
		long double _V) const
		{return (do_put(_F, __X, _Fill, _V)); }
	_OI put(_OI _F, ios_base& __X, _E _Fill,
		const void *_V) const
		{return (do_put(_F, __X, _Fill, _V)); }
protected:
	virtual _OI do_put(_OI _F, ios_base& __X, _E _Fill,
		_Bool _V) const
		{const _Mypunct& _Fac = _Mypunct();
		_Mystr _Str;
		if (!(__X.flags() & ios_base::boolalpha))
			_Str.append((_Mystr::size_type)1,
				((_E)(_V ? '1' : '0')));
		else if (_V)
			_Str = _Fac.truename();
		else
			_Str = _Fac.falsename();
		size_t _M = __X.width() <= 0 || __X.width() <= _Str.size()
			? 0 : __X.width() - _Str.size();
		ios_base::fmtflags _Afl =
			__X.flags() & ios_base::adjustfield;
		if (_Afl != ios_base::left)
			_F = _Rep(_F, _Fill, _M), _M = 0;
		_F = _Put(_F, _Str.c_str(), _Str.size());
		__X.width(0);
		return (_Rep(_F, _Fill, _M)); }
	virtual _OI do_put(_OI _F, ios_base& __X, _E _Fill,
		long _V) const
		{char _Buf[2 * 32], _Fmt[6];
		return (_Iput(_F, __X, _Fill, _Buf,
			sprintf(_Buf, _Ifmt(_Fmt, 'd', __X.flags()), _V))); }
	virtual _OI do_put(_OI _F, ios_base& __X, _E _Fill,
		unsigned long _V) const
		{char _Buf[2 * 32], _Fmt[6];
		return (_Iput(_F, __X, _Fill, _Buf,
			sprintf(_Buf, _Ifmt(_Fmt, 'u', __X.flags()), _V))); }
	virtual _OI do_put(_OI _F, ios_base& __X, _E _Fill,
		double _V) const
		{char _Buf[8 + 36 + 16], _Fmt[8];
		streamsize _Prec = __X.precision() <= 0
			&& !(__X.flags() & ios_base::fixed) ? 6
			: __X.precision();
		int _Mpr = 36 < _Prec ? 36 : _Prec;
		return (_Fput(_F, __X, _Fill, _Buf, _Prec - _Mpr,
			sprintf(_Buf, _Ffmt(_Fmt, 0, __X.flags()),
				_Mpr, _V))); }
	virtual _OI do_put(_OI _F, ios_base& __X, _E _Fill,
		long double _V) const
		{char _Buf[8 + 36 + 16], _Fmt[8];
		streamsize _Prec = __X.precision() <= 0
			&& !(__X.flags() & ios_base::fixed) ? 6
			: __X.precision();
		int _Mpr = 36 < _Prec ? 36 : _Prec;
		return (_Fput(_F, __X, _Fill, _Buf, _Prec - _Mpr,
			sprintf(_Buf, _Ffmt(_Fmt, 'L', __X.flags()),
				_Mpr, _V))); }
	virtual _OI do_put(_OI _F, ios_base& __X, _E _Fill,
		const void *_V) const
		{
		const int _NL = 1
			+ (sizeof (void *) - 1) / sizeof (unsigned long);
		char _Buf[(_NL + 1) * (32 + 1)];
		int __N = sprintf(_Buf, "%p", _V);
		size_t _M = __X.width() <= 0 || __X.width() <= __N
			? 0 : __X.width() - __N;
		ios_base::fmtflags _Afl =
			__X.flags() & ios_base::adjustfield;
		if (_Afl != ios_base::left)
			_F = _Rep(_F, _Fill, _M), _M = 0;
		_F = _Putc(_F, _Buf, __N);
		__X.width(0);
		return (_Rep(_F, _Fill, _M)); }
	static char *_Ffmt(char *_Fmt, char _Spec,
		ios_base::fmtflags _Fl)
		{char *__S = _Fmt;
		*__S++ = '%';
		if (_Fl & ios_base::showpos)
			*__S++ = '+';
		if (_Fl & ios_base::showpoint)
			*__S++ = '#';
		*__S++ = '.';
		*__S++ = '*';
		if (_Spec != 0)
			*__S++ = _Spec;	
		ios_base::fmtflags _Ffl = _Fl & ios_base::floatfield;
		*__S++ = _Ffl == ios_base::fixed ? 'f'
			: _Ffl == ios_base::scientific ? 'e' : 'g';
		*__S = '\0';
		return (_Fmt); }
	static _OI _Fput(_OI _F, ios_base& __X, _E _Fill,
		const char *__S, size_t _Nz, size_t __N)
		{size_t _M = __X.width() <= 0 || __X.width() <= __N  + _Nz
			? 0 : __X.width() - __N - _Nz;
		ios_base::fmtflags _Afl =
			__X.flags() & ios_base::adjustfield;
		if (_Afl != ios_base::left && _Afl != ios_base::internal)
			_F = _Rep(_F, _Fill, _M), _M = 0;
		else if (_Afl == ios_base::internal)
			{if (0 < __N && (*__S == '+' || *__S == '-'))
				_F = _Putc(_F, __S, 1), ++__S, --__N;
			_F = _Rep(_F, _Fill, _M), _M = 0; }
		const char *__P = (const char *)memchr(__S,
			localeconv()->decimal_point[0], __N);
		if (__P != 0)
			{const _Mypunct& _Fac = _Mypunct();
			size_t _Nf = __P - __S + 1;
			_F = _Putc(_F, __S, _Nf - 1);
			_F = _Rep(_F, _Fac.decimal_point(), 1);
			__S += _Nf, __N -= _Nf; }
		if ((__P = (const char *)memchr(__S, 'e', __N)) != 0)
			{size_t _Nm = __P - __S + 1;
			_F = _Putc(_F, __S, _Nm - 1);
			_F = _Rep(_F, ((_E)('0')), _Nz), _Nz = 0;
			_F = _Putc(_F, __X.flags() & ios_base::uppercase
				? "E" : "e", 1);
			__S += _Nm, __N -= _Nm; }
		_F = _Putc(_F, __S, __N);
		_F = _Rep(_F, ((_E)('0')), _Nz);
		__X.width(0);
		return (_Rep(_F, _Fill, _M)); }
	static char *_Ifmt(char *_Fmt, char _Spec,
		ios_base::fmtflags _Fl)
		{char *__S = _Fmt;
		*__S++ = '%';
		if (_Fl & ios_base::showpos)
			*__S++ = '+';
		if (_Fl & ios_base::showbase)
			*__S++ = '#';
		*__S++ = 'l';
		ios_base::fmtflags _Bfl = _Fl & ios_base::basefield;
		*__S++ = _Bfl == ios_base::oct ? 'o'
			: _Bfl != ios_base::hex ? _Spec	
			: _Fl & ios_base::uppercase ? 'X' : 'x';
		*__S = '\0';
		return (_Fmt); }
	static _OI _Iput(_OI _F, ios_base& __X, _E _Fill,
		char *__S, size_t __N)
		{const size_t _Np = *__S == '+' || *__S == '-' ? 1
			: *__S == '0' && (__S[1] == 'x' || __S[1] == 'X') ? 2
			: 0;
		const _Mypunct& _Fac = _Mypunct();
		const string _Gr = _Fac.grouping();
		const _E _Ks = _Fac.thousands_sep();
		bool _Grp = '\0' < *_Gr.c_str();
		if (_Grp)
			{const char *_Pg = _Gr.c_str();
			size_t _I = __N;
			for (_Grp = false; *_Pg != 127 && '\0' < *_Pg
				&& *_Pg < _I - _Np; _Grp = true)
				{_I -= *_Pg;
				memmove(&__S[_I + 1], &__S[_I], __N + 1 - _I);
				__S[_I] = ',', ++__N;
				if ('\0' < _Pg[1])
					++_Pg; }}
		size_t _M = __X.width() <= 0 || __X.width() <= __N
			? 0 : __X.width() - __N;
		ios_base::fmtflags _Afl =
			__X.flags() & ios_base::adjustfield;
		if (_Afl != ios_base::left && _Afl != ios_base::internal)
			_F = _Rep(_F, _Fill, _M), _M = 0;
		else if (_Afl == ios_base::internal)
			{_F = _Putc(_F, __S, _Np), __S += _Np, __N -= _Np;
			_F = _Rep(_F, _Fill, _M), _M = 0; }
		if (!_Grp)
			_F = _Putc(_F, __S, __N);
		else
			for (; ; ++__S, --__N)
				{size_t _Nd = strcspn(__S, ",");
				_F = _Putc(_F, __S, _Nd);
				__S += _Nd, __N -= _Nd;
				if (__N == 0)
					break;
				if (_Ks != (_E)0)
					_F = _Rep(_F, _Ks, 1); }
		__X.width(0);
		return (_Rep(_F, _Fill, _M)); }
	static _OI _Put(_OI _F, const _E *__S, size_t __N)
		{for (; 0 < __N; --__N, ++_F, ++__S)
			*_F = *__S;
		return (_F); }
	static _OI _Putc(_OI _F, const char *__S, size_t __N)
		{for (; 0 < __N; --__N, ++_F, ++__S)
			*_F = ((_E)(*__S));
		return (_F); }
	static _OI _Rep(_OI _F, _E __C, size_t __N)
		{for (; 0 < __N; --__N, ++_F)
			*_F = __C;
		return (_F); }
	};


#pragma arguments_in_registers(pop)






 
#line 31 "c:\\rm3dev\\incplus\\ios"

		



#pragma       align   (ios=4)         

class ios: public ios_base {
public:
	typedef char _E;
	typedef char_traits _Tr;
	typedef ios _Myt;
	typedef ostream _Myos;
	typedef streambuf _Mysb;
	typedef ctype _Ctype;
	explicit ios(_Mysb *__S)
		{init(__S); }
	virtual ~ios()
		{}
	typedef _E char_type;
	typedef _Tr traits_type;
	typedef _Tr::int_type int_type;
	typedef _Tr::pos_type pos_type;
	typedef _Tr::off_type off_type;
	void clear(iostate _St = goodbit, bool _Ex = false)
		{ios_base::clear((iostate)(_Sb == 0
			? (int)_St | (int)badbit : (int)_St), _Ex); }
	void clear(io_state _St)
		{clear((iostate)_St); }
	void setstate(iostate _St, bool _Ex = false)
		{if (_St != goodbit)
			clear((iostate)((int)rdstate() | (int)_St), _Ex); }
	void setstate(io_state _St)
		{setstate((iostate)_St); }
	_Myt& copyfmt(const _Myt& _R)
		{_Tiestr = _R.tie();
		_Fillch = _R.fill();
		ios_base::copyfmt(_R);
		return (*this); }
	_Myos *tie() const
		{return (_Tiestr); }
	_Myos *tie(_Myos *__N)
		{_Myos *_O = _Tiestr;
		_Tiestr = __N;
		tie_sem();
		return (_O); }
	virtual	void	tie_sem(void) = 0;
	_Mysb *rdbuf() const
		{return (_Sb); }
	_Mysb *rdbuf(_Mysb *__N)
		{_Mysb *_O = _Sb;
		_Sb = __N;
		clear();
		return (_O); }
	locale imbue(const locale& _Ln)
		{if (rdbuf() != 0)
			rdbuf()->pubimbue(_Ln);
		return (ios_base::imbue(_Ln)); }
	_E fill() const
		{return (_Fillch); }
	_E fill(_E _Nf)
		{_E _Of = _Fillch;
		_Fillch = _Nf;
		return (_Of); }
	char narrow(_E __C, char _D = '\0') const
		{const _Ctype& _Fac = _Ctype();
		return (_Fac.narrow(__C, _D)); }
	_E widen(char __C) const
		{const _Ctype& _Fac = _Ctype();
		return (_Fac.widen(__C)); }
protected:
	void init(_Mysb *__S = 0,
		bool _Isstd = false)
		{_Sb = __S;
		_Tiestr = 0;
		_Fillch = ((_E)(' '));
		_Init();
		if (_Sb == 0)
			setstate(badbit);
		if (_Isstd)
			_Addstd(); }
	ios()
		{}
private:
	ios(const _Myt&);	
	ios& operator=(const _Myt&);	
	_Mysb *_Sb;
	_Myos *_Tiestr;
	_E _Fillch;
	};
		
inline ios_base& boolalpha(ios_base& _I)
	{_I.setf(ios_base::boolalpha);
	return (_I); }
inline ios_base& dec(ios_base& _I)
	{_I.setf(ios_base::dec, ios_base::basefield);
	return (_I); }
inline ios_base& fixed(ios_base& _I)
	{_I.setf(ios_base::fixed, ios_base::floatfield);
	return (_I); }
inline ios_base& hex(ios_base& _I)
	{_I.setf(ios_base::hex, ios_base::basefield);
	return (_I); }
inline ios_base& internal(ios_base& _I)
	{_I.setf(ios_base::internal, ios_base::adjustfield);
	return (_I); }
inline ios_base& left(ios_base& _I)
	{_I.setf(ios_base::left, ios_base::adjustfield);
	return (_I); }
inline ios_base& noboolalpha(ios_base& _I)
	{_I.unsetf(ios_base::boolalpha);
	return (_I); }
inline ios_base& noshowbase(ios_base& _I)
	{_I.unsetf(ios_base::showbase);
	return (_I); }
inline ios_base& noshowpoint(ios_base& _I)
	{_I.unsetf(ios_base::showpoint);
	return (_I); }
inline ios_base& noshowpos(ios_base& _I)
	{_I.unsetf(ios_base::showpos);
	return (_I); }
inline ios_base& noskipws(ios_base& _I)
	{_I.unsetf(ios_base::skipws);
	return (_I); }
inline ios_base& nounitbuf(ios_base& _I)
	{_I.unsetf(ios_base::unitbuf);
	return (_I); }
inline ios_base& nouppercase(ios_base& _I)
	{_I.unsetf(ios_base::uppercase);
	return (_I); }
inline ios_base& oct(ios_base& _I)
	{_I.setf(ios_base::oct, ios_base::basefield);
	return (_I); }
inline ios_base& right(ios_base& _I)
	{_I.setf(ios_base::right, ios_base::adjustfield);
	return (_I); }
inline ios_base& scientific(ios_base& _I)
	{_I.setf(ios_base::scientific, ios_base::floatfield);
	return (_I); }
inline ios_base& showbase(ios_base& _I)
	{_I.setf(ios_base::showbase);
	return (_I); }
inline ios_base& showpoint(ios_base& _I)
	{_I.setf(ios_base::showpoint);
	return (_I); }
inline ios_base& showpos(ios_base& _I)
	{_I.setf(ios_base::showpos);
	return (_I); }
inline ios_base& skipws(ios_base& _I)
	{_I.setf(ios_base::skipws);
	return (_I); }
inline ios_base& unitbuf(ios_base& _I)
	{_I.setf(ios_base::unitbuf);
	return (_I); }
inline ios_base& uppercase(ios_base& _I)
	{_I.setf(ios_base::uppercase);
	return (_I); }


#pragma arguments_in_registers(pop)






 
#line 30 "c:\\rm3dev\\incplus\\ostream"
		
#line 42 "c:\\rm3dev\\incplus\\ostream"

		



#pragma       align   (ostream=4)                     

class ostream: public ios {
public:
	typedef char _E;
	typedef char_traits _Tr;
	typedef ostream _Myt;
	typedef ios _Myios;
	typedef streambuf _Mysb;
	typedef _Ostrit _Iter;
	typedef num_put _Nput;
	explicit ostream(streambuf *__S,
		bool _Isstd = false)
		{init(__S, _Isstd); }
	ostream(_Uninitialized)
		{_Addstd(); }
	virtual ~ostream()
		{}
	typedef _Tr::int_type int_type;
	typedef _Tr::pos_type pos_type;
	typedef _Tr::off_type off_type;
	class sentry {
	public:
		explicit sentry(_Myt& _Os)
			 
			: _Lk(2,&_Os._ios_sem), _Ostr(_Os)
			{if (_Os.good() && _Os.tie() != 0)
				_Os.tie()->flush();
			_Ok = _Os.good(); }
		~sentry()
			{_Ostr.osfx(); }
		operator bool() const
			{return (_Ok); }
	private:
		sentry(const sentry&);	
		sentry& operator=(const sentry&);	
		bool _Ok;
		_Lockit _Lk;
		_Myt& _Ostr;
		};
	bool opfx()
		{if (ios_base::good() && _Myios::tie() != 0)
			_Myios::tie()->flush();
		return (ios_base::good()); }
	void osfx()
		{if (ios_base::flags() & ios_base::unitbuf)
			flush(); }
	_Myt& operator<<(_Myt& (*_F)(_Myt&))
		{return ((*_F)(*this)); }
	_Myt& operator<<(_Myios& (*_F)(_Myios&))
		{(*_F)(*(_Myios *)this);
		return (*this); }
	_Myt& operator<<(ios_base& (*_F)(ios_base&))
		{(*_F)(*(ios_base *)this);
		return (*this); }
	_Myt& operator<<(_Bool __X)
		{ios_base::iostate _St = ios_base::goodbit;
		const sentry _Ok(*this);
		if (_Ok)
			{const _Nput& _Fac = _Nput();
			try {
			if (_Fac.put(_Iter(_Myios::rdbuf()), *this,
				_Myios::fill(), __X).failed())
				_St |= ios_base::badbit;
			} catch (...) { _Myios::setstate(ios_base::badbit, true); } }
		_Myios::setstate(_St);
		return (*this); }
	_Myt& operator<<(short __X)
		{ios_base::iostate _St = ios_base::goodbit;
		const sentry _Ok(*this);
		if (_Ok)
			{const _Nput& _Fac = _Nput();
			ios_base::fmtflags _Bfl =
				ios_base::flags() & ios_base::basefield;
			long _Y = (_Bfl == oct || _Bfl == hex)
				? (long)(unsigned short)__X : (long)__X;
			try {
			if (_Fac.put(_Iter(_Myios::rdbuf()), *this,
				_Myios::fill(), _Y).failed())
				_St |= ios_base::badbit;
			} catch (...) { _Myios::setstate(ios_base::badbit, true); } }
		_Myios::setstate(_St);
		return (*this); }
	_Myt& operator<<(unsigned short __X)
		{ios_base::iostate _St = ios_base::goodbit;
		const sentry _Ok(*this);
		if (_Ok)
			{const _Nput& _Fac = _Nput();
			try {
			if (_Fac.put(_Iter(_Myios::rdbuf()), *this,
				_Myios::fill(), (unsigned long)__X).failed())
				_St |= ios_base::badbit;
			} catch (...) { _Myios::setstate(ios_base::badbit, true); } }
		_Myios::setstate(_St);
		return (*this); }
	_Myt& operator<<(int __X)
		{ios_base::iostate _St = ios_base::goodbit;
		const sentry _Ok(*this);
		if (_Ok)
			{const _Nput& _Fac = _Nput();
			ios_base::fmtflags _Bfl =
				ios_base::flags() & ios_base::basefield;
			long _Y = (_Bfl == oct || _Bfl == hex)
				? (long)(unsigned int)__X : (long)__X;
			try {
			if (_Fac.put(_Iter(_Myios::rdbuf()), *this,
				_Myios::fill(), _Y).failed())
				_St |= ios_base::badbit;
			} catch (...) { _Myios::setstate(ios_base::badbit, true); } }
		_Myios::setstate(_St);
		return (*this); }
	_Myt& operator<<(unsigned int __X)
		{ios_base::iostate _St = ios_base::goodbit;
		const sentry _Ok(*this);
		if (_Ok)
			{const _Nput& _Fac = _Nput();
			try {
			if (_Fac.put(_Iter(_Myios::rdbuf()), *this,
				_Myios::fill(), (unsigned long)__X).failed())
				_St |= ios_base::badbit;
			} catch (...) { _Myios::setstate(ios_base::badbit, true); } }
		_Myios::setstate(_St);
		return (*this); }
	_Myt& operator<<(long __X)
		{ios_base::iostate _St = ios_base::goodbit;
		const sentry _Ok(*this);
		if (_Ok)
			{const _Nput& _Fac = _Nput();
			try {
			if (_Fac.put(_Iter(_Myios::rdbuf()), *this,
				_Myios::fill(), __X).failed())
				_St |= ios_base::badbit;
			} catch (...) { _Myios::setstate(ios_base::badbit, true); } }
		_Myios::setstate(_St);
		return (*this); }
	_Myt& operator<<(unsigned long __X)
		{ios_base::iostate _St = ios_base::goodbit;
		const sentry _Ok(*this);
		if (_Ok)
			{const _Nput& _Fac = _Nput();
			try {
			if (_Fac.put(_Iter(_Myios::rdbuf()), *this,
				_Myios::fill(), __X).failed())
				_St |= ios_base::badbit;
			} catch (...) { _Myios::setstate(ios_base::badbit, true); } }
		_Myios::setstate(_St);
		return (*this); }
	_Myt& operator<<(float __X)
		{ios_base::iostate _St = ios_base::goodbit;
		const sentry _Ok(*this);
		if (_Ok)
			{const _Nput& _Fac = _Nput();
			try {
			if (_Fac.put(_Iter(_Myios::rdbuf()), *this,
				_Myios::fill(), (double)__X).failed())
				_St |= ios_base::badbit;
			} catch (...) { _Myios::setstate(ios_base::badbit, true); } }
		_Myios::setstate(_St);
		return (*this); }
	_Myt& operator<<(double __X)
		{ios_base::iostate _St = ios_base::goodbit;
		const sentry _Ok(*this);
		if (_Ok)
			{const _Nput& _Fac = _Nput();
			try {
			if (_Fac.put(_Iter(_Myios::rdbuf()), *this,
				_Myios::fill(), __X).failed())
				_St |= ios_base::badbit;
			} catch (...) { _Myios::setstate(ios_base::badbit, true); } }
		_Myios::setstate(_St);
		return (*this); }
	_Myt& operator<<(long double __X)
		{ios_base::iostate _St = ios_base::goodbit;
		const sentry _Ok(*this);
		if (_Ok)
			{const _Nput& _Fac = _Nput();
			try {
			if (_Fac.put(_Iter(_Myios::rdbuf()), *this,
				_Myios::fill(), __X).failed())
				_St |= ios_base::badbit;
			} catch (...) { _Myios::setstate(ios_base::badbit, true); } }
		_Myios::setstate(_St);
		return (*this); }
	_Myt& operator<<(const void *__X)
		{ios_base::iostate _St = ios_base::goodbit;
		const sentry _Ok(*this);
		if (_Ok)
			{const _Nput& _Fac = _Nput();
			try {
			if (_Fac.put(_Iter(_Myios::rdbuf()), *this,
				_Myios::fill(), __X).failed())
				_St |= ios_base::badbit;
			} catch (...) { _Myios::setstate(ios_base::badbit, true); } }
		_Myios::setstate(_St);
		return (*this); }
	_Myt& operator<<(_Mysb *_Pb)
		{ios_base::iostate _St = ios_base::goodbit;
		bool _Copied = false;
		const sentry _Ok(*this);
		if (_Ok && _Pb != 0)
			for (int_type __C = _Tr::eof(); ; _Copied = true)
				{try {
				__C = _Tr::eq_int_type(_Tr::eof(), __C)
					? _Pb->sgetc() : _Pb->snextc();
				} catch (...) {
					_Myios::setstate(ios_base::failbit);
					throw;
				}
				if (_Tr::eq_int_type(_Tr::eof(),__C))
					break;
				try {
					if (_Tr::eq_int_type(_Tr::eof(),
						_Myios::rdbuf()->sputc(
							_Tr::to_char_type(__C))))
						{_St |= ios_base::badbit;
						break; }
				} catch (...) { _Myios::setstate(ios_base::badbit, true); } }
		ios_base::width(0);
		_Myios::setstate(!_Copied
			? _St | ios_base::failbit : _St);
		return (*this); }
	_Myt& put(_E __X)
		{ios_base::iostate _St = ios_base::goodbit;
		const sentry _Ok(*this);
		if (!_Ok)
			_St |= ios_base::badbit;
		else
			{try {
			 if (_Tr::eq_int_type(_Tr::eof(),
				_Myios::rdbuf()->sputc(__X)))
				_St |= ios_base::badbit;
			} catch (...) { _Myios::setstate(ios_base::badbit, true); } }
		_Myios::setstate(_St);
		return (*this); }
	_Myt& write(const _E *__S, streamsize __N)
		{ios_base::iostate _St = ios_base::goodbit;
		const sentry _Ok(*this);
		if (!_Ok)
			_St |= ios_base::badbit;
		else
			{try {
			if (_Myios::rdbuf()->sputn(__S, __N) != __N)
				_St |= ios_base::badbit;
			} catch (...) { _Myios::setstate(ios_base::badbit, true); } }
		_Myios::setstate(_St);
		return (*this); }
	_Myt& flush()
		{ios_base::iostate _St = ios_base::goodbit;
		if (!ios_base::fail()
			&& _Myios::rdbuf()->pubsync() == -1)
			_St |= ios_base::badbit;
		_Myios::setstate(_St);
		return (*this); }
	_Myt& seekp(pos_type __P)
		{if (!ios_base::fail())
			_Myios::rdbuf()->pubseekpos(__P, ios_base::out);
		return (*this); }
	_Myt& seekp(off_type _O, ios_base::seekdir _W)
		{if (!ios_base::fail())
			_Myios::rdbuf()->pubseekoff(_O, _W, ios_base::out);
		return (*this); }
	pos_type tellp()
		{if (!ios_base::fail())
			return (_Myios::rdbuf()->pubseekoff(0,
				ios_base::cur, ios_base::out));
		else
			return (pos_type(_BADOFF)); }
protected:
	



 
        void    tie_sem(void) {
                __cadul_share_critical_section_lock((void *)&_ios_sem,
                                           (void *)&(tie()->_ios_sem));
        }
	};
		
inline ostream& operator<<(ostream& _O, const char *__X)
	{typedef char _E;
	typedef char_traits _Tr;
	typedef ostream _Myos;
	ios_base::iostate _St = ios_base::goodbit;
	size_t __N = _Tr::length(__X);
	size_t _M = _O.width() <= 0 || _O.width() <= __N
		? 0 : _O.width() - __N;
	const _Myos::sentry _Ok(_O);
	if (!_Ok)
		_St |= ios_base::badbit;
	else
		{try {
		if ((_O.flags() & ios_base::adjustfield)
			!= ios_base::left)
			for (; 0 < _M; --_M)
				if (_Tr::eq_int_type(_Tr::eof(),
					_O.rdbuf()->sputc(_O.fill())))
					{_St |= ios_base::badbit;
					break; }
		if (_St == ios_base::goodbit
			&& _O.rdbuf()->sputn(__X, __N) != __N)
			_St |= ios_base::badbit;
		if (_St == ios_base::goodbit)
			for (; 0 < _M; --_M)
				if (_Tr::eq_int_type(_Tr::eof(),
					_O.rdbuf()->sputc(_O.fill())))
					{_St |= ios_base::badbit;
					break; }
		_O.width(0);
		} catch (...) { (_O). setstate(ios_base::badbit, true); } }
	_O.setstate(_St);
	return (_O); }
inline ostream& operator<<(ostream& _O, char __C)
	{typedef char _E;
	typedef char_traits _Tr;
	typedef ostream _Myos;
	ios_base::iostate _St = ios_base::goodbit;
	const _Myos::sentry _Ok(_O);
	if (_Ok)
		{size_t _M = _O.width() <= 1 ? 0 : _O.width() - 1;
		try {
		if ((_O.flags() & ios_base::adjustfield)
			!= ios_base::left)
			for (; _St == ios_base::goodbit && 0 < _M; --_M)
				if (_Tr::eq_int_type(_Tr::eof(),
					_O.rdbuf()->sputc(_O.fill())))
					_St |= ios_base::badbit;
		if (_St == ios_base::goodbit
			&& _Tr::eq_int_type(_Tr::eof(),
				_O.rdbuf()->sputc(__C)))
			_St |= ios_base::badbit;
		for (; _St == ios_base::goodbit && 0 < _M; --_M)
			if (_Tr::eq_int_type(_Tr::eof(),
				_O.rdbuf()->sputc(_O.fill())))
				_St |= ios_base::badbit;
		} catch (...) { (_O). setstate(ios_base::badbit, true); } }
	_O.width(0);
	_O.setstate(_St);
	return (_O); }
inline ostream& operator<<(ostream& _O,
	const signed char *__X)
	{return (_O << (const char *)__X); }
inline ostream& operator<<(ostream& _O,
	const signed char __C)
	{return (_O << (char)__C); }
inline ostream& operator<<(ostream& _O,
	const unsigned char *__X)
	{return (_O << (const char *)__X); }
inline ostream& operator<<(ostream& _O,
	const unsigned char __C)
	{return (_O << (char)__C); }
		
inline ostream& endl(ostream& _O)
	{_O.put('\n');
	_O.flush();
	return (_O); }
inline ostream& ends(ostream& _O)
	{_O.put(char('\0'));
	return (_O); }
inline ostream& flush(ostream& _O)
	{_O.flush();
	return (_O); }


#pragma arguments_in_registers(pop)






 
#line 30 "c:\\rm3dev\\incplus\\istream"

		



#pragma       align   (istream=4)             

class istream: public ios {
public:
	typedef char _E;
	typedef char_traits _Tr;
	typedef istream _Myt;
	typedef ios _Myios;
	typedef streambuf _Mysb;
	typedef _Istrit _Iter;
	typedef ctype _Ctype;
	typedef num_get _Nget;
	explicit istream(_Mysb *__S, bool _Isstd = false)
		: _Chcount(0) {init(__S, _Isstd); }
	istream(_Uninitialized)
		{_Addstd(); }
	virtual ~istream()
		{}
	typedef _Tr::int_type int_type;
	typedef _Tr::pos_type pos_type;
	typedef _Tr::off_type off_type;
	class sentry {
	public:
		explicit sentry(_Myt& _Is, bool _Noskip = false)
                         
			: _Lk(2,&_Is._ios_sem)  
			

 
			{_Ok = _Is.ipfx(_Noskip);}
		operator bool() const
			{return (_Ok); }
	private:
		sentry(const sentry&);	
		sentry& operator=(const sentry&);	
		bool _Ok;
		_Lockit _Lk;
		};
	bool ipfx(bool _Noskip = false)
		{if (ios_base::good())
			{if (_Myios::tie() != 0)
				_Myios::tie()->flush();
			if (!_Noskip && ios_base::flags() & ios_base::skipws)
				{const _Ctype& _Fac =
					_Ctype();
				try {
				int_type __C = _Myios::rdbuf()->sgetc();
				for (; ; __C = _Myios::rdbuf()->snextc())
					if (_Tr::eq_int_type(_Tr::eof(), __C))
						{_Myios::setstate(ios_base::eofbit);
						break; }
					else if (!_Fac.is(_Ctype::space,
						_Tr::to_char_type(__C)))
						break;
				} catch (...) { _Myios::setstate(ios_base::badbit, true); } }
			if (ios_base::good())
				return (true); }
		_Myios::setstate(ios_base::failbit);
		return (false); }
	void isfx()
		{}
	_Myt& operator>>(_Myt& (*_F)(_Myt&))
		{return ((*_F)(*this)); }
	_Myt& operator>>(_Myios& (*_F)(_Myios&))
		{(*_F)(*(_Myios *)this);
		return (*this); }
	_Myt& operator>>(ios_base& (*_F)(ios_base&))
		{(*_F)(*(ios_base *)this);
		return (*this); }
	_Myt& operator>>(_Bool& __X)
		{ios_base::iostate _St = ios_base::goodbit;
		const sentry _Ok(*this);
		if (_Ok)
			{const _Nget& _Fac = _Nget();
			try {
			_Fac.get(_Iter(_Myios::rdbuf()), _Iter(0),
				*this, _St, __X);
			} catch (...) { _Myios::setstate(ios_base::badbit, true); } }
		_Myios::setstate(_St);
		return (*this); }
	_Myt& operator>>(short& __X)
		{ios_base::iostate _St = ios_base::goodbit;
		const sentry _Ok(*this);
		if (_Ok)
			{long _Y;
			const _Nget& _Fac = _Nget();
			try {
			_Fac.get(_Iter(_Myios::rdbuf()), _Iter(0),
				*this, _St, _Y);
			} catch (...) { _Myios::setstate(ios_base::badbit, true); }
			if (_St & ios_base::failbit
				|| _Y < (-32768) || 32767 < _Y)
				_St |= ios_base::failbit;
			else
				__X = _Y; }
		_Myios::setstate(_St);
		return (*this); }
	_Myt& operator>>(unsigned short& __X)
		{ios_base::iostate _St = ios_base::goodbit;
		const sentry _Ok(*this);
		if (_Ok)
			{const _Nget& _Fac = _Nget();
			try {
			_Fac.get(_Iter(_Myios::rdbuf()), _Iter(0),
				*this, _St, __X);
			} catch (...) { _Myios::setstate(ios_base::badbit, true); } }
		_Myios::setstate(_St);
		return (*this); }
	_Myt& operator>>(int& __X)
		{ios_base::iostate _St = ios_base::goodbit;
		const sentry _Ok(*this);
		if (_Ok)
			{long _Y;
			const _Nget& _Fac = _Nget();
			try {
			_Fac.get(_Iter(_Myios::rdbuf()), _Iter(0),
				*this, _St, _Y);
			} catch (...) { _Myios::setstate(ios_base::badbit, true); }
			if (_St & ios_base::failbit
				|| _Y < (-2147483647l-1) || 2147483647 < _Y)
				_St |= ios_base::failbit;
			else
				__X = _Y; }
		_Myios::setstate(_St);
		return (*this); }
	_Myt& operator>>(unsigned int& __X)
		{ios_base::iostate _St = ios_base::goodbit;
		const sentry _Ok(*this);
		if (_Ok)
			{const _Nget& _Fac = _Nget();
			try {
			_Fac.get(_Iter(_Myios::rdbuf()), _Iter(0),
				*this, _St, __X);
			} catch (...) { _Myios::setstate(ios_base::badbit, true); } }
		_Myios::setstate(_St);
		return (*this); }
	_Myt& operator>>(long& __X)
		{ios_base::iostate _St = ios_base::goodbit;
		const sentry _Ok(*this);
		if (_Ok)
			{const _Nget& _Fac = _Nget();
			try {
			_Fac.get(_Iter(_Myios::rdbuf()), _Iter(0),
				*this, _St, __X);
			} catch (...) { _Myios::setstate(ios_base::badbit, true); } }
		_Myios::setstate(_St);
		return (*this); }
	_Myt& operator>>(unsigned long& __X)
		{ios_base::iostate _St = ios_base::goodbit;
		const sentry _Ok(*this);
		if (_Ok)
			{const _Nget& _Fac = _Nget();
			try {
			_Fac.get(_Iter(_Myios::rdbuf()), _Iter(0),
				*this, _St, __X);
			} catch (...) { _Myios::setstate(ios_base::badbit, true); } }
		_Myios::setstate(_St);
		return (*this); }
	_Myt& operator>>(float& __X)
		{ios_base::iostate _St = ios_base::goodbit;
		const sentry _Ok(*this);
		if (_Ok)
			{const _Nget& _Fac = _Nget();
			try {
			_Fac.get(_Iter(_Myios::rdbuf()), _Iter(0),
				*this, _St, __X);
			} catch (...) { _Myios::setstate(ios_base::badbit, true); } }
		_Myios::setstate(_St);
		return (*this); }
	_Myt& operator>>(double& __X)
		{ios_base::iostate _St = ios_base::goodbit;
		const sentry _Ok(*this);
		if (_Ok)
			{const _Nget& _Fac = _Nget();
			try {
			_Fac.get(_Iter(_Myios::rdbuf()), _Iter(0),
				*this, _St, __X);
			} catch (...) { _Myios::setstate(ios_base::badbit, true); } }
		_Myios::setstate(_St);
		return (*this); }
	_Myt& operator>>(long double& __X)
		{ios_base::iostate _St = ios_base::goodbit;
		const sentry _Ok(*this);
		if (_Ok)
			{const _Nget& _Fac = _Nget();
			try {
			_Fac.get(_Iter(_Myios::rdbuf()), _Iter(0),
				*this, _St, __X);
			} catch (...) { _Myios::setstate(ios_base::badbit, true); } }
		_Myios::setstate(_St);
		return (*this); }
	_Myt& operator>>(void *& __X)
		{ios_base::iostate _St = ios_base::goodbit;
		const sentry _Ok(*this);
		if (_Ok)
			{const _Nget& _Fac = _Nget();
			try {
			_Fac.get(_Iter(_Myios::rdbuf()), _Iter(0),
				*this, _St, __X);
			} catch (...) { _Myios::setstate(ios_base::badbit, true); } }
		_Myios::setstate(_St);
		return (*this); }
	_Myt& operator>>(_Mysb *_Pb)
		{ios_base::iostate _St = ios_base::goodbit;
		bool _Copied = false;
		const sentry _Ok(*this);
		if (_Ok && _Pb != 0)
			{try {
			int_type __C = _Myios::rdbuf()->sgetc();
			for (; ; __C = _Myios::rdbuf()->snextc())
				if (_Tr::eq_int_type(_Tr::eof(), __C))
					{_St |= ios_base::eofbit;
					break; }
				else
					{try {
						if (_Tr::eq_int_type(_Tr::eof(),
							_Pb->sputc(_Tr::to_char_type(__C))))
							break;
					} catch (...) {
						break;
					}
					_Copied = true; }
			} catch (...) { _Myios::setstate(ios_base::badbit, true); } }
		_Myios::setstate(!_Copied
			? _St | ios_base::failbit : _St);
		return (*this); }
	int_type get()
		{int_type __C;
		ios_base::iostate _St = ios_base::goodbit;
		_Chcount = 0;
		const sentry _Ok(*this, true);
		if (!_Ok)
			__C = _Tr::eof();
		else
			{try {
			__C = _Myios::rdbuf()->sbumpc();
			if (_Tr::eq_int_type(_Tr::eof(), __C))
				_St |= ios_base::eofbit | ios_base::failbit;
			else
				++_Chcount;
			} catch (...) { _Myios::setstate(ios_base::badbit, true); } }
		_Myios::setstate(_St);
		return (__C); }
	_Myt& get(_E *__S, streamsize __N)
		{return (get(__S, __N, _Myios::widen('\n'))); }
	_Myt& get(_E *__S, streamsize __N, _E _D)
		{ios_base::iostate _St = ios_base::goodbit;
		_Chcount = 0;
		const sentry _Ok(*this, true);
		if (_Ok && 0 < __N)
			{try {
			int_type __C = _Myios::rdbuf()->sgetc();
			for (; 0 < --__N; __C = _Myios::rdbuf()->snextc())
				if (_Tr::eq_int_type(_Tr::eof(), __C))
					{_St |= ios_base::eofbit;
					break; }
				else if (_Tr::to_char_type(__C) == _D)
					break;
				else
					*__S++ = _Tr::to_char_type(__C), ++_Chcount;
			} catch (...) { _Myios::setstate(ios_base::badbit, true); } }
		_Myios::setstate(_Chcount == 0
			? _St | ios_base::failbit : _St);
		*__S = _E();
		return (*this); }
	_Myt& get(_E& __X)
		{int_type __C = get();
		if (!_Tr::eq_int_type(_Tr::eof(), __C))
			__X = _Tr::to_char_type(__C);
		return (*this); }
	_Myt& get(_Mysb& _Sb)
		{return (get(_Sb, _Myios::widen('\n'))); }
	_Myt& get(_Mysb& _Sb, _E _D)
		{ios_base::iostate _St = ios_base::goodbit;
		_Chcount = 0;
		const sentry _Ok(*this, true);
		if (_Ok)
			{try {
			int_type __C = _Myios::rdbuf()->sgetc();
			for (; ; __C = _Myios::rdbuf()->snextc())
				if (_Tr::eq_int_type(_Tr::eof(), __C))
					{_St |= ios_base::eofbit;
					break; }
				else
					{try {
						_E _Ch = _Tr::to_char_type(__C);
						if (_Ch == _D
							|| _Tr::eq_int_type(_Tr::eof(),
								_Sb.sputc(_Ch)))
							break;
					} catch (...) {
						break;
					}
					++_Chcount; }
			} catch (...) { _Myios::setstate(ios_base::badbit, true); } }
		if (_Chcount == 0)
			_St |= ios_base::failbit;
		_Myios::setstate(_St);
		return (*this); }
	_Myt& getline(_E *__S, streamsize __N)
		{return (getline(__S, __N, _Myios::widen('\n'))); }
	_Myt& getline(_E *__S, streamsize __N, _E _D)
		{ios_base::iostate _St = ios_base::goodbit;
		_Chcount = 0;
		const sentry _Ok(*this, true);
		if (_Ok && 0 < __N)
			{int_type _Di = _Tr::to_int_type(_D);
			try {
			int_type __C = _Myios::rdbuf()->sgetc();
			for (; ; __C = _Myios::rdbuf()->snextc())
				if (_Tr::eq_int_type(_Tr::eof(), __C))
					{_St |= ios_base::eofbit;
					break; }
				else if (__C == _Di)
					{++_Chcount;
					_Myios::rdbuf()->sbumpc();
					break; }
				else if (--__N <= 0)
					{_St |= ios_base::failbit;
					break; }
				else
					{++_Chcount;
					*__S++ = _Tr::to_char_type(__C); }
			} catch (...) { _Myios::setstate(ios_base::badbit, true); } }
		*__S = _E();
		_Myios::setstate(_Chcount == 0
			? _St | ios_base::failbit : _St);
		return (*this); }
	_Myt& ignore(streamsize __N = 1, int_type _Di = _Tr::eof())
		{ios_base::iostate _St = ios_base::goodbit;
		_Chcount = 0;
		const sentry _Ok(*this, true);
		if (_Ok && 0 < __N)
			{try {
			for (; ; )
				{int_type __C;
				if (__N != 2147483647 && --__N < 0)
					break;
				else if (_Tr::eq_int_type(_Tr::eof(),
					__C = _Myios::rdbuf()->sbumpc()))
					{_St |= ios_base::eofbit;
					break; }
				else
					{++_Chcount;
					if (__C == _Di)
						break; }}
			} catch (...) { _Myios::setstate(ios_base::badbit, true); } }
		_Myios::setstate(_St);
		return (*this); }
	_Myt& read(_E *__S, streamsize __N)
		{ios_base::iostate _St = ios_base::goodbit;
		_Chcount = 0;
		const sentry _Ok(*this, true);
		if (_Ok)
			{try {
			const streamsize _M = _Myios::rdbuf()->sgetn(__S, __N);
			_Chcount += _M;
			if (_M != __N)
				_St |= ios_base::eofbit | ios_base::failbit;
			} catch (...) { _Myios::setstate(ios_base::badbit, true); } }
		_Myios::setstate(_St);
		return (*this); }
	streamsize readsome(_E *__S, streamsize __N)
		{ios_base::iostate _St = ios_base::goodbit;
		_Chcount = 0;
		int _M;
		if (_Myios::rdbuf() == 0)
			_St |= ios_base::failbit;
		else if ((_M = _Myios::rdbuf()->in_avail()) < 0)
			_St |= ios_base::eofbit;
		else if (0 < _M)
			read(__S, _M < __N ? _M : __N);
		_Myios::setstate(_St);
		return (gcount()); }
	int_type peek()
		{ios_base::iostate _St = ios_base::goodbit;
		_Chcount = 0;
		int_type __C;
		const sentry _Ok(*this, true);
		if (!_Ok)
			__C = _Tr::eof();
		else
			{try {
			if (_Tr::eq_int_type(_Tr::eof(),
				__C = _Myios::rdbuf()->sgetc()))
				_St |= ios_base::eofbit;
			} catch (...) { _Myios::setstate(ios_base::badbit, true); } }
		_Myios::setstate(_St);
		return (__C); }
	_Myt& putback(_E __X)
		{ios_base::iostate _St = ios_base::goodbit;
		_Chcount = 0;
		const sentry _Ok(*this, true);
		if (_Ok)
			{try {
			if (_Tr::eq_int_type(_Tr::eof(),
				_Myios::rdbuf()->sputbackc(__X)))
				_St |= ios_base::badbit;
			} catch (...) { _Myios::setstate(ios_base::badbit, true); } }
		_Myios::setstate(_St);
		return (*this); }
	_Myt& unget()
		{ios_base::iostate _St = ios_base::goodbit;
		_Chcount = 0;
		const sentry _Ok(*this, true);
		if (_Ok)
			{try {
			if (_Tr::eq_int_type(_Tr::eof(),
				_Myios::rdbuf()->sungetc()))
				_St |= ios_base::badbit;
			} catch (...) { _Myios::setstate(ios_base::badbit, true); } }
		_Myios::setstate(_St);
		return (*this); }
	streamsize gcount() const
		{return (_Chcount); }
	int sync()
		{ios_base::iostate _St = ios_base::goodbit;
		int _Ans;
		if (_Myios::rdbuf() == 0)
			_Ans = -1;
		else if (_Myios::rdbuf()->pubsync() == -1)
			_St |= ios_base::badbit, _Ans = -1;
		else
			_Ans = 0;
		_Myios::setstate(_St);
		return (_Ans); }
	_Myt& seekg(pos_type __P)
		{if (!ios_base::fail())
			_Myios::rdbuf()->pubseekpos(__P, ios_base::in);
		return (*this); }
	_Myt& seekg(off_type _O, ios_base::seekdir _W)
		{if (!ios_base::fail())
			_Myios::rdbuf()->pubseekoff(_O, _W, ios_base::in);
		return (*this); }
	pos_type tellg()
		{if (!ios_base::fail())
			return (_Myios::rdbuf()->pubseekoff(0,
				ios_base::cur, ios_base::in));
		else
			return (pos_type(_BADOFF)); }
private:
	streamsize _Chcount;

protected:
        



 
	void	tie_sem(void) {
		__cadul_share_critical_section_lock((void *)&_ios_sem,
					   (void *)&(tie()->_ios_sem));
	}
	};
		
inline istream& operator>>(istream& _I, char *__X)
	{typedef char _E;
	typedef char_traits _Tr;
	typedef istream _Myis;
	typedef ctype _Ctype;
	ios_base::iostate _St = ios_base::goodbit;
	_E *__S = __X;
	const _Myis::sentry _Ok(_I);
	if (_Ok)
		{const _Ctype& _Fac = _Ctype();
		try {
		int __N = 0 < _I.width() ? _I.width() : 2147483647;
		_Myis::int_type __C = _I.rdbuf()->sgetc();
		for (; 0 < --__N; __C = _I.rdbuf()->snextc())
			if (_Tr::eq_int_type(_Tr::eof(), __C))
				{_St |= ios_base::eofbit;
				break; }
			else if (_Fac.is(_Ctype::space,
				_Tr::to_char_type(__C)))
				break;
			else
				*__S++ = _Tr::to_char_type(__C);
		} catch (...) { (_I). setstate(ios_base::badbit, true); } }
	*__S = _E();
	_I.width(0);
	_I.setstate(__S == __X ? _St | ios_base::failbit : _St);
	return (_I); }
inline istream& operator>>(istream& _I, char& __X)
	{typedef char _E;
	typedef char_traits _Tr;
	typedef istream _Myis;
	_Myis::int_type __C;
	ios_base::iostate _St = ios_base::goodbit;
	const _Myis::sentry _Ok(_I);
	if (_Ok)
		{try {
		__C = _I.rdbuf()->sbumpc();
		if (_Tr::eq_int_type(_Tr::eof(), __C))
			_St |= ios_base::eofbit | ios_base::failbit;
		else
			__X = _Tr::to_char_type(__C);
		} catch (...) { (_I). setstate(ios_base::badbit, true); } }
	_I.setstate(_St);
	return (_I); }
inline istream& operator>>(istream& _I, signed char *__X)
	{return (_I >> (char *)__X); }
inline istream& operator>>(istream& _I, signed char& __C)
	{return (_I >> (char&)__C); }
inline istream& operator>>(istream& _I, unsigned char *__X)
	{return (_I >> (char *)__X); }
inline istream& operator>>(istream& _I, unsigned char& __C)
	{return (_I >> (char&)__C); }
		
inline istream& ws(istream& _I)
	{typedef char _E;
	typedef char_traits _Tr;
	typedef istream _Myis;
	typedef ctype _Ctype;
	ios_base::iostate _St = ios_base::goodbit;
	const _Myis::sentry _Ok(_I, true);
	if (_Ok)
		{const _Ctype& _Fac = _Ctype();
		try {
		for (_Tr::int_type __C = _I.rdbuf()->sgetc(); ;
			__C = _I.rdbuf()->snextc())
			if (_Tr::eq_int_type(_Tr::eof(), __C))
				{_St |= ios_base::eofbit;
				break; }
			else if (!_Fac.is(_Ctype::space,
				_Tr::to_char_type(__C)))
				break;
		} catch (...) { (_I). setstate(ios_base::badbit, true); } }
	_I.setstate(_St);
	return (_I); }


#pragma arguments_in_registers(pop)






 
#line 30 "c:\\rm3dev\\incplus\\iostream.h"

		
static ios_base::Init _Ios_init0;
extern istream cin;
extern ostream cout;






#pragma arguments_in_registers(pop)






 
#line 32 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\rmos_inc.h"
#line 1 "c:\\rm3dev\\incplus\\iomanip"
 



















  





#pragma noarguments_in_registers(push)



		
#line 46 "c:\\rm3dev\\incplus\\iomanip"
		



#pragma       align   (_Smanip_char=4)                

struct _Smanip_char { _Smanip_char(void (*_F)(ios&, char), char _A) : _Pf(_F), _Manarg(_A) {} void (*_Pf)(ios&, char); char _Manarg; }; inline istream& operator>>(istream& _I, const _Smanip_char& _M) {(*_M . _Pf)(_I, _M . _Manarg); return (_I); } inline ostream& operator<<(ostream& _O, const _Smanip_char& _M) {(*_M . _Pf)(_O, _M . _Manarg); return (_O); }



#pragma       align   (_Smanip_fmt=4)                 

struct _Smanip_fmt { _Smanip_fmt(void (*_F)(ios_base&, ios_base::fmtflags), ios_base::fmtflags _A) : _Pf(_F), _Manarg(_A) {} void (*_Pf)(ios_base&, ios_base::fmtflags); ios_base::fmtflags _Manarg; }; inline istream& operator>>(istream& _I, const _Smanip_fmt& _M) {(*_M . _Pf)(_I, _M . _Manarg); return (_I); } inline ostream& operator<<(ostream& _O, const _Smanip_fmt& _M) {(*_M . _Pf)(_O, _M . _Manarg); return (_O); }



#pragma       align   (_Smanip_int=4)                 

struct _Smanip_int { _Smanip_int(void (*_F)(ios_base&, int), int _A) : _Pf(_F), _Manarg(_A) {} void (*_Pf)(ios_base&, int); int _Manarg; }; inline istream& operator>>(istream& _I, const _Smanip_int& _M) {(*_M . _Pf)(_I, _M . _Manarg); return (_I); } inline ostream& operator<<(ostream& _O, const _Smanip_int& _M) {(*_M . _Pf)(_O, _M . _Manarg); return (_O); }



#pragma       align   (_Smanip_str=4)                 

struct _Smanip_str { _Smanip_str(void (*_F)(ios_base&, streamsize), streamsize _A) : _Pf(_F), _Manarg(_A) {} void (*_Pf)(ios_base&, streamsize); streamsize _Manarg; }; inline istream& operator>>(istream& _I, const _Smanip_str& _M) {(*_M . _Pf)(_I, _M . _Manarg); return (_I); } inline ostream& operator<<(ostream& _O, const _Smanip_str& _M) {(*_M . _Pf)(_O, _M . _Manarg); return (_O); }
_Smanip_char setfill(char);
_Smanip_fmt resetiosflags(ios_base::fmtflags);
_Smanip_fmt setiosflags(ios_base::fmtflags);
_Smanip_int setbase(int);
_Smanip_str setprecision(streamsize);
_Smanip_str setw(streamsize);


#pragma arguments_in_registers(pop)






 
#line 33 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\rmos_inc.h"
#line 1 "c:\\rm3dev\\incplus\\fstream.h"
 



















  





#pragma noarguments_in_registers(push)

#line 1 "c:\\rm3dev\\incplus\\fstream"
 



















  





#pragma noarguments_in_registers(push)







 




 

FILE *_Fiopen(const char *, ios_base::openmode);
		



#pragma       align   (filebuf=4)             

class filebuf : public streambuf {
public:
	typedef char _E;
	typedef char_traits _Tr;
	typedef filebuf _Myt;
	typedef streambuf _Mysb;
	virtual ~filebuf()
		{if (_Closef)
			close(); }
	typedef _Tr::int_type int_type;
	typedef _Tr::pos_type pos_type;
	typedef _Tr::off_type off_type;
	filebuf(FILE *_Fi = 0)
		: _Loc(), _Mysb() {_Init(_Fi, _Newfl); }
	filebuf(_Uninitialized)
		: _Loc(_Noinit), _Mysb(_Noinit) {}
	enum _Initfl {_Newfl, _Openfl, _Closefl};
	bool is_open() const
		{return (_File != 0); }
	_Myt *open(const char *__S, ios_base::openmode _M)
		{FILE *_Fi;
		if (_File != 0 || (_Fi = _Fiopen(__S, _M)) == 0)
			return (0);
		_Init(_Fi, _Openfl);
		_Initcvt();
		return (this); }
	_Myt *open(const char *__N, ios::open_mode _M)
		{return (open(__N, (ios::openmode)_M)); }
	_Myt *close()
						 
		{if (_File != 0 && _Endwrite() && fclose(_File) == 0)
			{_Init(0, _Closefl);
			return (this); }
		else
			return (0); }
protected:
	virtual int_type overflow(int_type __C = _Tr::eof())
		{if (_Tr::eq_int_type(_Tr::eof(), __C))
			return (_Tr::not_eof(__C));
		else if (_Mysb::pptr() != 0
			&& _Mysb::pptr() < _Mysb::epptr())
			{*_Mysb::_Pninc() = _Tr::to_char_type(__C);
			return (__C); }
		else if (_File == 0)
			return (_Tr::eof());
		else
						 
			return (fputc(_Tr::to_char_type(__C), _File) != (-1)
				? __C : _Tr::eof()); }
	virtual int_type pbackfail(int_type __C = _Tr::eof())
		{if (_Mysb::gptr() != 0
			&& _Mysb::eback() < _Mysb::gptr()
			&& (_Tr::eq_int_type(_Tr::eof(), __C)
			 || _Tr::eq_int_type(_Tr::to_int_type(gptr()[-1]),
				__C)))
			{_Mysb::_Gndec();
			return (_Tr::not_eof(__C)); }
		else if (_File == 0 || _Tr::eq_int_type(_Tr::eof(), __C))
			return (_Tr::eof());
		else
							 
			return (ungetc(_Tr::to_char_type(__C), _File) != (-1)
				? __C : _Tr::eof()); }
	virtual int_type underflow()
		{if (_Mysb::gptr() != 0
			&& _Mysb::gptr() < _Mysb::egptr())
			return (_Tr::to_int_type(*_Mysb::gptr()));
		else
			return (pbackfail(uflow())); }
	virtual int_type uflow()
		{if (_Mysb::gptr() != 0
			&& _Mysb::gptr() < _Mysb::egptr())
			return (_Tr::to_int_type(*_Mysb::_Gninc()));
		else if (_File == 0)
			return (_Tr::eof());
		else
			{int_type _Ch;
					 
			return ((_Ch = fgetc(_File)) != (-1) ? _Ch
				: _Tr::eof()); }}
	virtual pos_type seekoff(off_type _O, ios_base::seekdir _Way,
		ios_base::openmode =
			(ios_base::openmode)(ios_base::in | ios_base::out))
		{fpos_t _Fp;
		if (_File == 0 || !_Endwrite()
			 
			|| fseek(_File, _O, _Way) != 0
			|| fgetpos(_File, &_Fp) != 0)
			return (pos_type(_BADOFF));
		return (pos_type(_State, _Fp)); }
	virtual pos_type seekpos(pos_type __P,
		ios_base::openmode =
			(ios_base::openmode)(ios_base::in | ios_base::out))
		{fpos_t _Fp = __P.seekpos();
		off_type _Off = (off_type)__P - ((long)(_Fp));
		if (_File == 0 || !_Endwrite()
			 
			|| fsetpos(_File, &_Fp) != 0
			|| _Off != 0 && fseek(_File, _Off, 1) != 0
			|| fgetpos(_File, &_Fp) != 0)
			return (pos_type(_BADOFF));
		return (pos_type(_State, _Fp)); }
	virtual _Mysb *setbuf(_E *__S, streamsize __N)
					 
		{return (_File == 0 || setvbuf(_File, (char *)__S,
			0x0000, __N * sizeof (_E)) != 0 ? 0 : this); }
	virtual int sync()
		{return (_File == 0
			|| _Tr::eq_int_type(_Tr::eof(), overflow())
				 
			|| 0 <= fflush(_File) ? 0 : -1); }
	void _Init(FILE *_Fp, _Initfl _Which)
		{static _Tr::state_type _Stinit;
		_Closef = _Which == _Openfl;
		_Mysb::_Init();
		_File = _Fp; 	 
		_State = _Stinit; }
	void _Initcvt()
		{}
	bool _Endwrite()
		{return (true); }
private:
	



 
#line 189 "c:\\rm3dev\\incplus\\fstream"
	




 
#line 207 "c:\\rm3dev\\incplus\\fstream"
	_Tr::state_type _State;
	bool _Closef;
	locale _Loc;
	FILE *_File;
	};

		



#pragma       align   (ifstream=4)            

class ifstream : public istream {
public:
	typedef char _E;
	typedef char_traits _Tr;
	typedef ifstream _Myt;
	typedef filebuf _Myfb;
	typedef ios _Myios;
	ifstream()
		: istream(&_Fb) {}
	explicit ifstream(const char *__S,
		ios_base::openmode _M = ios_base::in)
		: istream(&_Fb)
		{if (_Fb.open(__S, _M | ios_base::in) == 0)
			setstate(failbit); }
	virtual ~ifstream()
		{}
	_Myfb *rdbuf() const
		{return ((_Myfb *)&_Fb); }
	bool is_open() const
		{return (_Fb.is_open()); }
	void open(const char *__S,
		ios_base::openmode _M = ios_base::in)
		{if (_Fb.open(__S, _M | ios_base::in) == 0)
			_Myios::setstate(ios_base::failbit); }
	void open(const char *__S, ios_base::open_mode _M)
		{open(__S, (ios_base::openmode)_M); }
	void close()
		{if (_Fb.close() == 0)
			_Myios::setstate(ios_base::failbit); }
private:
	_Myfb _Fb;
	};

		



#pragma       align   (ofstream=4)            

class ofstream : public ostream {
public:
	typedef char _E;
	typedef char_traits _Tr;
	typedef ofstream _Myt;
	typedef filebuf _Myfb;
	typedef ios _Myios;
	ofstream()
		: ostream(&_Fb) {}
	explicit ofstream(const char *__S,
		ios_base::openmode _M = ios_base::out)
		: ostream(&_Fb)
		{if (_Fb.open(__S, _M | ios_base::out) == 0)
			setstate(failbit); }
	virtual ~ofstream()
		{}
	_Myfb *rdbuf() const
		{return ((_Myfb *)&_Fb); }
	bool is_open() const
		{return (_Fb.is_open()); }
	void open(const char *__S,
		ios_base::openmode _M = ios_base::out)
		{if (_Fb.open(__S, _M | ios_base::out) == 0)
			_Myios::setstate(ios_base::failbit); }
	void open(const char *__S, ios_base::open_mode _M)
		{open(__S, (ios_base::openmode)_M); }
	void close()
		{if (_Fb.close() == 0)
			_Myios::setstate(ios_base::failbit); }
private:
	_Myfb _Fb;
	};


#pragma arguments_in_registers(pop)






 
#line 30 "c:\\rm3dev\\incplus\\fstream.h"






#pragma arguments_in_registers(pop)






 
#line 34 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\rmos_inc.h"
#line 1 "c:\\rm3dev\\incplus\\strstream.h"
 



















  



#pragma noarguments_in_registers(push)
#line 1 "c:\\rm3dev\\incplus\\strstream"
 



















  





#pragma noarguments_in_registers(push)



		



#pragma       align   (strstreambuf=4)                

class strstreambuf : public streambuf {
public:
	enum __Strstate {_Allocated = 1, _Constant = 2,
		_Dynamic = 4, _Frozen = 8};
	typedef int _Strstate;
	explicit strstreambuf(streamsize __N = 0)
		{_Init(__N); }
	strstreambuf(void *(*_A)(size_t),
		void (*_F)(void *))
		{_Init(), _Palloc = _A, _Pfree = _F; }
	strstreambuf(char *_G, streamsize __N, char *__P = 0)
		{_Init(__N, _G, __P); }
	strstreambuf(unsigned char *_G, streamsize __N,
		unsigned char *__P = 0)
		{_Init(__N, (char *)_G, (char *)__P); }
	strstreambuf(const char *_G, streamsize __N)
		{_Init(__N, (char *)_G, 0, _Constant); }
	strstreambuf(const unsigned char *_G, streamsize __N)
		{_Init(__N, (char *)_G, 0, _Constant); }
	virtual ~strstreambuf();
	void freeze(bool = true);
	char *str()
		{freeze();
		return (gptr()); }
	streamsize pcount() const
		{return (pptr() == 0 ? 0 : pptr() - pbase()); }
	strstreambuf(signed char *_G, streamsize __N,
		signed char *__P = 0)
		{_Init(__N, (char *)_G, (char *)__P); }
	strstreambuf(const signed char *_G, streamsize __N)
		{_Init(__N, (char *)_G, 0, _Constant); }
protected:
	virtual int overflow(int = (-1));
	virtual int pbackfail(int = (-1));
	virtual int underflow();
	virtual streampos seekoff(streamoff, ios::seekdir,
		ios::openmode = ios::in | ios::out);
	virtual streampos seekpos(streampos,
		ios::openmode = ios::in | ios::out);
	void _Init(int = 0, char * = 0, char * = 0,
		_Strstate = (_Strstate)0);
	void _Tidy();
private:
	enum {_ALSIZE = 512, _MINSIZE = 32};
	char *_Pendsave, *_Seekhigh;
	int _Alsize;
	_Strstate _Strmode;
	void *(*_Palloc)(size_t);
	void (*_Pfree)(void *);
	};

		



#pragma       align   (istrstream=4)          

class istrstream : public istream {
public:
	explicit istrstream(const char *__S)
		: istream(&_Sb), _Sb(__S, 0) {}
	istrstream(const char *__S, streamsize __N)
		: istream(&_Sb), _Sb(__S, __N) {}
	explicit istrstream(char *__S)
		: istream(&_Sb), _Sb((const char *)__S, 0) {}
	istrstream(char *__S, int __N)
		: istream(&_Sb), _Sb((const char *)__S, __N) {}
	virtual ~istrstream();
	strstreambuf *rdbuf() const
		{return ((strstreambuf *)&_Sb); }
	char *str()
		{return (_Sb.str()); }
private:
	strstreambuf _Sb;
	};
		



#pragma       align   (ostrstream=4)          

class ostrstream : public ostream {
public:
	ostrstream()
		: ostream(&_Sb), _Sb() {}
	ostrstream(char *, streamsize,
		ios::openmode = ios::out);
	virtual ~ostrstream();
	strstreambuf *rdbuf() const
		{return ((strstreambuf *)&_Sb); }
	void freeze(bool _F = true)
		{_Sb.freeze(_F); }
	char *str()
		{return (_Sb.str()); }
	streamsize pcount() const
		{return (_Sb.pcount()); }
private:
	strstreambuf _Sb;
	};


#pragma arguments_in_registers(pop)






 
#line 27 "c:\\rm3dev\\incplus\\strstream.h"
#pragma arguments_in_registers(pop)



#line 35 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\rmos_inc.h"
#line 1 "\\rm3dev\\inc\\io.h"






















 









            
            
#pragma fixedparams ("read", "duread", "write", "access")
#pragma fixedparams ("duwrite", "unlink", "lseek", "close")
#pragma fixedparams ("mount", "dismount", "remap")
#pragma fixedparams ("x_cr_getskhandle", "x_cr_allocskhandle")
#pragma varparams ("open")
#pragma varparams ("search", "checkpoint", "getvolumestatus")
#pragma varparams ("createvib", "changevib", "efsuse", "efsstop")
#pragma varparams ("chmod")
#pragma varparams ("inhibitabort")



#line 1 "c:\\rm3dev\\inc\\hsfs.h"























 








 static const char idstr_hsfssvc_h [] =
{
        "\0"    "(C) SIEMENS AG 1994"   "\0"     
        "\1"    "HSFS.H"                "\1"
        "\2"    "0012"                  "\2"
        "\3"    "W.K."                  "\3"
};




 #pragma align( _MS_BOOT_SEC = 1)
 #pragma align( _VOL_DATA = 1)
 #pragma align( _DEV_DATA_FIELD = 1)
 #pragma align( _DIR_ENTRY = 1)
 #pragma align( _MDR_RPB = 1)
 #pragma align( _OC_RPB = 1)
 #pragma align( _OCD_RPB = 1)
 #pragma align( _RW_RPB = 1)
 #pragma align( _SR_RPB = 1)
 #pragma align( _VS_RPB = 1)
 #pragma align( _CKP_RPB = 1)
 #pragma align( _CTV_RPB = 1)
 #pragma align( _CHV_RPB = 1)











 

typedef struct _MS_BOOT_SEC
{
    char            boot_jmp[3];
    char            disk_name[8];
    unsigned short  bytes_per_sec;
    char            sec_per_clust;
    unsigned short  res_sec;
    char            no_of_fats;
    unsigned short  root_entries;
    unsigned short  partition_sec1;
    char            id_byte;
    unsigned short  sec_per_fat;
    unsigned short  sec_per_track;
    unsigned short  sides;
    long            hidden_sec;
    long            partition_sec2;
    char            fill_block[476];
} MS_BOOT_SEC;



 

typedef struct _VOL_DATA
{
    char            vol_name[2];
    unsigned long   no_of_blocks;
    unsigned int    no_of_root_blocks;
    unsigned char   device_id;
    unsigned char   unit_id;
    unsigned int    flags;
    char            *fat_buf;



    unsigned long   start_block;
  
    void            *boot_sec;



} VOL_DATA;



 

typedef struct _DEV_DATA_FIELD
{
    unsigned char   device_id;
    unsigned char   unit_id;
    unsigned char   read_code;
    unsigned char   write_code;
    unsigned char   is_block_dev;
    unsigned short  block_size;
} DEV_DATA_FIELD;



 

typedef struct _DIR_ENTRY
{
    char            file_name[8];
    char            delim;
    char            file_ext[3];
    unsigned short  blocking;
    unsigned long   file_size;
    unsigned short  reserved1[3];
    char            attrib;
    unsigned char   reserved2;
    unsigned short  time;
    unsigned short  date;
    unsigned short  reserved3;
} DIR_ENTRY;



 

typedef struct _MDR_RPB
{
    char            vol_name[2];
    unsigned int    format;
} MDR_RPB;



 

typedef struct _OC_RPB
{
    char            *file_name;
    unsigned int    rec_size;
    unsigned long   rec_count;
    unsigned int    file_channel;
    char            file_attribs,
                    oc_options;
    unsigned int    dir_channel;
    unsigned short  wr_date;
    unsigned short  wr_time;
} OC_RPB;



 

typedef struct _OCD_RPB
{
    char            *file_name;
    DEV_DATA_FIELD  *device_file;

    unsigned short  fillup;



    unsigned int    file_channel;
    char            file_attribs,
                    oc_options;
    unsigned int    dir_channel;
    unsigned short  wr_date;
    unsigned short  wr_time;
} OCD_RPB;



 

typedef struct _RW_RPB
{
    unsigned int    file_channel;
    unsigned long   first_rec;
    unsigned int    nr_recs;
    char            *buffer_addr;
    unsigned int    recs_xferred;
    char            terminator,
                    rw_options;
} RW_RPB;



 

typedef struct _SR_RPB
{
    char            *file_name;
    unsigned int    dir_channel,
                    first_rec;
    DIR_ENTRY       *found_name;
    unsigned int    found_rec,
                    padding;
 } SR_RPB;



 

typedef struct _VS_RPB
{
    char            vol_name[2];
    VOL_DATA        *vol_vib;
    unsigned int    vol_flags;
    unsigned long   free_blocks;
    unsigned int    open_files,
                    write_errors;
} VS_RPB;



 

typedef struct _CKP_RPB
{
    unsigned int    file_channel;
} CKP_RPB;



 

typedef struct _CTV_RPB
{
    VOL_DATA        *new_vib;
    char            pool_id;
} CTV_RPB;



 

typedef struct _CHV_RPB
{
    char            vol_name[2];
    VOL_DATA        *vol_data;
} CHV_RPB;



 

#line 283 "c:\\rm3dev\\inc\\hsfs.h"



 

#line 298 "c:\\rm3dev\\inc\\hsfs.h"



 

#line 310 "c:\\rm3dev\\inc\\hsfs.h"



 

#line 326 "c:\\rm3dev\\inc\\hsfs.h"



 

#line 357 "c:\\rm3dev\\inc\\hsfs.h"









#line 52 "\\rm3dev\\inc\\io.h"
#line 1 "c:\\rm3dev\\inc\\efs.h"























 




#line 1 "c:\\rm3dev\\inc\\rmtypes.h"
























 




#line 1 "c:\\rm3dev\\inc\\misc86.h"

































 




#line 1 "c:\\rm3dev\\inc\\macro.h"


























 











	  



#line 51 "c:\\rm3dev\\inc\\macro.h"

#line 87 "c:\\rm3dev\\inc\\macro.h"











#line 41 "c:\\rm3dev\\inc\\misc86.h"




static const
char idstr_misc86_h [] =
{
        "\0"    "(C) SIEMENS AG 1994"   "\0"     
        "\1"    "MISC86.H"              "\1"
		  "\2"    "0007"                  "\2"
        "\3"    "J.R."                  "\3"
};




#line 64 "c:\\rm3dev\\inc\\misc86.h"

#line 1 "c:\\cadul\\include\\builtin.h"













































 
#line 53 "c:\\cadul\\include\\builtin.h"
extern	"C"	{







 

#pragma	_selector_(selector)












































 

#pragma _builtin_(buildptr)
void far * buildptr(selector sel, void near *offset);


#pragma	_builtin_(push)
volatile void push(int);

#pragma	_builtin_(pop)
volatile int pop(void);

#pragma	_builtin_(causeinterrupt)
void causeinterrupt(unsigned char inum);

#pragma	_builtin_(clearcarryflag)
void	volatile clearcarryflag(void);

#pragma	_builtin_(cleardirectionflag)
void	volatile cleardirectionflag(void);

#pragma	_builtin_(disable)
void	disable(void);

#pragma	_builtin_(enable)
void	enable(void);

#pragma	_builtin_(getflags)
volatile unsigned int getflags(void);

#pragma	_builtin_(get_reg_cs)
volatile unsigned short get_reg_cs(void);

#pragma	_builtin_(get_reg_ds)
volatile unsigned short get_reg_ds(void);

#pragma	_builtin_(get_reg_es)
volatile unsigned short get_reg_es(void);

#pragma	_builtin_(get_reg_ss)
volatile unsigned short get_reg_ss(void);

#pragma	_builtin_(halt)
void halt(void);

#pragma	_builtin_(inbyte)
volatile unsigned char inbyte(unsigned short port);

#pragma	_builtin_(inword)
volatile unsigned int inword(unsigned short port);

#pragma	_builtin_(lockset)
unsigned char lockset(unsigned char *lockptr, unsigned char newvalue);

#pragma	_builtin_(nop)
void volatile nop(void);

#pragma _builtin_(_inline)
void volatile _inline(unsigned char uc);

#line 183 "c:\\cadul\\include\\builtin.h"

#pragma	_builtin_(outbyte)
volatile void	outbyte(unsigned short port, unsigned char byte);

#pragma	_builtin_(outword)
volatile void	outword(unsigned short port, unsigned int word);

#pragma _builtin_(reverse_byte_order)
unsigned long reverse_byte_order(unsigned long);

#pragma _builtin_(setcarryflag)
void    volatile setcarryflag(void);
 
#pragma _builtin_(setdirectionflag)
void    volatile setdirectionflag(void);
 
#pragma	_builtin_(set_reg_cs)
unsigned short volatile set_reg_cs(unsigned short value);

#pragma	_builtin_(set_reg_ds)
unsigned short volatile set_reg_ds(unsigned short value);

#pragma	_builtin_(set_reg_es)
unsigned short volatile set_reg_es(unsigned short value);

#pragma	_builtin_(set_reg_ss)
unsigned short volatile set_reg_ss(unsigned short value);

#pragma _builtin_(setflags)
void	setflags(unsigned int flags);

#pragma  _builtin_(swap_word)
unsigned short swap_word(unsigned short);

#pragma _builtin_(swap_long)
unsigned long swap_long(unsigned long);




















 

#pragma	_builtin_(fclex)
void	fclex(void);

#pragma	_builtin_(finit)
void	finit(void);

#pragma	_builtin_(fldcw)
void	fldcw(unsigned short cw);

#pragma	_builtin_(fstcw)
void	fstcw(unsigned short *cwp);

#pragma	_builtin_(fstenv)
void	fstenv(void *p);

#pragma	_builtin_(fstsw)
unsigned short	fstsw(void);

#pragma	_builtin_(getrealerror)
unsigned short getrealerror(void);

#pragma	_builtin_(initrealmathunit)
void	initrealmathunit(void);

#pragma	_builtin_(restorerealstatus)
void	restorerealstatus(void *saved_status);

#pragma	_builtin_(saverealstatus)
void	saverealstatus(void *save_area);

#pragma	_builtin_(setrealmode)
void	setrealmode(unsigned short mode);











 
#line 297 "c:\\cadul\\include\\builtin.h"

















 

#pragma	_builtin_(blockinbyte)
volatile void	blockinbyte(unsigned short port, unsigned char *destination,
		unsigned int count);

#pragma	_builtin_(blockinword)
volatile void	blockinword(unsigned short port, unsigned int *destination,
		unsigned int count);

#pragma _builtin_(blockoutbyte)
volatile void	blockoutbyte(unsigned short port, unsigned char const *destination,
		unsigned int count);

#pragma	_builtin_(blockoutword)
volatile void	blockoutword(unsigned short port, unsigned int const *destination,
		unsigned int count);

#pragma	_builtin_(popall)
void	popall(void);

#pragma	_builtin_(pushall)
void	pushall(void);

#pragma	_builtin_(pushf)
void	pushf(void);

#pragma	_builtin_(popf)
void	popf(void);




























 

#pragma _builtin_(adjustrpl)
volatile selector adjustrpl(selector sel);

#pragma _builtin_(cleartaskswitchedflag)
void cleartaskswitchedflag(void);

#pragma _builtin_(getaccessrights)
volatile unsigned int getaccessrights(selector sel);

#pragma _builtin_(getlocaltable)
volatile selector getlocaltable(void);

#pragma _builtin_(setmachinestatus)
#pragma _builtin_(getmachinestatus)
volatile void	setmachinestatus(unsigned short value);
volatile unsigned short getmachinestatus(void);

#pragma _builtin_(getsegmentlimit)
volatile unsigned int getsegmentlimit(selector sel);

#pragma _builtin_(settaskregister)
#pragma _builtin_(gettaskregister)
volatile void	settaskregister(selector value);
volatile selector gettaskregister(void);

#pragma _builtin_(saveglobaltable)
#pragma _builtin_(restoreglobaltable)
volatile void	saveglobaltable(void *ptr);
volatile void restoreglobaltable(void * ptr);

#pragma _builtin_(saveinterrupttable)
#pragma _builtin_(restoreinterrupttable)
volatile void	saveinterrupttable(void *ptr);
volatile void restoreinterrupttable(void * ptr);

#pragma _builtin_(segmentreadable, segmentwritable)
volatile int	segmentreadable(selector sel);
volatile int	segmentwritable(selector sel);

#pragma _builtin_(setlocaltable)
volatile void setlocaltable(selector sel);

#pragma	_builtin_(waitforinterrupt)
volatile void waitforinterrupt(void);


#line 493 "c:\\cadul\\include\\builtin.h"














































 

#pragma	_builtin_(outhword)
volatile void outhword(unsigned short port, unsigned short wordvalue);

#pragma _builtin_(inhword)
volatile unsigned short inhword(unsigned short port);

#pragma _builtin_(blockinhword)
volatile void blockinhword(unsigned short port, unsigned short *despt,
		unsigned int wordcount);

#pragma _builtin_(blockouthword)
volatile void blockouthword(unsigned short port, unsigned short const *srcpt,
		unsigned int wordcount);

#pragma	_builtin_(get_reg_eax)
volatile int get_reg_eax(void);

#pragma	_builtin_(get_reg_ebp)
volatile int get_reg_ebp(void);

#pragma	_builtin_(get_reg_ebx)
volatile int get_reg_ebx(void);

#pragma	_builtin_(get_reg_ecx)
volatile int get_reg_ecx(void);

#pragma	_builtin_(get_reg_edi)
volatile int get_reg_edi(void);

#pragma	_builtin_(get_reg_edx)
volatile int get_reg_edx(void);

#pragma	_builtin_(get_reg_esi)
volatile int get_reg_esi(void);

#pragma	_builtin_(get_reg_esp)
volatile int get_reg_esp(void);

#pragma _builtin_(setcontrolregister)
#pragma _builtin_(getcontrolregister)
volatile void	setcontrolregister(const unsigned char n, unsigned int value);
volatile unsigned int getcontrolregister(const unsigned char n);

#pragma _builtin_(setdebugregister)
#pragma _builtin_(getdebugregister)
volatile void	setdebugregister(const unsigned char n, unsigned int value);
volatile unsigned int getdebugregister(const unsigned char n);

#pragma _builtin_(settestregister)
#pragma _builtin_(gettestregister)
volatile void	settestregister(const unsigned char n, unsigned int value);
volatile unsigned int gettestregister(const unsigned char n);

#pragma	_builtin_(set_reg_fs)
unsigned short volatile set_reg_fs(unsigned short value);

#pragma	_builtin_(set_reg_gs)
unsigned short volatile set_reg_gs(unsigned short value);


#pragma	_builtin_(get_reg_fs)
unsigned short volatile get_reg_fs(void);

#pragma	_builtin_(get_reg_gs)
unsigned short volatile get_reg_gs(void);

#pragma	_builtin_(set_reg_eax)
int volatile set_reg_eax(int value);

#pragma	_builtin_(set_reg_ebp)
int volatile set_reg_ebp(int value);

#pragma	_builtin_(set_reg_ebx)
int volatile set_reg_ebx(int value);

#pragma	_builtin_(set_reg_ecx)
int volatile set_reg_ecx(int value);

#pragma	_builtin_(set_reg_edi)
int volatile set_reg_edi(int value);

#pragma	_builtin_(set_reg_edx)
int volatile set_reg_edx(int value);

#pragma	_builtin_(set_reg_esi)
int volatile set_reg_esi(int value);

#pragma	_builtin_(set_reg_esp)
int volatile set_reg_esp(int value);


#pragma	_builtin_(farptr16)
unsigned long farptr16(void far *fp);

#pragma _builtin_(farptr32)
void far *farptr32(void far *);

#pragma _builtin_(farptr48)
void far *farptr48(void far *);

#pragma	_builtin_(set_reg_ssesp)
void volatile set_reg_ssesp(void far *);





#pragma	_builtin_(byteswap)
unsigned int	byteswap(unsigned int value);

#pragma	_builtin_(invalidatedatacache)
volatile void	invalidatedatacache(void);

#pragma	_builtin_(wbinvalidatedatacache)
volatile void	wbinvalidatedatacache(void);


#pragma	_builtin_(invalidatetlbentry)
volatile void	invalidatetlbentry(void far *);






}

 
#line 67 "c:\\rm3dev\\inc\\misc86.h"






#line 251 "c:\\rm3dev\\inc\\misc86.h"


#line 38 "c:\\rm3dev\\inc\\rmtypes.h"


#line 47 "c:\\rm3dev\\inc\\rmtypes.h"



static const
char idstr_rmtypes_h [] =
{
        "\0"    "(C) SIEMENS AG 1995"   "\0"     
        "\1"    "RMTYPES.H"             "\1"
        "\2"    "0005"                  "\2"
        "\3"    "K.P.H."                "\3"
};




   
   
   


#pragma align (_RmMailboxStruct      = 1)
#pragma align (_RmMailIDStruct       = 1)
#pragma align (_RmTCDStruct          = 1)
#pragma align (_RmXTCDStruct         = 1)
#pragma align (_RmTCBStruct          = 1)
#pragma align (_RmSTKStruct          = 1)
#pragma align (_RmTaskInfoStruct     = 1)
#pragma align (_RmTimeStruct         = 1)
#pragma align (_RmEntryStruct        = 1)
#pragma align (_RmExtendedEntryStruct= 1)
#pragma align (_RmMemPoolInfoStruct  = 1)
#pragma align (_RmRCBStruct          = 1)
#pragma align (_RmAbsTimeStruct      = 1)
#pragma align (_RmAsciiTimeStruct    = 1)
#pragma align (_RmIntrhandMailStruct = 1)
#pragma align (_RmSysB               = 1)
#pragma align (_RmIOStatusStruct     = 1)
#pragma align (_RmDCDStruct          = 1)
#pragma align (_RmUCDHeadStruct      = 1)
#pragma align (_RmUCDStruct          = 1)
#pragma align (_RmDCBStruct          = 1)
#pragma align (_RmUCBStruct          = 1)
#pragma align (_RmIRBStruct          = 1)
#pragma align (_RmTMBStruct          = 1)
#pragma align (_RmSystemTables       = 1)











   
   
   







typedef unsigned long           longlong[2];

typedef unsigned char           uchar;
typedef unsigned short          ushort;
typedef unsigned int            uint;
typedef unsigned long           ulong;

typedef void (far      * rmfarproc) (void);
typedef void (near     * rmnearproc)(void);
typedef void (near  * rmproc)    (void);   

   
   
   

 

typedef struct  _RmMailboxStruct
{
    void       *adr;             




    ushort      pad;             

    uint        len;             
} RmMailboxStruct;

typedef struct  _RmMailIDStruct
{
    ulong        low;           
    ulong        high;          
} RmMailIDStruct;                                                    


 

typedef struct  _RmTCDStruct
{
    uint        eax;              
    uint        ebx;
    ushort      ds;
    ushort      es;
    char       *stck;            



    rmfarproc   task;            





    char       *load;            
                                 
#line 175 "c:\\rm3dev\\inc\\rmtypes.h"
    ushort      time;            
    uchar       ovpri;           
    uchar       bpri;            
    uchar       inpri;           
    uchar       pid;             
    ushort      flags;           
    ushort      rr_ticks;        
                                 

    uint        efg[2];          



    uchar       reserve[4];      
    uint        seq;             
                                 
    uint    	seq_to;	         



} RmTCDStruct;

typedef struct  _RmXTCDStruct
{
    uint        eax;             
    uint        ebx;
    ushort      ds;
    ushort      es;
    char       *stck;            



    rmfarproc   task;            



    char       *load;            
                                 



    char        ovrd_tme_unit;   
    char        ovrd_int_num;    
    char        ovrd_prio_inc;   
    char        ovrd_prio_bnd;   
    char        inherent_prio;   
    char        cpu_id;          
    ushort      flags;           
    ushort      rr_ticks;        

    char        reserve[4];      
    uint        seq;             
                                 
    uint        seq_to;          



} RmXTCDStruct;


 

typedef struct  _RmTCBStruct
{
    struct _RmTCBStruct near *link;  
    uchar       pri;             
    uchar       state;           
    uint        esp;             
    ushort      ss;              

    uchar       schdl[8];        



    struct _RmRCBStruct near *qrst;     
    struct _RmRCBStruct near *crcb;     
    struct _RmTMBStruct near *tmb;      
    uchar       pid;             
    uchar       flags;           
    uint        msg;             
    uint        stmb;            
    struct _RmTCDStruct far  *tcd;     



    ushort      sel;             

    ushort      tcb_res1;        
    void far  *cr_tdp;          
    void far  *cr_inhp;         
    ushort      tasktype;        
    ushort      lseg;            
    void near *nextsmr;         

} RmTCBStruct;

 

typedef    struct _RmSTKStruct
{
    uint    ds;      

    uint    gs;      
    uint    fs;      

    uint    es;      
    uint    edi;     
    uint    esi;     
    uint    ebp;     
    uint    esp;     
    uint    ebx;     
    uint    edx;     
    uint    ecx;     
    uint    eax;     
    uint    eip;     
    uint    cs;      
    uint    efl;     
} RmSTKStruct;      

 

typedef struct  _RmTaskInfoStruct
{
    uchar       pri;             
    uchar       state;           
    uint       *sp_ss;           




    longlong    rdy_time;        



    char        cpu_id;          
    char        flg;             
    struct _RmTCDStruct *tcd_ptr;  



} RmTaskInfoStruct;


 

typedef struct  _RmTimeStruct
{
    uchar       day;
    uchar       month;
    ushort      year;
    uchar       hours;
    uchar       minutes;
    uchar       seconds;
} RmTimeStruct;


 

typedef struct _RmEntryStruct
{
    uchar       slen;            
    char        string[16];      
    uchar       type;            
    ulong       ide;             
    ushort      id;              
} RmEntryStruct;

typedef struct _RmExtendedEntryStruct
{
    uchar       slen;            
    char        string[10];      
    char       *text;            
    uchar       type;            
    ulong       ide;             
    ushort      id;              
} RmExtendedEntryStruct;
                     
                     
 

typedef struct _RmMemPoolInfoStruct
{   
    ulong       pool_size;       
    ulong       avail_mem_size;  
    ulong       max_block_size;  
    ulong       reserved[5];     
} RmMemPoolInfoStruct;
                     
                     
 

typedef struct _RmRCBStruct
{
    struct _RmRCBStruct near *link;  
    char        pri;             
    char        cord;            
    struct _RmTCBStruct near *wtcb;  
    uint        eax;             
    uint        ebx;             
    struct _RmTCBStruct near *tcb;   
    uint        res1[2];         
     
    void       *ord_ptr;         



    uchar      *tcd_load;        
                                 
                                 



    uint        reserved[4];     
} RmRCBStruct;


 

typedef struct _RmAbsTimeStruct
{
    ulong       lotime;          
    ulong       hitime;          
} RmAbsTimeStruct;

 

typedef struct _RmAsciiTimeStruct
{
    char        day[2];          
    char        delim0;          
    char        month[3];        
    char        delim1;          
    char        year[4];         
    char        blank;           
    char        hour[2];         
    char        colon0;          
    char        min[2];          
    char        colon1;          
    char        sec[2];          
} RmAsciiTimeStruct;


 
   
typedef struct _RmIntrhandMailStruct
{
    uint        int_no;
    uint        int_vec             : 8;
    uint        int_kind            : 1;
    uint        lost_int_overflow   : 1;

    uint        dummy_2             : 22;



    ushort      lost_int;

    ushort      dummy_3;

} RmIntrhandMailStruct;


 
   
typedef struct _RmSysB
{
    uchar       version[6];      
    ushort      proctype;        
                                 
                                 
                                 
                                 
    ushort      systemtype;      
                                 
                                 
                                 
    ushort      res1;            
    ulong       reserved;        
                                     
    char        statname[16];    
    uchar       bootfname[128];  
    uchar       bootnode[6];     
    uchar       bootdrive;       
                                 
                                 
                                 
                                 
                                 
                                 
                                 
    uchar       res2;            
                                     
    ulong       ram_size;        
    uint        smr_max;         
    uint        smr_used;        
    uint        smr_avail;       
    uint        out_of_smr_count; 

    ushort      fl_er_sel;       
    ushort      fl_rw_sel;       

                                     
    ushort      rate_msec;       
    ulong       rate_usec;       
    ulong       pit_count;       
    ushort      timer_int;       
                                     
    rmproc      issue_eoi_entry; 
    uchar       pic_count;       
    uchar       pic_base[8];     
                                 
    uchar       pic_mask[8];     
                                     

    uchar       res3[3];         



    int (far  * set_pic_mask)(uint irq);   
                                 




    ushort      res4;            

                                 
    int (far  * init_pit)(void); 




    ushort      res5;            

                                 
    int (far  * set_rtc_entry)(RmTimeStruct *); 




    ushort      res6;            

                                 
    int (far  * get_rtc_entry)(RmTimeStruct *); 




    ushort      res7;            

                                 
    int (far  * putchar_entry)(char);




} RmSysB;


 
   
typedef struct _RmIOStatusStruct
{
    char        primary;
    char        secondary;
    ushort      count;

    ushort      status3;
    ushort      status4;

} RmIOStatusStruct;

 
   
typedef struct _RmSystemTables
{
    void *tcb_table;
    uint        tcb_num;
    void *gefd_table;
    uint        gefd_num;
    void *scbd_table;
    uint        scbd_num;
    void *mbxd_table;
    uint        mbxd_num;
    void *mpdd_table;
    uint        mpdd_num;
    void *mpbd_table;
    uint        mpbd_num;
    void *system_table;
    uint        system_num;
    void *hook_table;
    uint        hook_num;
    void *user_table_code;
    uint        user_num_code;
    void *user_table_data;
    uint        user_num_data;
} RmSystemTables;


 

typedef struct _RmDCDStruct
{
    struct _RmUCDStruct near *ucd;   
    uchar       units;           
    uchar       shr;             
                                 
    rmproc      init;            
    rmproc      svc;             
                                 
    uchar       flags;           
                                







 
    uchar       fmax;            

    uchar       res[4];          



} RmDCDStruct;


 

typedef struct _RmUCDHeadStruct
{
    uchar       pid;             
    uchar       intno;           
    rmfarproc   intadr;          
    ushort      uns;             
} RmUCDHeadStruct;
        
typedef struct _RmUCDStruct
{
    uchar       pid;             
    uchar       intno;           
    rmfarproc   intadr;          
    ushort      uns;             

    uchar       port[256-10];    



} RmUCDStruct;


 

typedef struct _RmDCBStruct
{
    struct _RmDCBStruct near *link;  
    uchar       id;              
    uchar       sts;             
    struct _RmIRBStruct near *qirb;  
    struct _RmIRBStruct near *cirb;  
    struct _RmUCBStruct near *ucb;   
    struct _RmDCDStruct near *dcd;   

    uchar       gpr[256-22];     



} RmDCBStruct;


 

typedef struct _RmUCBStruct
{
    struct _RmUCBStruct near *link;  
    uchar       unit;            
    uchar       sts;             
    struct _RmIRBStruct near *qirb;  
    struct _RmIRBStruct near *cirb;  
    ushort      seg;             
    struct _RmDCBStruct near *dcb;   
    struct _RmUCDStruct near *ucd;   
    struct _RmTCBStruct near *tcb;   

    uchar       gpr[256-28];     



} RmUCBStruct;


 

typedef struct _RmIRBStruct
{
    struct _RmIRBStruct near *link;  
    ushort      pri;             
    struct _RmTCBStruct near *tcb;   
    struct _RmUCBStruct near *ucb;   
    struct _RmTMBStruct near *tmb;   
    uchar       rio;             
    uchar       funct;           
    uchar       device;          
    uchar       unit;            
    uchar       grp;             
    uint        flags;           
    void       *status;          



    void       *bufr;            
                                 



    ushort      seq;             
} RmIRBStruct;


 

typedef struct _RmTMBStruct
{
     
    struct _RmTMBStruct near *link;  
    uint        ltime;           
    uint        htime;           
    uchar       type;            
                                 
                                 
                                 
                                 
                                 
                                 
                                 
                                 
                                 
    union
    {
     
        struct
        {
            uchar   res;
            struct _RmUCBStruct near *ucb;  
            void   *sadr;            




        } type_1;
     
        struct
        {
            uchar   res;
            struct _RmTCBStruct near *tcb;  
        } type_2;
     
        struct
        {
            uchar   efgrp;           
            struct _RmTCBStruct near *tcb;  
            uint    efmsk;           
        } type_3;
     
        struct
        {
            uchar   res;
            struct _RmTCBStruct near *tcb;  
        } type_4;
     
        struct
        {
            uchar   res;
            struct _RmTCBStruct near *tcb;  
            uchar   ovpri;           
            uchar   bpri;            
            uchar   ovtime;          
        } type_5;
     
        struct
        {
            uchar   res;
            struct _RmTCBStruct near *tcb;  
            uint    swb;             
            uint    sem;             
        } type_6;
     
        struct
        {
            uchar   res;
            struct _RmIRBStruct near *irb;  
        } type_7;
     
        struct
        {
            uchar   res;
            uint    tjt;         
            ushort  svc;         
            uint    qh;          
            uint    wb;          
        } type_8;
     
        struct
        {
            uchar   res[3];
            uint    alarm;       
            uint    tib;         
        } type_9;
    } utmb;
} RmTMBStruct;


   
   
   












#line 34 "c:\\rm3dev\\inc\\efs.h"








static const
char idstr_efs_h [] =
{
        "\0"    "(C) SIEMENS AG 1995"   "\0"     
        "\1"    "EFS.H"                 "\1"
        "\2"    "0003"                  "\2"
        "\3"    "A.J."                  "\3"
};








 


 #pragma align( _EUSE_RPB  = 1)
 #pragma align( _ESTOP_RPB = 1)
 #pragma align( _ENOOP_RPB = 1)
 #pragma align( _ECTL_RPB  = 1)
 #pragma align( _ESYS_RPB  = 1)
 #pragma align( _EDG_RPB   = 1)
 #pragma align( _EVS_RPB   = 1)
 #pragma align( _ECHV_RPB  = 1)
 #pragma align( _ESTI_RPB  = 1)
 #pragma align(  efs_addr  = 1)
 #pragma align( _TS_DESC   = 1)
 #pragma align( _EFS_START_SERVER = 1)
#line 80 "c:\\rm3dev\\inc\\efs.h"



 



 






typedef	struct	{
short	unsigned	 loctsapid;
short	unsigned	 remtsapid;
long	unsigned	 subnetid;
char	unsigned	 netaddress[6];
short	unsigned	 nsapid;
		char		 res1;
		char		 medium;
		char		 res2;
		char		 res3;
		} efs_addr;

typedef	struct _EUSE_RPB	{
		char		 vol_name [2];	 
		char		 rvol_name [2]; 
 
		efs_addr 	*netaddr;		
 
		char		*netname;		
 
short	unsigned	 vol_flags;		 
		char		*rvol_namep;	 
									 
		} EUSE_RPB;

#line 132 "c:\\rm3dev\\inc\\efs.h"



 

typedef	struct _ESTOP_RPB	{
		char		 vol_name[2];	 
		} ESTOP_RPB;



 

typedef	struct _ENOOP_RPB	{
		char		 vol_name[2];	 
short	unsigned	 vol_flags;		 
		} ENOOP_RPB;



 

typedef	struct _ECTL_RPB	{
		char		 vol_name[2];	 
short	unsigned	 vol_flags;		 
		} ECTL_RPB;



 

typedef	struct _ESYS_RPB	{
		char		 vol_name[2];	 
short	unsigned	 task_id;		 
short	unsigned	 mess_len;		
 
		char 		*mess_adr;		 
		} ESYS_RPB;
 


 

typedef struct _EVS_RPB	{
		char		 vol_name[2];
		VOL_DATA	*vol_vib;
		unsigned	 vol_flags;
		long		 free_blocks;
		unsigned	 open_files,
					 write_errors;
		} EVS_RPB;



 

typedef struct _ECHV_RPB {
		char		 vol_name[2];
		VOL_DATA	*vol_data;
		} ECHV_RPB;



 

typedef struct _ESTI_RPB {
		char		 vol_name[2];
		char		 date[8];
		char		 time[8];
		} ESTI_RPB;



 

typedef	struct _EDG_RPB	{
		char		 vol_name [2];	 
		efs_addr 	*netaddr;		
 
		char 		*buffer;		 
short	unsigned	 length;		 
		} EDG_RPB;



 

 

#line 232 "c:\\rm3dev\\inc\\efs.h"



 

typedef	struct	{
		char		 access;
		char		 mode;
		char		 res[14];
		} ctl_datagram;











 



 



#line 286 "c:\\rm3dev\\inc\\efs.h"

#line 317 "c:\\rm3dev\\inc\\efs.h"



 






#line 333 "c:\\rm3dev\\inc\\efs.h"














 

#line 360 "c:\\rm3dev\\inc\\efs.h"



 

typedef	struct _TS_DESC	{
		efs_addr 	 netaddr;		 
short   unsigned     scount;         
short   unsigned     ncount;         
		} TS_DESC;

typedef	struct _EFS_START_SERVER	{
		char		 version;		 
		char		 ts_count;		 
		TS_DESC		*ts_desc[16];	 
		} EFS_START_SERVER;

#line 405 "c:\\rm3dev\\inc\\efs.h"



 

typedef	struct	{
	char	 vcb_name [2];	 
	unsigned long	 vcb_sects;		 
									 
	unsigned int	 vcb_dsze;		





 
	char	 vcb_dev [2];	

 
	unsigned int	 vcb_status;	 
	unsigned long 	 vcb_bmap;		




 
	unsigned short	 vcb_flg_grp;
	unsigned int	 vcb_flg_msk;	
 
	union	{
	char 	*vcb_boot;		
 
	char 	*vcb_data;		 
			} u5;
	char 	*vcb_pref_buf;	 
	unsigned int	 vcb_flags;		


 
							 
	unsigned int	 vcb_dccb;		 
	efs_addr *vcb_nadr;		 
	unsigned int	 vcb_open;		 
	unsigned short	 vcb_acc_rights; 
	char	 		*vcb_ser_namep;  
	unsigned short	 vcb_ser_desc;	 
	unsigned char	 vcb_ser_dw;	 
	unsigned char	 vcb_ser_ver;	 
	char	 vcb_ser_sys[16];  
	char	 vcb_sname[16];	 
		} vcb;

typedef struct  {
    int (near *ts_initp)(    );  
    int (near *ts_exitp)(    );  
    int (near *initp)(    );     
    int (near *exitp)(    );     
    int (near *callp)(    );     
    int (near *listenp)(    );   
    int (near *closep)(    );    
    int (near *sendp)(    );     
    int (near *send_eomp)(    ); 
    int (near *receivep)(    );  
    int (near *snddgp)(    );    
    int (near *rcvdgp)(    );    
    int (near *cancelp)(    );   
    int (near *statusp)(    );   
    int (near *errorp)(    );    
    int (near *cmpadrp)(    );   




                } jump_table;









int	far RcInitEfs			( void );
int far RcDecodeEfsError	( uint, int, char * );
int far RcASCIIDecodeEfs	( char * );
int	far RcInitEfsLayer	( jump_table const *(near *)(uchar), char *, char,
	ushort, ushort, ushort, ushort,	ushort, ushort, ushort, ushort );
int	far RcInitEfsBk1Layer	( ushort, ushort, ushort );
int	far RcInitEfsSocLayer	( ushort, ushort, ushort );
int	far RcInitEfsMpiLayer	( ushort, ushort, ushort );
int	far RcInitEfsSh1Layer	( ushort, ushort, ushort );
int	far RcInitEfsRedir	( void );
int	far RcAddEfsRedirUnit	( char *, ushort, ushort );
int	far RcInitEfsServer	( ushort );
int far RcInitEfsWdog	( void );

jump_table const	* near x_efs_bk1_init ( uchar );
jump_table const	* near x_efs_soc_init ( uchar );
jump_table const	* near x_efs_mpi_init ( uchar );
jump_table const	* near x_efs_sh1_init ( uchar );

#line 55 "\\rm3dev\\inc\\io.h"




extern "C" {


extern int     far access     (const char *filename, int amode);
extern int       far changevib  (char *volume, VOL_DATA *newvib);
extern int       far checkpoint (int handle);
extern int       far chmod      (const char *filename, int pmode);
extern int     far close      (int handle);
extern int       far createvib  (VOL_DATA *newvib, int poolid);
extern int     far dismount   (const char *volume_name);
extern size_t  far duwrite    (int device, int unit, const void *buffer,
                                      size_t nbytes);
extern size_t  far duread     (int device, int unit, void *buf,
                                      size_t nsize);
extern int       far efsstop    (char *volume);
extern int       far efsuse     (char *volume, char *rvolume,
                                      efs_addr *naddr, char *nname);
extern int       far getvolumestatus (char *volume, VOL_DATA *volvib,
                                           unsigned long *freeblocks,
                                           unsigned *openfiles,
                                           unsigned *writeerrors);
extern int       far inhibitabort    (int mode);
extern long    far lseek      (int handle, long offset, int ptofref);
extern int     far mount      (const char *volume_name, int format);
extern int       far open       (const char *pathname, int access, ... );
extern size_t  far read       (int handle, void *buf, size_t nbytes);
extern int     far remap      (const char *volume_name, int format);
extern int       far search     (int *record, char *string,
                                      DIR_ENTRY *direntry);
extern int     far unlink     (const char *filename);
extern size_t  far write      (int handle, const void *buffer,
                                      size_t nbytes);

extern int     far x_cr_getskhandle   (void);
extern int     far x_cr_allocskhandle (size_t scb_size);


}






#line 1 "c:\\rm3dev\\inc\\fcntl.h"





















 







 
 




                                 







 




 
 






 
#line 65 "c:\\rm3dev\\inc\\fcntl.h"
 
#line 73 "c:\\rm3dev\\inc\\fcntl.h"

#line 105 "\\rm3dev\\inc\\io.h"



 





#line 37 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\rmos_inc.h"
#line 1 "c:\\rm3dev\\inc\\rmapi.h"





























 




#line 1 "c:\\rm3dev\\inc\\rmdef.h"
























 




#line 36 "c:\\rm3dev\\inc\\rmdef.h"




static const
char idstr_rmdef_h [] =
{
        "\0"    "(C) SIEMENS AG 1995"   "\0"     
        "\1"    "RMDEF.H"               "\1"
        "\2"    "0004"                  "\2"
        "\3"    "K.P.H."                "\3"
};




   
   
   













   
   
   


                          
#line 82 "c:\\rm3dev\\inc\\rmdef.h"
                          
#line 144 "c:\\rm3dev\\inc\\rmdef.h"




  
   
   
   

                 






                      





                   








                      





                       






                 





 



                 

#line 208 "c:\\rm3dev\\inc\\rmdef.h"


                     






         






            




                

#line 247 "c:\\rm3dev\\inc\\rmdef.h"

                





                




               





               





             





                










                       

#line 301 "c:\\rm3dev\\inc\\rmdef.h"


                   

#line 315 "c:\\rm3dev\\inc\\rmdef.h"

#line 324 "c:\\rm3dev\\inc\\rmdef.h"

#line 333 "c:\\rm3dev\\inc\\rmdef.h"

#line 342 "c:\\rm3dev\\inc\\rmdef.h"

#line 351 "c:\\rm3dev\\inc\\rmdef.h"

#line 360 "c:\\rm3dev\\inc\\rmdef.h"

#line 369 "c:\\rm3dev\\inc\\rmdef.h"

#line 378 "c:\\rm3dev\\inc\\rmdef.h"

                             






                                                     

                                                     

                                                     

                                                     


                     








                 

#line 443 "c:\\rm3dev\\inc\\rmdef.h"


                 

#line 453 "c:\\rm3dev\\inc\\rmdef.h"


                      






                                                     




            

#line 480 "c:\\rm3dev\\inc\\rmdef.h"


                 





                 





                  





                          





                          






                         





















#line 43 "c:\\rm3dev\\inc\\rmapi.h"








static const
char idstr_rmapi_h [] =
{
        "\0"    "(C) SIEMENS AG 1995"   "\0"     
        "\1"    "RMAPI.H"               "\1"
        "\2"    "0010"                  "\2"
        "\3"    "B.N."                  "\3"
};



  
  
  

  
  
  


 #pragma fixedparams (RmResetOS,RmInitOS,RmCreateOS,RmSetOS,RmRunOS)
 #pragma fixedparams (RmSetPutcharProc,RmSetSVC,RmSetSMRCount)



extern "C" {




int  far RmResetOS(              uint            NPXTestMode,
                                        ulong           SysBAddress,
                                        ulong           RAMEndAddress );


#line 92 "c:\\rm3dev\\inc\\rmapi.h"
int  far RmInitOS(               ulong           SystemPeriod,
                                        rmfarproc       InitTimerProc,
                                        rmproc          IssueEOIProc,
                                        int ( far *SetPICMaskProc)(uint IRQ),
                                        int ( far *SetClockProc)(RmTimeStruct *pDate),
                                        int ( far *GetClockProc)(RmTimeStruct *pDate) );

int  far RmCreateOS(             uint            SemaphoreNum,
                                        uint            FlagNum,
                                        uint            MailboxNum );

int  far RmSetOS(                uint            RoundRobinCounter,
                                        uint            SVCExceptionType,
                                        const char far *pUnitName );



int  far RmRunOS(                const char far *pTaskName );

int  far RmSetPutcharProc(       int( far *PutcharProc)(char) );

int  far RmSetSVC(               uint            SVCNumber,
                                        rmfarproc       SVCHandler );


int  far RmSetSMRCount(          uint            SMRNumber );


}


  
  
  


 #pragma fixedparams (RmDecode,RmLinkDecodeProc,RmLinkTimerProc)
 #pragma fixedparams (RmUnlinkTimerProc,RmGetSystemTables,RmGetSysB)



extern "C" {






int  far RmDecode(               uint            Type,
                                        int             Code,
                                        char       far *pText );

int  far RmLinkTimerProc(        rmfarproc       ProcEntry );

int  far RmUnlinkTimerProc(      rmfarproc       ProcEntry );

int  far RmGetSystemTables(      RmSystemTables far *pSystemTables );



int  far RmLinkDecodeProc(       rmfarproc       DecodeProc );



int  far RmGetSysB(              RmSysB far * far *ppSysB );


}


  
  
  



 #pragma fixedparams (RmCreateDescriptor,RmDeleteDescriptor,RmChangeDescriptor)
 #pragma fixedparams (RmChangeDescriptorAccess,RmGetLinAddress,RmMapMemory)
 #pragma fixedparams (RmGetPhysAddress,RmFlatToSegAddress,RmSegToFlatAddress)



extern "C" {




int  far RmCreateDescriptor(       ulong         LinAddress,
                                          ulong         Limit,
                                          selector far *pSel );

int  far RmDeleteDescriptor(       selector      Sel );

int  far RmChangeDescriptor(       selector      Sel,
                                          ulong         LinAddress,
                                          ulong         Limit );

int  far RmChangeDescriptorAccess( selector      Sel,
                                          uint          Access );



#line 202 "c:\\rm3dev\\inc\\rmapi.h"

int  far RmGetLinAddress(          void     far *pPointer,
                                          ulong    far *pLinAddress );

int  far RmGetPhysAddress(         void     far *pPointer,
                                          ulong    far *pPhysAddress );

int  far RmMapMemory(              ulong         PhysAddress,
                                          ulong         Length,
                                          void far * far *pPointer );

int  far RmFlatToSegAddress(       ulong         FlatAddress,
                                          ushort   far *pSel,
                                          ulong    far *pOffset);

int  far RmSegToFlatAddress(       ushort        Sel,
                                          ulong         Offset,
                                          ulong    far *pFlatAddress );


}




  
  
  


 #pragma fixedparams (RmAlloc,RmFree,RmReAlloc,RmFreeAll)
 #pragma fixedparams (RmExclude,RmGetSize)
 #pragma fixedparams (RmMemPoolAlloc,RmCreateMemPool,RmDeleteMemPool)
 #pragma fixedparams (RmGetMemPoolInfo)



extern "C" {






int  far RmAlloc(                ulong           TimeOutValue,
                                        uint            Mode,
                                        ulong           Size,
                                        void far * far *ppMemory );

int  far RmFree(                 void       far *pMemory );





int  far RmReAlloc(              ulong           TimeOutValue,
                                        uint            Mode,
                                        ulong           NewSize,
                                        void far * far *ppMemory );

int  far RmFreeAll(              uint            TaskID );

#line 273 "c:\\rm3dev\\inc\\rmapi.h"

int  far RmExclude(              ulong           PhysAddress,
                                        ulong           Size,
                                        void far * far *ppMemory );

int  far RmGetSize(              void       far *pMemory,
                                        ulong      far *pSize );

int  far RmMemPoolAlloc(         ulong           TimeOutValue,
                                        uint            Mode,
                                        uint            PoolID,
                                        ulong           Size,
                                        void far * far *ppMemory );

int  far RmGetMemPoolInfo(       uint            PoolID,
                                        RmMemPoolInfoStruct far *Info);

int  far RmCreateMemPool(        const char far *pPoolName,
                                        void       far *pPoolAddress,
                                        ulong           Size,
                                        uint       far *pPoolID);

int  far RmDeleteMemPool(        uint            PoolID);


}


  
  
  


 #pragma fixedparams (RmCatalog,RmList,RmGetEntry,RmGetName,RmUncatalog)



extern "C" {


#line 322 "c:\\rm3dev\\inc\\rmapi.h"

int  far RmCatalog(              uint            Type,
                                        uint            ID,
                                        ulong           IDEx,
                                        const char far *pName );

int  far RmList(                 uint            Type,
                                        uint            Count,
                                        uint       far *pIndex,
                                        uint       far *pNumEntries,
                                        RmEntryStruct far *pEntry );

int  far RmGetEntry(             ulong           TimeOutValue,
                                        const char far *pName,
                                        RmEntryStruct far *pEntry );

int  far RmGetName(              uint            Type,
                                        uint            ID,
                                        ulong           IDEx,
                                        char       far *pName );

int  far RmUncatalog(            const char far *pName );


}


  
  
  


 #pragma fixedparams (RmCreateTask,RmDeleteTask,RmStartTask,RmQueueStartTask)
 #pragma fixedparams (RmCreateChildTask,RmGetTCBAddress)
 #pragma fixedparams (RmEndTask,RmKillTask,RmRestartTask)
 #pragma fixedparams (RmResumeTask,RmSuspendTask,RmActivateTask,RmPauseTask)
 #pragma fixedparams (RmGetTaskID,RmGetTaskPriority,RmSetTaskPriority)
 #pragma fixedparams (RmGetTaskState,RmGetTaskInfo,RmEnableScheduler)
 #pragma fixedparams (RmDisableScheduler,RmCreateTaskEx)

 #pragma fixedparams (RmQCopy,RmLinkLRS,RmSequenceTask)




extern "C" {


#line 377 "c:\\rm3dev\\inc\\rmapi.h"

int  far RmCreateTask(           const char far *pTaskName,
                                        ulong           TaskStackSize,
                                        uint            Priority,
                                        rmfarproc       TaskEntry,
                                        uint       far *pTaskID );

int  far RmCreateChildTask(      const char far *pTaskName,
                                        ulong           TaskStackSize,
                                        uint            Priority,
                                        rmfarproc       TaskEntry,
                                        uint       far *pTaskID );

int  far RmCreateTaskEx(         const char far *pTaskName,
                                        RmTCDStruct far *pTcd,
                                        uint       far *pTaskID );

int  far RmDeleteTask(           uint            TaskID );

#line 402 "c:\\rm3dev\\inc\\rmapi.h"

int  far RmStartTask(            uint            Wait,
                                        uint            TaskID,
                                        uint            Priority,
                                        uint            RegVal1,
                                        uint            RegVal2 );

int  far RmQueueStartTask(       uint            Wait,
                                        uint            TaskID,
                                        uint            Priority,
                                        uint            RegVal1,
                                        uint            RegVal2 );

int  far RmEndTask(              void );






int  far RmKillTask(             uint            Mode,
                                        uint            TaskID );

int  far RmRestartTask(          uint            Mode,
                                        ulong           TimeValue );

int  far RmResumeTask(           uint            TaskID );

int  far RmSuspendTask(          uint            TaskID );

int  far RmActivateTask(         uint            TaskID );

int  far RmPauseTask(            ulong           TimeValue );

#line 444 "c:\\rm3dev\\inc\\rmapi.h"

int  far RmGetTaskID(            uint            Tcb,
                                        uint       far *pTaskID );

int  far RmGetTCBAddress(        uint            TaskID,
                                        void far * far *ppTcb );

int  far RmGetTaskPriority(      uint            TaskID,
                                        uint       far *pPriority );

int  far RmSetTaskPriority(      uint            TaskID,
                                        uint            Priority );

int  far RmGetTaskState(         uint            TaskID,
                                        uint       far *pTaskState );

int  far RmGetTaskInfo(          uint            TaskID,
                                        RmTaskInfoStruct far *pTaskInfo );

int  far RmEnableScheduler(      void );

int  far RmDisableScheduler(     void );


int  far RmQCopy(                RmRCBStruct far *Rcb );







int  far RmLinkLRS(              uint            TaskID,
                                        void       far *pLRS );

int  far RmSequenceTask(         uint            Mode,
                                        uint            StartTaskID,
                                        uint            EndTaskID );


}


  
  
  


 #pragma fixedparams (RmCreateDriver,RmDeleteDriver,RmCreateUnit,RmDeleteUnit)
 #pragma fixedparams (RmResumeDriver,RmSuspendDriver,RmIO)



extern "C" {



int  far RmCreateDriver(         uint            Mode,
                                        const char far *pDeviceName,
                                        RmDCDStruct far *pDcd,
                                        uint       far *pDriverID );

int  far RmDeleteDriver(         uint            DeviceID );

int  far RmCreateUnit(           const char far *pDeviceName,
                                        const char far *pUnitName,
                                        RmUCDStruct far *pUcd,
                                        uint       far *pUnitID );

int  far RmDeleteUnit(           uint            DeviceID,
                                        uint            UnitID );

int  far RmResumeDriver(         uint            DeviceID );

int  far RmSuspendDriver(        uint            DeviceID );

int  far RmIO(                   uint            Function,
                                        uint            DeviceID,
                                        uint            UnitID,
                                        uint            FlagID,
                                        uint            FlagMask,
                                        RmIOStatusStruct far *pState,
                                        void       far *pParam );




}


  
  
  


 #pragma fixedparams (RmCreateFlagGrp,RmDeleteFlagGrp,RmSetFlag)
 #pragma fixedparams (RmSetFlagDelayed,RmGetFlag,RmResetFlag)
 #pragma fixedparams (RmSetLocalFlag,RmResetLocalFlag)



extern "C" {






int  far RmCreateFlagGrp(        const char far *pFlagGrpName,
                                        uint       far *pFlagGrpID );

int  far RmDeleteFlagGrp(        uint            FlagGrpID );

#line 567 "c:\\rm3dev\\inc\\rmapi.h"

int  far RmSetFlag(              uint            FlagGrpID,
                                        uint            FlagMask );

int  far RmSetFlagDelayed(       ulong           TimeValue,
                                        uint            FlagGrpID,
                                        uint            FlagMask );

int  far RmResetFlag(            uint            FlagGrpID,
                                        uint            FlagMask );

int  far RmGetFlag(              ulong           TimeOutValue,
                                        uint            Type,
                                        uint            FlagGrpID,
                                        uint            TestMask,
                                        uint       far *pFlagMask );

int  far RmSetLocalFlag(         uint            TaskID,
                                        uint            FlagMask );

int  far RmResetLocalFlag(       uint            TaskID,
                                        uint            FlagMask );


}


  
  
  


 #pragma fixedparams (RmCreateMailbox,RmDeleteMailbox,RmSendMail)
 #pragma fixedparams (RmReceiveMail,RmSetMailboxSize,RmSendMailDelayed)
 #pragma fixedparams (RmSendMailCancel)



extern "C" {





int  far RmCreateMailbox(        const char far *pMailboxName,
                                        uint       far *pMailboxID );

int  far RmDeleteMailbox(        uint            MailboxID );

#line 626 "c:\\rm3dev\\inc\\rmapi.h"

int  far RmSendMail(             ulong           TimeOutValue,
                                        uint            Priority,
                                        uint            MailboxID,
                                        void       far *pMail );

int  far RmReceiveMail(          ulong           TimeOutValue,
                                        uint            MailboxID,
                                        void       far *pMail );

int  far RmSetMailboxSize(       uint            MailboxID,
                                        uint            Limit );

int  far RmSendMailDelayed(      ulong           TimeValue,
                                        uint            Priority,
                                        uint            MailboxID,
                                        void       far *pMail,
                                        RmMailIDStruct far *pMailID );

int  far RmSendMailCancel(       RmMailIDStruct far *pMailID,
                                        void       far *pMail );


}


  
  
  


 #pragma fixedparams (RmCreateMessageQueue,RmDeleteMessageQueue,RmSendMessage)
 #pragma fixedparams (RmReadMessage,RmSetMessageQueueSize,RmGetStatusMessageQueue)



extern "C" {






int  far RmCreateMessageQueue(   char       far *pMessageQueueName,
                                        uint            TaskID );

int  far RmDeleteMessageQueue(   uint            TaskID );

#line 681 "c:\\rm3dev\\inc\\rmapi.h"

int  far RmSendMessage(          ulong           TimeOutValue,
                                        uint            Priority,
                                        uint            TaskID,
                                        uint            Message,
                                        void       far *pMessageParam );

int  far RmReadMessage(          ulong           TimeOutValue,
                                        uint       far *pMessage,
                                        void far * far *pMessageParam );

int  far RmSetMessageQueueSize(  uint            TaskID,
                                        uint            Limit );

int  far RmGetStatusMessageQueue(uint            TaskID,
                                        uint       far *NumberOfMessages );


}


  
  
  


 #pragma fixedparams (RmCreateBinSemaphore,RmDeleteBinSemaphore)
 #pragma fixedparams (RmReleaseBinSemaphore,RmGetBinSemaphore)



extern "C" {






int  far RmCreateBinSemaphore(   const char far *pSemaphoreName,
                                        uint       far *pSemaphoreID );

int  far RmDeleteBinSemaphore(   uint            SemaphoreID );

int  far RmReleaseBinSemaphore(  uint            SemaphoreID );





int  far RmGetBinSemaphore(      ulong           TimeOutValue,
                                        uint            SemaphoreID );


}


  
  
  


 #pragma fixedparams (RmSetSystemTime,RmGetSystemTime,RmSetHWClockTime)
 #pragma fixedparams (RmGetHWClockTime,RmGetAbsTime,RmGetSystemPeriod)
 #pragma fixedparams (RmSetClocks,RmSetSystemPeriod)



extern "C" {


int  far RmSetSystemTime(        const RmAsciiTimeStruct far *pTimeInfo );

int  far RmGetSystemTime(        RmAsciiTimeStruct far *pTimeInfo );

int  far RmSetHWClockTime(       const RmAsciiTimeStruct far *pTimeInfo );

int  far RmGetHWClockTime(       RmAsciiTimeStruct far *pTimeInfo );

int  far RmSetClocks(            const RmAsciiTimeStruct far *pTimeInfo );

int  far RmGetAbsTime(           RmAbsTimeStruct   far *pAbsTime );

int  far RmGetSystemPeriod(      ulong             far *pTime );

int  far RmSetSystemPeriod(      ulong                   Time );


}


  
  
  


 #pragma fixedparams (RmIntrhand,RmSetDeviceHandler)



extern "C" {







int  far RmIntrhand(             uint            IntType,
                                        uint            IntNum,
                                        uint            ID,
                                        uint            IntPriv,
                                        rmfarproc       Entry0,
                                        rmfarproc       Entry1,
                                        rmfarproc  far *pOldEntry );

 
#line 805 "c:\\rm3dev\\inc\\rmapi.h"

 
#line 815 "c:\\rm3dev\\inc\\rmapi.h"

 
#line 825 "c:\\rm3dev\\inc\\rmapi.h"

 
#line 835 "c:\\rm3dev\\inc\\rmapi.h"

 
#line 845 "c:\\rm3dev\\inc\\rmapi.h"

 
#line 855 "c:\\rm3dev\\inc\\rmapi.h"

 
#line 865 "c:\\rm3dev\\inc\\rmapi.h"

 
#line 875 "c:\\rm3dev\\inc\\rmapi.h"






int  far RmSetDeviceHandler(     uint            IntNum,
                                        const char      *pDeviceName,
                                        const char      *pUnitName,
                                        rmfarproc       HandlerEntry );


}



  
  
  


 #pragma fixedparams (RmSetBreakpoint,RmKillBreakpoint)



extern "C" {








int  far RmSetBreakpoint(        uint            CpuID,
                                        uint            BpID,
                                        uint            BpType,
                                        void       far *BpAddress,
                                        uint            BpCount,
                                        void       far *BpStruct );

int  far RmKillBreakpoint(       uint            CpuID,
                                        uint            BpID );

  
  
  

 
#line 930 "c:\\rm3dev\\inc\\rmapi.h"
    
#line 938 "c:\\rm3dev\\inc\\rmapi.h"

#line 945 "c:\\rm3dev\\inc\\rmapi.h"


}


  
  
  





 #pragma fixedparams (getparm, get2ndparm, getdword)



extern "C" {


int *           far getparm(     void );  
unsigned int    far get2ndparm(  void );  
unsigned long   far getdword(    void );  


}




  
  
  





 #pragma fixedparams (x_bu_get, x_bu_init)



extern "C" {


int  far x_bu_get(               char       far *busy_ptr );
int  far x_bu_init(              void );


}







#line 38 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\rmos_inc.h"
#line 1 "c:\\rm3dev\\inc\\task.h"






















 









            
            
#pragma varparams   ("xinitc", "xinitt", "x_cr_killtsk")
#pragma fixedparams ("x_cr_gettaskid", "x_cr_gettaskparam")
#pragma fixedparams ("x_cr_initenv", "x_cr_setexit")

#pragma align (std_struct = 4)
















struct std_struct
        {
        int             stdin_dev;
        int             stdin_unit;
        int             stdout_dev;
        int             stdout_unit;
        int             stderr_dev;
        int             stderr_unit;
        char            *stdin_fname;



        char            *stdout_fname;



        char            *stderr_fname;



        char            *tmp_path;



        };
       
typedef struct std_struct       STDSTRUCT;



extern "C" {


extern int         far xinitc            (unsigned int PoolId,
                                               unsigned int Reserved1,
                                               int Reserved2, int Reserved3,
                                               char *TmpPath);
extern int         far xinitt            (int stdin_dev, int stdin_unit,
                                               int stdout_dev, int stdout_unit,
                                               int stderr_dev, int stderr_unit,
                                               char *TmpPath);
extern unsigned  far x_cr_gettaskid    (void);
extern int       far x_cr_gettaskparam (unsigned TaskId,
                                               STDSTRUCT *StdData, char **Env);
extern int       far x_cr_initenv      (char *Env);
extern int         far x_cr_killtsk      (unsigned TaskId);
extern int       far x_cr_setexit      (void ( far *exithandler)(int));


}












 
#line 125 "c:\\rm3dev\\inc\\task.h"


#line 39 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\rmos_inc.h"
#line 1 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\rmos320.h"




















 




#line 55 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\rmos320.h"



#line 40 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\rmos_inc.h"
#line 1 "c:\\rm3dev\\inc\\math.h"





















 









            
            
#pragma fixedparams("acos", "asin", "atan", "atan2", "ceil", "cos", "cosh")
#pragma fixedparams("exp", "x_fabs", "floor", "fmod", "frexp", "ldexp", "log")
#pragma fixedparams("log10", "modf", "pow", "sin", "sinh", "sqrt", "tan")
#pragma fixedparams("tanh","matherr")
 





#line 69 "c:\\rm3dev\\inc\\math.h"

#line 95 "c:\\rm3dev\\inc\\math.h"




#line 105 "c:\\rm3dev\\inc\\math.h"


extern "C" {


extern double  far acos   (double);
extern double  far asin   (double);
extern double  far atan   (double);
extern double  far atan2  (double, double);
extern double  far ceil   (double);
extern double  far cos    (double);
extern double  far cosh   (double);
extern double  far exp    (double);
extern double  far x_fabs   (double);
extern double  far floor  (double);
extern double  far fmod   (double, double);
extern double  far frexp  (double, int *);
extern double  far ldexp  (double, int);
extern double  far log    (double);
extern double  far log10  (double);
extern double  far modf   (double, double *);
extern double  far pow    (double, double);
extern double  far sin    (double);
extern double  far sinh   (double);
extern double  far sqrt   (double);
extern double  far tan    (double);
extern double  far tanh   (double);


}



 

            
#pragma noalign(mathexception)

struct mathexception {
  int type;
  char *name;
  double arg1, arg2, retval;
};
int  matherr(struct mathexception *);  



 
 
 
 
   
#line 206 "c:\\rm3dev\\inc\\math.h"


#line 41 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\rmos_inc.h"
#line 1 "c:\\rm3dev\\inc\\rio.h"

























 










static const
char idstr_rio_h [] =
{
        "\0"    "(C) SIEMENS AG 1995"   "\0"     
        "\1"    "RIO.H"                 "\1"
        "\2"    "0009"                  "\2"
        "\3"    "P.F."                  "\3"
};





 



    

#pragma noalign (byt_parm_struct)















 




 



 
struct byt_parm_struct
{
    char            *string;     



    unsigned int    strlen;      
    char            *buffer;     



    unsigned int    timlen;      
    unsigned int    status;      
};
typedef struct byt_parm_struct  RmBytParmStruct;
    






 

#line 121 "c:\\rm3dev\\inc\\rio.h"

 

#line 139 "c:\\rm3dev\\inc\\rio.h"



 

    


 





 

#line 162 "c:\\rm3dev\\inc\\rio.h"

 

#line 172 "c:\\rm3dev\\inc\\rio.h"



 





 

#line 196 "c:\\rm3dev\\inc\\rio.h"

 

#line 212 "c:\\rm3dev\\inc\\rio.h"



 

    


 




          
 

#line 236 "c:\\rm3dev\\inc\\rio.h"

 

#line 247 "c:\\rm3dev\\inc\\rio.h"



 

    


 






 

#line 279 "c:\\rm3dev\\inc\\rio.h"

 

#line 297 "c:\\rm3dev\\inc\\rio.h"



 

    


 





 

#line 322 "c:\\rm3dev\\inc\\rio.h"

 

#line 334 "c:\\rm3dev\\inc\\rio.h"









#line 42 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\rmos_inc.h"
#line 1 "c:\\rm3dev\\inc\\rmnames.h"





















 




 
 
 

 
#line 43 "c:\\rm3dev\\inc\\rmnames.h"

 


 


                                     

 


                                     

 





 
#line 76 "c:\\rm3dev\\inc\\rmnames.h"

 




 






 


                                   



#line 43 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\rmos_inc.h"
#line 1 "c:\\rm3dev\\inc\\com201.h"



























 




   

#line 1 "c:\\rm3dev\\inc\\typedefs.h"























 









typedef unsigned char   BYTE;
typedef unsigned short  WORD16;
typedef unsigned int    WORD;
typedef unsigned long   WORD32;

typedef void far *     POINTER;         
typedef unsigned int    OFFSET;
typedef unsigned short  SEGMENT;


typedef void *          PTR_VOID;





#line 40 "c:\\rm3dev\\inc\\com201.h"


   


                       
    #pragma fixedparams("Com201Start", "Com201Stop")
    #pragma fixedparams("Dp12IsaStart", "Dp12IsaStop")










   

  typedef enum {
    ComNoErrLog=0,             
    ComErrLog
  } ComErrLogFmt;
  
  typedef enum {
    ComDPSModeRepeat=0,
    ComDPSModeBuffered
  } ComDPSModeFmt;
  
  typedef enum {
    ComOk=0,                    
    ComErrDriver,               
    ComErrReStart,               
    ComErrReStop,                
    ComErrUnit,                 
    ComErrCfg,                  
    ComErrParam,                
    ComErrL2Reset,              
    ComErrL2ResetNoConf,        
    ComErrL2FillBpb,            
    ComErrL2MemInit,            
    ComErrL2MemAlloc,           
    ComErrInitCbfSrv,           
    ComErrDataBase,             
    ComErrStationMode,          
    ComErrDPMInit,              
    ComErrDPMInitAck,           
    ComErrBoardId,              
    ComErrDAMInit,              
    ComErrPAMInit,              
    ComErrHardware,             
    ComErrPtrs,                 
    ComErrFillSlcb,             
    ComErrSetMaMo,              
    ComErrSetMaMoAck,           
    ComErrAddSlv,               
    ComErrWithdrawSlv,          
    ComErrDPMClose,             
    ComErrDPSInit,              
    ComErrDPSMemAlloc,          
    ComErrDPSInBuf,             
    ComErrDPSDiaBuf,            
    ComErrFatal                 
  } ComEcodeFmt;

   

  ComEcodeFmt  far Com201Start(unsigned       Unit,  
                                      void far     *pDataBase,
                                      unsigned long  LenDataBase,
                                      ComDPSModeFmt  DPSMode,
                                      ComErrLogFmt   ErrLog);

  ComEcodeFmt  far Com201Stop (unsigned       Unit);

  ComEcodeFmt  far Dp12IsaStart(unsigned       Unit,       
                                       void far     *pDataBase,
                                       unsigned long  LenDataBase,
                                       ComDPSModeFmt  DPSMode,
                                       ComErrLogFmt   ErrLog);
  ComEcodeFmt  far Dp12IsaStop (unsigned Unit);

   









#line 45 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\rmos_inc.h"
#line 1 "c:\\rm3dev\\inc\\dpn_user.h"




























 




   

#line 42 "c:\\rm3dev\\inc\\dpn_user.h"

   


                       
    #pragma fixedparams("dpn_init", "dpn_read_cfg", "dpn_slv_diag")
    #pragma fixedparams("dpn_read_sys_info", "dpn_out_slv", "dpn_in_slv")
    #pragma fixedparams("dpn_read_slv", "dpn_reset", "dpn_signal")
    #pragma fixedparams("dpn_wd", "dpn_read_bus_par", "dpn_load_bus_par")
    #pragma fixedparams("dpn_read_slv_par", "dpn_set_slv_state")
    #pragma fixedparams("dpn_out_slv_m", "dpn_in_slv_m")
    #pragma fixedparams("dpn_set_mode", "dpn_get_mode", "dpn_global_ctrl")
    #pragma fixedparams("dpn_slv_out_diag", "dpn_slv_wd_state")

    #pragma align(REFERENCE=1)
    #pragma align(dpn_interface=1)
    #pragma align(dpn_interface_s=1)
    #pragma align(dpn_interface_m=1)
    #pragma align(dpn_buspar=1)










   

#line 82 "c:\\rm3dev\\inc\\dpn_user.h"

  struct REFERENCE {
    BYTE board_select; 
    BYTE access;
  };

  struct dpn_interface {
    struct REFERENCE reference;
    BYTE             stat_nr;
    BYTE             length;
    WORD16           error_code;
    BYTE             slv_state;
    BYTE             sys_state;
    BYTE             sys_event;
    BYTE             user_data[255];
  };

  struct dpn_interface_s {                        
    struct REFERENCE reference;
    BYTE             stat_nr;
    BYTE             length;
    WORD16           error_code;
    BYTE             slv_state;
    BYTE             sys_state;
    BYTE             sys_event;
    BYTE             user_data[32];
  };

  struct dpn_interface_m {
    struct dpn_interface_s dpn_if_single[32];
  };

   

  






 











   

  struct dpn_buspar {
    WORD16 Reserved;
    BYTE   FdlAdd;
    BYTE   baudrate;
    WORD16 Tsl;
    WORD16 MinTsdr;
    WORD16 MaxTsdr;
    BYTE   Tqui;
    BYTE   Tset;
    WORD32 Ttr;
    BYTE   G;
    BYTE   Hsa;
    BYTE   MaxRetryLimit;
    BYTE   BpFlag; 
    WORD16 MinSlaveInterval;
    WORD16 PollTimeout;
    WORD16 DataControlTime;   
  };

   

#line 165 "c:\\rm3dev\\inc\\dpn_user.h"

   




   

#line 181 "c:\\rm3dev\\inc\\dpn_user.h"

   






   

#line 197 "c:\\rm3dev\\inc\\dpn_user.h"

   





   










   





   




   
  






   

  WORD16  far dpn_init          (struct dpn_interface far *);
  WORD16  far dpn_read_cfg      (struct dpn_interface far *);
  WORD16  far dpn_slv_diag      (struct dpn_interface far *);
  WORD16  far dpn_read_sys_info (struct dpn_interface far *);
  WORD16  far dpn_out_slv       (struct dpn_interface far *);
  WORD16  far dpn_in_slv        (struct dpn_interface far *);
  WORD16  far dpn_read_slv      (struct dpn_interface far *);
  WORD16  far dpn_reset         (struct dpn_interface far *);

  WORD16  far dpn_signal        (struct dpn_interface far *);

   

  WORD16  far dpn_wd            (struct dpn_interface far *);
  WORD16  far dpn_read_bus_par  (struct dpn_interface far *);
  WORD16  far dpn_load_bus_par  (struct dpn_interface far *);
  WORD16  far dpn_read_slv_par  (struct dpn_interface far *);
  WORD16  far dpn_set_slv_state (struct dpn_interface far *);
  WORD16  far dpn_out_slv_m     (struct dpn_interface_m far *);
  WORD16  far dpn_in_slv_m      (struct dpn_interface_m far *);
  WORD16  far dpn_set_mode      (struct dpn_interface far *);
  WORD16  far dpn_get_mode      (struct dpn_interface far *);
  WORD16  far dpn_global_ctrl   (struct dpn_interface far *);

   

  WORD16  far dpn_slv_out_diag  (struct dpn_interface far *);
  WORD16  far dpn_slv_wd_state  (struct dpn_interface far *);

   

  


 

#line 295 "c:\\rm3dev\\inc\\dpn_user.h"

   









#line 46 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\rmos_inc.h"



#line 25 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\source\\rwth_logger.cpp"

 
#line 1 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\rwth_logger.hpp"













 




 
 




#line 1 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\raw_t_pool.hpp"

















 




 
#line 1 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\puff_cnc_s.hpp"



#line 1 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\uftcncs.hpp"



   struct Def_APW_Halbe_Form
   {
      double DaWP;
      double diWP;
      double hWP_m;
      double sWP_a;
      double sWP_i;
      double hWP_a;
      double hWP_i;
      double alpha_Profil_a_bo;
      double alpha_Profil_i_bo;
      double dhWP_a;
      double dhWP_i;
      double ddh_m;
      double dx_Schraege_Profil_a;
      double dx_Schraege_Profil_i;
      double sWP_ges;
      double dx_Breite_Profil_max;
      double dx_Breite_Profil_min;
      double dxWP_vor_iu; 
      double dxWP_nach_au;
      double dyWP_vor_iu; 
      double dyWP_nach_au;
      double d_Fliessscheide;
      double d_WP_Profil_i;
      double d_WP_Profil_a;
   };




	struct Def_Form
	{
      float da;                              
      float dm;                              
      float di;                              
      float sm;                              
      float hm;                              
                                             
      float gewicht;                         

      double dFSWP;                          
      
      struct Def_APW_Halbe_Form Halbe_Form_o;
      struct Def_APW_Halbe_Form Halbe_Form_u;
	};



#line 5 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\puff_cnc_s.hpp"
#line 1 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\raw_t_cnc_s.hpp"







   









   


   





   




   
#line 40 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\raw_t_cnc_s.hpp"
 





   
#line 53 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\raw_t_cnc_s.hpp"















   



   




   













   struct Def_R_Form
   {  
      float s;
      float h;
      float ra;
      float ri;
      float rm;
   };




   struct Def_Maschine_Motor
   {
      
      float p_nenn;                 
      float i_nenn;                 
      float eta_p;                  
      float n_nenn;                 
      float n_max;                  
      float n_regelreserve_p;       
      float ueberlastung_p;         
      float getriebe_untersetzung;  
      
      int   n_vari_flag;            

      
      float m_nenn;                 
      float m_eff;                  
      float m_max;                  
   };                

   
   struct Def_axi_Achse
   { 
      
      float p_system_hoch;             
      float p_system_nenn;             
      float d_kolben;                  
      float d_kolbenstange;            
      float f_regelreserve_p;          
      float f_max_manu;                
      float f_kommi_hoch;              
      float f_kommi_nenn;              

      
      float anteil_bis_fa_nenn_proz;   
      float anteil_bis_fa_hoch_proz;   
      float f_reduz_vorne_proz;        

      
      float dis_grund_bis_lagerung; 
                                    
      float durchmesser_welle;      
      float sigma_b_max_zul_welle;  

      int   fa_max_begrenzung_neu_flag;
      int   f_max_manu_flag;           
      int   hoch_druck_flag;           

      
      float a_kolben;                  
      float a_ring;                    
      float f_max_nutz_hoch;           
      float f_max_nutz_nenn;           
   };


   
   struct Def_rad_Achse
   { 
      
      float p_system_hoch;               
      float p_system_nenn;               
      float d_kolben_o;                  
      float d_kolben_u;                  
      float d_kolbenstange_o;            
      float d_kolbenstange_u;            
      float f_regelreserve_p;            
      float f_max_manu;                  
      float f_kommi_hoch;                
      float f_kommi_nenn;                
      float kraftniveau_ueber_BE;        
      float kraftniveau_unter_BE;        
      float l_dw_unter_BE;               
      float l_dw_ueber_BE;               
      
                                         
      float l_max_dw_ueber_BE;           
      float l_min_dw_ueber_BE;           
      
      int   f_max_manu_flag;            
      int   hoch_druck_flag;            
      int   zwei_radialschlitten_flag;   
      int   ws_dw_einspannung;         

      
      float a_kolben_o;                  
      float a_kolben_u;                  
      float a_ring_o;                  
      float a_ring_u;                  
      float f_max_nutz_hoch;            
      float f_max_nutz_hoch_o;         
      float f_max_nutz_hoch_u;         
      float f_max_nutz_nenn;            
      float f_max_nutz_nenn_o;         
      float f_max_nutz_nenn_u;         
      float l_dw_gesamt;               
   };

   struct Def_Maschine_Achse
   { 
      
      float p_system;                  
      float d_kolben;                  
      float d_kolbenstange;            
      float f_regelreserve_p;            
      float f_nenn_gesetzt;            
      
      int   f_max_nutz_manu_flag;      

      
      float a_kolben;                  
      float a_ring;                     
      float f_max_system;               
      float f_max_nutz;                  
   };

   
   
   
   struct Def_Walzprodukt
   {
      float s1r_o;
      float s1r_u;
      float ra_1r_o;
      float ra_1r_u;   
      float dra_1r_ou;
      float ri_1r_o;
      float ri_1r_u;
      float s1a_o;                              
      float s1a_u;                              
      float dra_1a_ou;
      float ra_1a_o;
      float ra_1a_u;
      float ri_1a_o;  
      float ri_1a_u;
   };

   
   
   
   struct Def_dPos_Dorn_oben
   {
      float rwg_rad_soll_o;         
      float rwg_rad_soll_u;         
      float d_rwg_ou_korr;          

      float deltas_soll_o;          
      float deltas_soll_u;          
      float d_deltas_ou_soll;       

      float dalpha_dreh_ou_soll_bo; 
      float winkel_dw_soll_bo;      
      float winkel_dw_ist_bo;       

      float d_pos_rso_soll_0;         
      float d_pos_rso_soll;         
      float d_pos_rso_ist;          

      float dis_drehpunkte_dw_vert; 

      float v_hw_mw;                
      float v_rso_soll;               
      float t_korr;                 
   };




   struct Def_fumo
   {
      float u;   
      float m;   
      float o;   
   };




   struct Def_fumomw
   {
      float u;   
      float m;   
      float o;   
      float mw;  
   };




   struct Def_Mess_Ebene
   {
      
      float y_pos_Laser_u;

      
      float y_pos_Laser_o;

      
      float du_HW_Laser_u;

      
      float du_DW_Laser_u;
   };




   struct Def_WP_Mess_Ebene
   {
      
      float pos_Laser_osp_u;

      
      float pos_Laser_osp_o;

      
      float pos_AG_osp;
   };




   struct Def_h_3Segm
   {
      int    segment_nr;
      struct Def_fumo h_Segm_umo;
      struct Def_fumo h_Segm_fak_umo;
   };




   struct   Def_querschnitte_TWST
   {
      float h_m_bei_s_ist;
      float s_m_bei_h_ist;
   
      float h_l_bei_s_ist;
      float s_l_bei_h_ist;
   
      float h_r_bei_s_ist;
      float s_r_bei_h_ist;

      float h_l_bei_s_m;
      float h_r_bei_s_m;
   };




   struct Def_Form_Mess
   {
      float da;            
      float dm;            
      float di;            
      float dis_hw_dw;     
      float dis_aw;        

      double dFSWP;        
      struct Def_APW_Halbe_Form Halbe_Form_o;      
      struct Def_APW_Halbe_Form Halbe_Form_u;      
   };




   struct Def_Dim_EKV   
   {
      float du_ekv;  
      float da_ekv;  
      float dm_ekv;  
      float di_ekv;  
      float h_ekv;   
      float s_ekv;   
   };




   struct Def_Walzen_Geo
   {
      
      int glatt_flag;   
      
      float d_nenn;     
      float d_min;      
      float h_ges;      
      float h_kaliber;  
      float t_kaliber;  
      float h_lippe;    
      float t_lippe;    
      float d_lager;    

      
      float du_max_profil;
      float du_max_gesamt;
#line 410 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\raw_t_cnc_s.hpp"
   
      
      float r_nenn;        
      float r_min;         
      float r_lager;       
   };




   struct Def_AW_Geo
   {
      
      float delta_w_konstr_gr;      
      float l_fehlende_spitze;      
      float l_nutz;                 
                                    
      float l_zyl_ansatz;           
      float winkel_gr;              

      
      float delta_w_konstr_bo;      
      float du_grund;               
      float du_spitze;              
      float l_mantel_theo;          
      float winkel_bo;              


      float achsenlaenge;                    
      float achsenlaenge_l_fehlende_spitze;  
      float achsenlaenge_l_nutz;             





   };




   struct Def_Schlupf
   {
      float b_weg_ag;      
      float dis_sl;         
      float pos_laser_osp; 
      float pos_laser_msp; 
   };




   struct   Def_Walzphase
   {
      int   aw_kontakt_flag;
      int   aw_teil_ueberdeckt_flag;
      int   aw_voll_ueberdeckt_flag;
      int   aw_vorformhoehe_erreicht_flag;
      int   aw_auto_gelueftet_flag;
      int   aw_manu_gelueftet_flag;
      int   aw_gelueftet_flag;
      int   ekv_erreicht_flag;
      int   fh_erreicht_flag;
      int   fa_erkannt_flag;      
      int   fr_erkannt_flag;
      int   hw_motor_hochgelaufen_flag;
      int   schlupfwalzen_flag;
      int   sw_erreicht_flag;
      int   um_ekv_10proz_flag;
      int   um_ekv_33proz_flag;



   };




   struct   Def_Ufz_Rad
   {
      float adr;
      float br;
      float cr;
      float delta_s;
      float dhr_mw;        
      float dhr_max;       
      float epsilon_s;
      float eqr;
      float eta_rad;       
      float h0r;
      float h1r;
      float hmr;
      float phi_s;         
      float phi_qr;        
      float s0r;
      float s1r;
      float smr;
                                 
      float ha_verh;             
      float hebelarm;            

      float ds_hw_dw;            
      float ds_dw_mw;            
      float ds_hw_mw;            
      float du_dw_fiktiv;        
      float du_hw_fiktiv;        
      float du_dw_hw_fiktiv_verh;
      float lr_mw;               
      float ld_dw;               
      float ld_hw;               
      float rr_mw;               
      float verh_lhw_ldw;        
   };




   struct   Def_Ufz_Axi
   {
      float ada;           
      float ba;            
      float ca;            
      float delta_h;       
      float dsa_mw;        
      float dsa_max;       
      float epsilon_h;     
      float eqa;           
      float h0a;           
      float h1a;           
      float sam;           
      float la_mw;         
      float phi_h;         
      float phi_qa;        
      float s0a;           
      float s1a;           

                           
      float ha_verh;       
      float hebelarm;      
   };




   struct   Def_lueften_as
   {
      float deltad_lf;
      float dh_lf;
      float du_lf;
   };




   struct   Def_du_HW_DW_3Segm
   {
      struct   Def_fumomw du_HW_werte;
      struct   Def_fumomw du_DW_werte;

      float    dr_HW_ou;
      float    dr_HW_mu;
      float    dr_DW_ou;
      float    dr_DW_mu;
   };




   struct   Def_kw_fr_fa_mr_ma
   {
      float kw_fa;
      float kw_fr;
      float kw_ma;
      float kw_mr;
   };




   struct Def_Radien_Axial
   {
      
      float ram_o;               
      float raa_o;                                                                        
      float rai_o;                                                                        
      float rawa_o;               
      float rawi_o;               
      float s_aw_kontakt_o;      
      float s_aw_kontakt_hori_o;   
      float kontaktmitte_o; 

      
      float ram_u;               
      float raa_u;                                                                        
      float rai_u;                                                                        
      float rawa_u;               
      float rawi_u;               
      float s_aw_kontakt_u;      
      float s_aw_kontakt_hori_u;   
      float kontaktmitte_u;   
   };




   struct   Def_Iterstop
   {                   
      float genau_eps_abs;
      float genau_eps_rel;
      float genau_rwg_abs;
      float genau_rwg_rel;

      int   iter_abnahme_max;
      int   iter_rwg_max;
   };




   struct   Def_Verlagerung
   {
		float alpha_dm_bo;
		float alpha_hw_mp_bo; 
		float dDa_Messfehler;
		float dv_rel_verl_mm_pro_s_summe;
		float dv_rel_verl_prozess_mm_pro_s;
		float soll;
   };




   struct   Def_Walzphase_Onli
   {
      int   startphase_flag;
      int   hauptphase_flag;
      int   endphase_flag;
      int   aufweiten_ende_flag;

      int   limit_delh;
      int   limit_dels;
      int   limit_fm_max_axial_flag;
      int   limit_fm_max_radial_flag;
      int   limit_rwg_flag;
   };




   struct   Def_ds_dh_sp_hp
   {
      float dh_zustellung;
      float ds_zustellung;
      float h_punkt;
      float s_punkt;
   };




   struct Def_Endphase
   {
      float delta_du;
      float dm;
      float du_ref;

      float delta_du_original;
      float dm_original;
      float du_ref_original;
   };




   struct   Def_iter_anpass
   {
      int prozess_am_limit;
      int fmmax_deltah;
      int fmmax_deltas;
      int rwgmax_deltah;
      int rwgmax_deltas;
      int start_end_deltah;
      int start_end_deltas;
   };




   struct Def_Leistung_max
   {
      float fa_max;   
      float fr_max;   
      float ma_max;   
      float ma_nenn;  
      float mr_max;   
      float mr_nenn;  
   };




   struct Def_rwg_ds_dh_ufz
   {
      float  deltah_Fmax;
      float  deltah_Mmax;
      float  deltah_DZB;
      float  delta_h_fm_max;
      float  delta_h_fm_max_wst;
      float  dh_wst_bei_ds_fm_max;

      float  deltas_Fmax;
      float  deltas_Mmax;
      float  deltas_DZB;
      float  delta_s_fm_max;
      float  delta_s_fm_max_wst;
      float  ds_wst_bei_dh_fm_max;

      float  fakq0_of;
      float  fakq0_mf;
      float  fakq_out;
      float  fakq_out_kontrolle;

      float  rwg_axi;
      float  rwg_eta;
      float  rwg_fm_max;
      float  rwg_start_endphase;
      float  rwg_ges;
      float  rwg_rad;
      float  rwg_soll_aktu;

      struct Def_Ufz_Axi ufz_axi;
      struct Def_Ufz_Rad ufz_rad;
   };




   struct Def_Fr_Fa_Mr_Ma
   {
      float fa_durch_fa_max;
      float fa_max;
      float fa_walz;
      float fr_durch_fr_max;
      float fr_max;
      float fr_walz;

      float ma_durch_ma_max;
      float ma_max;
      float ma_walz;
      float mr_durch_mr_max;
      float mr_max;
      float mr_walz;
   };




   struct Def_n_omega
   {
      float n_aw_motor_g_o;   
      float n_aw_motor_g_u;   
      float n_hw_motor;       
      float n_wp_r;           

      float omega_aw_g_o;     
      float omega_aw_g_u;     
      float omega_hw;         
      float omega_wp_rad;     
      float omega_wp_axi;     

      float v_hw_dv0;
      float v_wp_dv0_hw; 
      float v_aw_dv0_u;
      float v_wp_dv0_aw_u;
      float v_aw_dv0_o;
      float v_wp_dv0_aw_o;

      float r_wp_dv0_hw;      

      float tu;               
   };




   struct Def_tu_d_dd_nru
   {
      float tu;
      float durchmesser;
      float delta_durchmesser;
      float rwg_mw;
   };




   struct Def_dmp
   {
      float axi;   
      float rad;   
      float ges;   
   };

   struct Def_Fehler
   {
#line 827 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\raw_t_cnc_s.hpp"
      unsigned long cpp_t_m;
      unsigned long uft_t; 
      unsigned long uft_m; 
      unsigned long raw_t1;
      unsigned long raw_t2;
      unsigned long raw_t3;
      unsigned long puff1;
      unsigned long puff2;
      unsigned long onli1;
      unsigned long onli2;

   }; 




   struct Def_Ibf_nominal
   {
      
      int   RS_act;         
      int   RS_mode;        

      float Soll_RS_Pos;    
      
      float Soll_FR;        
     
      
      int   AS_act;         
      int   AS_mode;        

      float Soll_AS_Pos;    
      
      float Soll_FA;        

      
      int   Zen_act;        
      int   Zen_mode;       

      float Soll_ZA_Pos;    
      float Soll_ZE_Pos;    
      float Soll_ZA_V;      
      float Soll_ZE_V;      
      float Soll_FZ;        

      float Verlag_ZA;      
      float Verlag_ZE;      
      float Verlag_angle;   

      
      int   AG_act;         
      int   AG_mode;        

      float Soll_AG_Pos;    
      float Soll_AG_V;      
      float Soll_FAG;       
   };




   struct Def_Ibf_actual
   {
      float Ist_ZEN_A;      
      float Ist_ZEN_E;      
      float Ist_AG;         

      float Ibf_Achse1;     
      float Ibf_Achse2;     
      float Ibf_Achse3;     
      float Ibf_Achse4;     
   };


#line 6 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\puff_cnc_s.hpp"
#line 1 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\apwcncs.hpp"



#line 1 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\ctmcncs.hpp"






	struct Def_fxyz
	{
		float x;
		float y;
		float z;
	};

	struct Def_dxyz
	{
		double x;
		double y;
		double z;
	};

        struct Def_ixy
	{
	        int   x;
		int   y;
	};


	
	
	
	struct Def_Kontur_Volumen
	{
		double volumen_gesamt;
		double volumen_oben;
		double volumen_unten;
	};
   



#line 5 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\apwcncs.hpp"






















   struct Def_APW_MIA
   {
      double i;
      double m;
      double a;
   };

   struct Def_APW_INT_MIA
   {
      int i;
      int m;
      int a;
   };

   struct Def_APW_OUMIA
   {
      double o_i;
      double o_m;
      double o_a;
      double u_i;
      double u_m;
      double u_a;
   };

   struct Def_APW_INT_OUMIA
   {
      int o_i;
      int o_m;
      int o_a;
      int u_i;
      int u_m;
      int u_a;
   };

   struct Def_APW_Iter_werte
   {
      double iter;
      double dds_sWP_ges;
      double dds_sWP_i;
      double dds_sWP_a;
      double dif_Vol_WP;
      double dif_Vol_WPi;
      double dif_Vol_WPa;
   };

   struct Def_APW_dif_Da_di_h
   {
      double da;
      double di;
      double hm;
   };

   struct Def_dh_luft_ou
   {
      struct Def_APW_OUMIA     dh_luft_AW; 
      struct Def_APW_MIA       dh_luft_ges;
      struct Def_APW_INT_MIA   Merker_Vollkontakt;
      struct Def_APW_INT_OUMIA Merker_Kontakt;
      int    du_FS_nimmt_zu;
   };

   struct Def_AW_Geo_profiliert
   {
      double dx_Ecke_Profil_max_innen;     
      double dx_Ecke_Profil_max_aussen;    

      double dx_Ecke_Profil_min_innen;     
      double dx_Ecke_Profil_min_aussen;    

      double dx_Breite_Profil_max;
      double dx_Breite_Profil_min;     
      double alpha_Schraege_innen_bo;
      double alpha_Schraege_aussen_bo;
      double dy_Profil_innen;
      double dy_Profil_aussen;
      double dx_Schraege_innen;        
      double dx_Schraege_aussen;       
      double dy_BE_P;
      double l_fehl_spitze;            
      double l_fehl_spitze_bis_awp;    
      double l_mantel_theo;            
      struct Def_APW_MIA dy_AW_Kante;  

      double du_grund;                 
      double du_spitze;                

      double l_zyl_ansatz;           
      double achsenlaenge;           

      int    Mit_Begr_flag;

      double dx_Breite_s_aussen;
      double dy_ueberhang_aussen;
      double alpha_Begr_aussen;
   };

   struct Def_Abgeleitete_Abmessungen
   {
      double hWPo_i;
      double hWPo_m;
      double hWPo_a;
      double sWP_ges;
      double hWPu_i;
      double hWPu_m;
      double hWPu_a;
      double sWPu_i;
      double sWPu_a;
      double sWPo_i;
      double sWPo_a;
      double dhWPo_i;
      double dhWPo_a;
      double dhWPu_i;
      double dhWPu_a;
   };

   struct Def_d_WP_ref_ou
   {
      double d_Fliessscheide_oben;
      double d_Fliessscheide_unten;

      struct Def_APW_OUMIA d_WP_ref;
   };

   struct Def_Da_di_WP
   {
      double Da_WPo;
      double Da_WPu;
      double di_WPo;
      double di_WPu;
   };

   struct Def_Vol_WP
   {
      double Vol_WP;
      double Vol_WP_i;
      double Vol_WP_a;

      double Vol_WP_oi;
      double Vol_WP_ui;
      double Vol_WP_oa;
      double Vol_WP_ua;
   };

   struct Def_Halber_Querschnitt_CNC
   {
      double Teil_vol_WP_Kontur_i[5-2];
      double Teil_vol_WP_Kontur_a[5-2];
      double Ges_vol_WP_Kontur_i;
      double Ges_vol_WP_Kontur_a;
      double Ges_vol_WP_Kontur;
      struct Def_dxyz Fliessscheide;
   };

   struct Def_Querschnitt_CNC
   {
      struct Def_Halber_Querschnitt_CNC WPo_werte;
      struct Def_Halber_Querschnitt_CNC WPu_werte;
      struct Def_Abgeleitete_Abmessungen Abgeleitete_Abmessungen;
      double y_pos_Unterkante;
      struct Def_Vol_WP Vol_WP;
      struct Def_Form Form;
      struct Def_Form Form_MW_Vol;
   };

  struct Def_Walzform_real_Iter
   {
      double   dh_ges_dVol;
      double   ds_ges_W;
      double   ds_sWPa_W;
      double   ds_sWPi_W;
      double   ddh_ges_dVol;
      double   dds_sWPa_W;
      double   dds_sWPi_W;
      double   dh_zu_ds_dVol_iter;
      int      iter;
   };

   struct Def_Walzform_real_dif_Vol_werte
   {
      double   dif_dVol_vergleich;
      double   dif_Vol_WP_W;
      double   dif_Vol_WPi_W;
      double   dif_Vol_WPa_W;
   };

   struct Def_Simu_Messwerte
   {
      double pos_Laser_pseudo_mS;
      double x_pos_AW_Spitze;
      double pos_DR_Achsen_mS;
      double WP_Da;
      double WP_Ra;
      double xWP_Achse;
   };

   struct Def_Zwischenform_Iter
   {
      int      iter_Z;

      double   dds_sWPi_Z;
      double   dds_sWPa_Z;

      double   dif_Vol_WPi_Z;
      double   dif_Vol_WPa_Z;

      double   dif_Vol_WPi_Z_rel;
      double   dif_Vol_WPa_Z_rel;

      double   dds_sWPo_i_Z;
      double   dds_sWPo_a_Z;
      double   dds_sWPu_i_Z;
      double   dds_sWPu_a_Z;

      double   dif_Vol_WPo_i_Z;
      double   dif_Vol_WPo_a_Z;
      double   dif_Vol_WPu_i_Z;
      double   dif_Vol_WPu_a_Z;

      double   dif_Vol_WPo_i_Z_rel;
      double   dif_Vol_WPo_a_Z_rel;
      double   dif_Vol_WPu_i_Z_rel;
      double   dif_Vol_WPu_a_Z_rel;

      double   ddh_hWPo_i_Z;
      double   ddh_hWPu_i_Z;
      double   ddh_hWPo_a_Z;
      double   ddh_hWPu_a_Z;

      struct   Def_APW_OUMIA   delh_werte_Z;
      struct   Def_APW_OUMIA   dels_werte_Z;

      int      Vollkontakt_axial_flag;
      int      Form_Iterieren_flag;
      int      Form_Iterieren_i_flag;
      int      Form_Iterieren_a_flag;

      int      Merker_Vollkontakt_i_Z;
      int      Merker_Kontakt_o_i_Z;   
      int      Merker_Kontakt_u_i_Z; 

      int      Merker_Vollkontakt_a_Z; 
      int      Merker_Kontakt_o_a_Z;   
      int      Merker_Kontakt_u_a_Z;     

      double   hWP_m_Vollkontakt_i_Z;
      double   hWP_m_Vollkontakt_a_Z;
   };

   struct Def_iterwerte_Z
   {
   









 

      struct Def_Zwischenform_Iter zwischenform_iter;
      struct Def_dh_luft_ou dh_luft_ou;
      double hWP_m_Z;
   };

   struct Def_dhzuds_Set
   {
      struct Def_APW_MIA Ohne_Kontakt;
      struct Def_APW_MIA Teilkontakt;
   };

   struct Def_Input_DR
   {
      double Da_WP;

      
      double dis_x_AW_Sp_theo_bis_Ref_AG;
      double dis_y_WW_Achse_bis_Ref_AG;
      double durchm_DR;
      double x_AW_Spitze_theo;
      double alpha_DR_zur_WW_Achse;
      struct Def_dxyz xy_mp_WP;
      double dis_messanschlag_bis_SP_Achsen;
   };

   struct Def_sWPoa_APS_Soll_Konstanten
   {
      double h_Radius_Start;
      double L_Sehne;
      double dis_Sehne;
      double Radius;
      double Winkel_Sehne;
      struct Def_dxyz xyMP_Sehne;
      double Drehrichtung;
      struct Def_dxyz xyMP_Radius;
   };

#line 7 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\puff_cnc_s.hpp"





































   









   
   
   
   struct Def_Ein_Puff
   {
      
      int      abschalt_modus;                  
      int      endphase_flag;                   
      int      walzenstart_flag;                
      int      sw_zuerst_fertig_flag;           
      int      taster_aw_manu_gelueftet_flag;   
      int      ws_d_lauf_flag;                  
      int      walz_modus;                      
      int      stuetzstellen_anwenden_flag;
      int      volumenberechnung_flag;          
      int      msg_flag;                        
      int      cnc_flag;                        
      int      kw_testbetrieb_flag;             
      int      test_walzen_ohne_ring_flag;
      int      aufwalzen_bis_ekv_flag;
      int      mit_breitung_flag;
      int      power_taster_flag;               
      int      keine_verteilung_hoehe_neg_voldiff_flag; 
      int      aw_ueberdeckung_check_flag;
      int      aps_1_walzung_flag;              
      int      rpt_1_walzung_flag;              
      int      rpt_2_walzung_flag;              
      
      
      float    dt_zyklus;                       
      float    zeit_walzen;                     
      float    n_hw_motor_soll;                 
      float    n_hw_motor_soll_0;               
      float    n_hw_motor_ist;                  
      float    n_awo_motor_ist;                 
      float    n_awu_motor_ist;                 
      float    v_gl_fak_hw_p;
      float    v_gl_fak_axi_p;
      float    d_hw_dv0_carwin;                 

      
      float    dv_Grundvertrim_ou_p;            

      
      float    t1_glaettung_vor_pos_laser_aw_n0;
      float    t1_glaettung_zurueck_pos_laser_aw_n0;

      
      struct   Def_Form_Mess   form_mess_of;    
      struct   Def_Form_Mess   form_mess_start; 
      struct   Def_Form_Mess   form_mess_mw_vol_of; 
      float    da_id;
      float    pos_laser_u_of;                  
      float    pos_laser_id;

      
      struct   Def_Mess_Ebene mess_ebene;       

      
      struct   Def_Form vorform;                
      struct   Def_Form soll_walzform;          

      
      float    fa_of;                           
      float    fr_of;                           
      float    fag_of;                          

      float    fa_kommi_nenn;                   
      float    fr_kommi_nenn;                   

      float    fr_erkannt_p;                    
      float    fa_erkannt_p;                    

      
      float    p_system_a_of;                   
      float    p_system_r_of;                   

      
      float    hw1_i_of;                        
      float    hw2_i_of;                        
      float    awo_i_of;                        
      float    awu_i_of;                        

      
      struct   Def_kw_fr_fa_mr_ma kw_fr_fa_mr_ma_test;   

      
      struct   Def_Walzen_Geo hw_geometrie;     
      struct   Def_Walzen_Geo dw_geometrie;     
      struct   Def_AW_Geo     awo_geometrie;    
      struct   Def_AW_Geo     awu_geometrie;    

      struct   Def_Schlupf    schlupf_u;        

      float    deltad_ekv;                      
      float    deltad_lf_nach_ekv;              
      float    lueftmass_auto_as;               

      
      float    volvertverha;                    

      
      struct   Def_Maschine_Motor hw1_motor;    
      struct   Def_Maschine_Motor hw2_motor;    
      struct   Def_Maschine_Motor awo_motor;    
      struct   Def_Maschine_Motor awu_motor;    

      
      float    delta_durchmesser_nru;
      float    tu_nru;




         long     nummer;


      
      int      Dorn_Messung_flag;                 

      struct   Def_Walzen_Geo dr_geometrie;       
      double   disy_dr_achsen_halbe;              

      struct   Def_AW_Geo_profiliert awo_geo_profiliert;
      struct   Def_AW_Geo_profiliert awu_geo_profiliert;

      double   y_be_basis;

      struct   Def_APW_dif_Da_di_h   dif_Vorform;  
      int      dif_Vorform_merker;                 

      double   y_awu_kante_mitte_aps;
      double   y_awu_kante_innen_aps;
      double   y_awu_kante_aussen_aps;
      double   y_awu_kante_max_aps;
      double   y_awu_kante_min_aps;

      struct   Def_APW_OUMIA   dy_awou_p;

      struct   Def_APW_OUMIA   dhWP_VS;

      struct   Def_dhzuds_Set dhzuds_set;

      
      struct   Def_Vol_WP              vorform_Vol_WP;
      struct   Def_APW_Iter_werte      vorform_Iter_VS;
      struct   Def_dh_luft_ou          vorform_dh_luft_ou;

      
      struct   Def_Form                ist_vorform;
      struct   Def_Vol_WP              ist_vorform_Vol_WP;
      struct   Def_dh_luft_ou          ist_vorform_dh_luft_ou;
      
      
      struct   Def_Vol_WP              form_mess_of_Vol_WP;
      struct   Def_dh_luft_ou          form_mess_of_dh_luft_ou;
      struct   Def_Zwischenform_Iter   form_mess_of_Iter_Z;     
      double   y_Bezug_Z_of;

      
      struct   Def_dh_luft_ou          soll_walzform_dh_luft_ou;
      struct   Def_Vol_WP              soll_walzform_Vol_WP;

      

      double   du_FS_Pos_faktor_oben;
      double   du_FS_Pos_faktor_oben_min;
      double   du_FS_Pos_faktor_oben_max;
      double   ds_dh_iterfaktor;

      int      du_FS_nimmt_zu_mit_zwei_VK;

      struct Def_APW_MIA h_Walzspalte_WS;
      struct Def_APW_MIA h_Walzspalte_VS;
      struct Def_APW_MIA h_Walzspalte_V;
      struct Def_APW_MIA h_Walzspalte_Z_of;
   };




   struct Def_Aus_Puff
   {
      float    pos_rs_achse;       
      float    pos_rs_achse_start; 
      float    pos_wp_achse;       
      float    pos_wp_achse_start; 

      
      struct   Def_Walzphase   walzphase;       

      
      struct   Def_Form         ist_walzform;        
      struct   Def_Form         form_ring;           
      struct   Def_Form_Mess    form_mess_mf;        
      double   y_Bezug_Z_mf;
      struct   Def_Form_Mess    form_mess_mw_vol_mf; 
      float    vorform_hoehe_variabel;               
      int      di_vorhanden_flag;                    

      struct   Def_Ufz_Rad      ufz_rad_mf;     
      struct   Def_Ufz_Axi      ufz_axi_mf;     

      float    pos_laser_u_mf;                  
      float    pos_laser_mit_spitze_u_mf;       
      float    pos_laser_mit_spitze_u_of;       
      float    pos_laser_mit_spitze_u_mf_start; 

      float    h0r;                             
      float    h1r;                             
      float    h0a;                             
      float    h1a;                             

      float    s0r;                             
      float    s1r;                             
      float    s0a;                             
      float    s1a;                             

      float    h_ekv;                           
      float    s_ekv;                           

      struct   Def_Walzprodukt wp;

      float    wp_pos_ra_1a_ms_hori_u;
      float    wp_aw_n_pos_ra_1a_ms_hori_u;

      
      struct   Def_lueften_as   lueften_as;

      
      
      float    s_Luft_Kal_DW_o;
      float    s_Luft_Kal_DW_u;

      float    s_Luft_Kal_HW_o;
      float    s_Luft_Kal_HW_u;

      
      float    delta_h_mf;                      
      float    delta_s_mf;                      

      
      float    dpa_mf;                          
      float    dpi_mf;                          
      float    dpm_mf;                          

      
      float    dpm_of;                          

      float    v1r_mw;
      float    v1a_mw;

      
      float    pos_laser_aw_n_mit_spitze_u_mf;
      struct   Def_n_omega            n_omega;

      float    hw_r_dv0_wp;                     
      float    wp_r_dv0_hw;
      float    aw_r_dv0_u;
      float    aw_r_dv0_o;
      float    wp_r_dv0_aw_u;
      float    wp_r_dv0_aw_o;

      
      struct   Def_du_HW_DW_3Segm   du_hw_dw_3segm;
      struct   Def_h_3Segm          h_3segm;

      
      struct   Def_kw_fr_fa_mr_ma kw_fr_fa_mr_ma_mf; 

      
      struct   Def_Radien_Axial   radien_axial;

      float    dvol_ring_proz;                  
      float    vol_ring_mf;                     
      float    vol_ring_mf_anzeige;             
      float    symmetrie_faktor;                

      
      float    fr_mf;                           
      float    fa_mf;                           

      
      float    mr_nenn_gesamt; 
      float    ma_nenn_gesamt;
      float    mr_mf;                           
      float    ma_mf;                           

      
      float    p_system_a_mf;                   
      float    p_system_r_mf;                   

      
      int      mit_breitung_rad_flag;           
      int      mit_breitung_axi_flag;           





      int      istanz_ru;                       

      








 
      struct   Def_Vol_WP              form_mess_mf_Vol_WP;
      struct   Def_Zwischenform_Iter   form_mess_mf_Iter_Z;     
      struct   Def_dh_luft_ou          form_mess_mf_dh_luft_ou;

      struct   Def_Vol_WP              ist_walzform_Vol_WP;
      struct   Def_Walzform_real_Iter  ist_walzform_Iter_W;
      struct   Def_dh_luft_ou          ist_walzform_dh_luft_ou;

      double   dpos_AG_Start_Vopt;

      double   ram_dv0_APS_o;
      double   ram_APS_o;

      double   ram_dv0_APS_u;
      double   ram_APS_u;

      double    test1;
      double    test2;
      double    test3;
      double    test4;
      double    test5;

      double    pos_Laser_Soll_mS;
      double    sWPoa_Soll;
      double   y_awo_basis_hinten;

      struct Def_APW_MIA h_Walzspalte_Z_mf;
   };




   struct Def_Lokal_Puff
   {
      
      float    fr_min;                          
      float    fr_of_kw;                        

      float    fa_min;                          
      float    fa_of_kw;                        

      float    fag_mf;                          


      
      float    mr_of;                           
      float    mr_min;                          
      float    mr_of_kw;                        

      float    ma_of;                           
      float    ma_min;                          
      float    ma_of_kw;                        

      
      float      da_old;                        
      float      dm_old;                        
      float      di_old;                        
      
      float      h1a0;                          
      float      s1r0;                          
      float      d_fertig;                      
      float      vol_ref;                       

      
      float      hw_strom_mf;                   
      float      aw_strom_mf;                   

      
      float      zeit_anwalzen;                 
      float      tu;                            

      
      float      dpa_of;                        
      float      dpm_of;                        
      float      dpi_of;                        
      
      
      float      delta_s_of;                    
      float      delta_h_of;                    

      
      float      deltahr0;
      float      deltasa0;
      float      deltahr_hilf;
      float      deltasa_hilf;

      
      struct   Def_kw_fr_fa_mr_ma kw_fr_fa_mr_ma_of;      

      float      kwa_ver;                       
      float      kwr_ver;                       

      float      kw_min;                        
      float      kw_max;                        

      
      unsigned   char it0;                      
      signed     char its;                      

      float      q_ru;                          
      float      q_ruh;                         

      float      tim_rh0;
      float      tim_rh1;
      float      tim_r0;
      float      tim_r1;

      float      trr;                           
      float      trrh;                          
      float      umf;                           
      float      umf_sum;                       
                                                
      float      umfh;                          

      float      umf_r0;
      float      umf_r1;
      float      umf_rh0;
      float      umf_rh1;
                                                
      float      deltahr_val[50];             
      float      deltasa_val[50];             
      float      h1a_val[50];                 
      float      s1r_val[50];                 
      float      tim_val[50];                 
      float      umf_val[50];                 

      int        i_pu;
      int        int_ip;
      int        istanz_ru_old;                 
   };



#line 27 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\raw_t_pool.hpp"
#line 1 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\onli_cnc_s.hpp"























   struct Def_Ein_Onli
   {






      
      
      float    s_aufweiten_proz;               
      float    kurv_faktor_aufweiten;          

      
      float    s_masse_verteilt_proz;          
      float    dh_masse_verteilt;              
      float    kurv_faktor_masse_verteilt;     

      
      float    kurv_faktor_walzen;             

      
      float    kurv_faktor_twst;               
      float    faecherbreite_min_proz;          
      float    faecherbreite_max_proz;
      float    anteil_breitung_wegwalzen_proz;

      
      int      kurv_uebertragen_flag;
      int      stuetz_anz;
      float    h_stuetz[50];
      float    s_stuetz[50];

      
      float    rwg_max;				
      float    rwg_min_endphase;		
      float    rwg_aufweiten;			
      float    rwg_poti_wert;			
      float    rwg_regelgrenze;			
      float    rwg_aps_bis_vk;                  

      float    deltad_rundier;                  

      float    d_du_pro_1_mm_rwg;					
      float    exponent_rwg_endphase;
      float    korrektur_deltad_endphase;       
      float    korrektur_endphase_poti_wert;	
      float    rwg_hochfahren_start;
      float    zeit_momente_hochfahren;
      int      aufwalzung_check_flag;

      int      endphase_delta_du_manu_flag;  
      float    endphase_delta_du_manu;       

      
      float    da_walz_max;			
      float    h_walz_max;			
      struct   Def_rad_Achse rs_achse;		
      struct   Def_axi_Achse as_achse;		

		
      int      fr_max_dornwalze_manu_flag;      
      int      fr_max_dornwalze_grenze_flag;    
      float    fr_max_dornwalze_manu;           
      float    fr_max_dornwalze_grenze;         
      float    dw_sigma_zul;                    
      float    dw_sigma_verh;

      
      float    dis_min_ag_dw;
      float    d_dw_pseudo_kolli_ag_dwlager;
      float    pos_rs_achse_min;                
		
      
      int      ws_agmodus;
      float    b_weg_ag_sl;
      float    ag_flex_move_exponent;
      float    dposag_start_vs;                 
      float    dposag_ende_vs;                  


      
      int      river_auto_flag;
      float    handrad_korrektur_river_auto;

      
      int      river_manu_flag;
      float    alpha_verl_manu_gr;

      
      float    rz_achse_hebelverh;
      float    rz_kf_Wert_bezug;

      float    rz_f_kommi_nenn;

      float    rz_f_zul_handrad_korrektur;
      float    rz_f_zul_t1_glaettung_d;
      float    rz_f_zul_t1_glaettung_handrad_klein;
      float    rz_f_zul_t1_glaettung_handrad_gross;


      int      rz_f_lueften_axial_flag;
      int      rz_f_start_flag;
      int      rz_f_radial_5proz_erkannt;
      int      rz_f_radial_vorform_erreicht;
      int      rz_f_walzen_radial_u_axial;
      int      rz_f_betriebsart;
      int      rz_f_manu_flag;
      int      rz_f_IB_Walzen_radial_u_axial;



      
      float    rz_f_manu_soll;            
      float    rz_f_max;                  
      float    rz_fz_eilgang;             
      float    rz_f_ist_zen_einl;         
      float    rz_f_ist_zen_ausl;         
#line 149 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\onli_cnc_s.hpp"

      
      struct	Def_Iterstop  iterstop;

      
      double    WT_dis_WP_Beladen; 
      double    WT_dis_WP_Entladen; 
      double    WT_Einlaufseite_dis_WP_Walzen; 
      double    WT_Auslaufseite_dis_WP_Walzen; 

      
      double    dis_x_AW_Sp_theo_bis_AG_Achse_ref_AS;
      double    dis_x_AW_Sp_theo_bis_AG_Achse_ref_ES;

      double    alpha_ZR_zur_WW_Achse_gr_AS;
      double    alpha_ZR_zur_WW_Achse_gr_ES;

      double    dis_y_WW_Achse_bis_AG_Achse_ref_AS;
      double    dis_y_WW_Achse_bis_AG_Achse_ref_ES;

      double    dis_messanschlag_bis_SP_Achsen_AS;
      double    dis_messanschlag_bis_SP_Achsen_ES;

      double    dr_poti_wert;

      
      double    fr_max_dornwalze_fliegend;       
      double    dw_d_lager;                      


      int       AG_Faehrt_Zum_Messzyklus_flag;   
                                                 
                                                 
                                                 
                                                 

      Def_Ibf_actual    Ibf_actual;
    };




	struct Def_Aus_Onli
	{
      
      struct   Def_Fehler fehler;

      
		int		walzspalt_kopplung_flag;

      
      int      index_stuetz_ziel;
      float    h_ziel;
      float    s_ziel;

		
		struct	Def_ds_dh_sp_hp		ds_dh_sp_hp;

		
		float		s_punkt_min;			
		float		h_punkt_min;

		
		struct	Def_Endphase			         endphase;
		
		
		struct	Def_Leistung_max		         nutz_leistungsgrenzen;

		float		fr_max_hydraulik;

#line 225 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\onli_cnc_s.hpp"

		float    pos_ag_soll;
		float    dpos_ag_soll;

		float		fr_max_dornwalze;

		float		fa_max_hydraulik;





		float		fa_max_axialwalze;

		
		struct	Def_Fr_Fa_Mr_Ma		fr_fa_mr_ma;

      
      float    red_fak_fr_of;
      float    red_fak_fa_of;
      float    red_fak_mr_of;
      float    red_fak_ma_of;
      float    red_fak_r_of; 
      float    red_fak_a_of; 
      float    red_fak_r_mf; 
      float    red_fak_a_mf; 

		
		struct	Def_Walzphase_Onli   walzphase_onli;

		
		float		du_ref_mess_nru;
      float		du_ref_ring_nru;
		struct	Def_rwg_ds_dh_ufz		rwg_ds_dh_ufz_anpass_nru;
		struct	Def_Form_Mess			form_mess_nru;
      struct   Def_Form				   form_ring_nru;
   	struct   Def_Radien_Axial		radien_axial_nru;

      
      float    rwg_poti_wert_endphase_start;

      
      float    rwg_max_zul;
      float    rwg_max_zul_korr;    

		
		struct	Def_Verlagerung		verlagerung_auto;

		
		struct	Def_Verlagerung		verlagerung_manu;

		






		
		struct	Def_tu_d_dd_nru		tu_d_dd_nru;

		
		struct	Def_iter_anpass		iter_anpass;

      
      int      abwalzen_bis_masse_verteilt_flag;    
      int      aufwalzen_bis_ekv_flag;
		float		h_aufweiten_ende;             
		float		s_aufweiten_ende;             

		float		h_masse_verteilt;             
		float		s_masse_verteilt;             

      
      float    h_twst_start_m;
      float    s_twst_start_m;
      float    s_start_rechts;
      float    h_start_rechts;
      float    s_start_links;
      float    h_start_links;
      float    faecherbreite_max;
      float    faecherbreite_min;

      int      modus_fakq_twst_flag;
      int      radial_walzen_flag;
      int      twst_gestartet_mkr;

      struct   Def_querschnitte_TWST qs_twst;

      float    za_f_zyl_zulaessig_einzeln;
      float    za_f_zyl_zulaessig_summe;
      float    za_f_ring_zulaessig;
      float    za_f_zyl_max_nutz;
      float    za_f_fz_zyl_ist_mw_mf;			 
      float    za_f_fz_zyl_diff_mf;				 
      float    za_f_zr_da_kraft_korrektur;
	   float	   za_f_zyl_zulaessig_auto_manu;	 



      long     Zaehler_check;



      int      phase;


      
      double   WT_Beladen_soll_pos;             
      double   WT_Entladen_soll_pos;            
      double   WT_Einlaufseite_Walzen_soll_pos; 
      double   WT_Auslaufseite_Walzen_soll_pos; 

      struct   Def_dxyz dr_auslauf_mp_no_korr;
      struct   Def_dxyz dr_einlauf_mp_no_korr;

      struct   Def_dxyz dr_auslauf_mp;
      struct   Def_dxyz dr_einlauf_mp;

      double   dr_auslauf_pos_zyl_no_korr;
      double   dr_einlauf_pos_zyl_no_korr;

      double   dr_pos_zyl_korr;

      double   dr_auslauf_pos_zyl;
      double   dr_einlauf_pos_zyl;

      double   diff_vol_wp_i;

      double   Frad_APS;



      
      struct   Def_Ibf_nominal Ibf_nominal;



      double    test1;
      double    test2;
      double    test3;
      double    test4;
      double    test5;
	};



#line 28 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\raw_t_pool.hpp"






#line 41 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\raw_t_pool.hpp"


    
    struct LOG_CHANNEL_DEF
    {
    	





 
        int    type;                        
                                            
                                            
                                            
                                            
                                            

        


 
        double faktor;                      
                                            
                                            
                                            
                                            

        
 
        void * pAdresse;                    
                                            
    };


    struct TeDat4_type
    {
    	
 
       char     Teststring[4][80];          
       
 
       long     TeDa[4][10];                
    }; 


    struct RwwtPool_tag
    {
    	
 
       int  Status_TRT;
       
 
       int  Steuer_TRT;
       
 
       int  Status_RWTH;
       
 
       int  Steuer_RWTH;

       
 
       int  Data_available;
       
 
       int  Data_availableRWTH;

       
 
       int  Data_initialed;


       
 
       LOG_CHANNEL_DEF        *pLTableRWTH; 

       TeDat4_type            *pTeDat;      

       struct Def_Ein_Puff    ein_puff;
       struct Def_Ein_Puff    ein_puff_back;
       struct Def_Ein_Puff    ein_puff_RWTH;
       struct Def_Aus_Puff    aus_puff;
       struct Def_Aus_Puff    aus_puff_RWTH;
       struct Def_Ein_Onli    ein_onli;
       struct Def_Ein_Onli    ein_onli_back;
       struct Def_Ein_Onli    ein_onli_RWTH;
       struct Def_Aus_Onli    aus_onli;
       struct Def_Aus_Onli    aus_onli_RWTH;
       struct Def_Lokal_Puff  lokal_puff;
    };




        extern RwwtPool_tag *RwwtPool;


    const char far Powercon_SendSema[] = "Power_SendSema";
    const char far Powercon_RecSema[] = "Power_RecSema";
    const char far Mailboxl[] = "TRT_MAILBOX";


#line 26 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\rwth_logger.hpp"



class   LOGGER_RWTH
{
    public:
        LOGGER_RWTH(void);
        ~LOGGER_RWTH(){;}
        int Kanalliste(void);

        LOG_CHANNEL_DEF * getLogPointer(void){return(&TableLogRWTH[0]);}

    private:
        LOG_CHANNEL_DEF TableLogRWTH[300];     
};
#line 28 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\source\\rwth_logger.cpp"
#line 1 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\rwth_task.hpp"













 




 




   




                                        
                                        

#line 1 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\rwth_exch.hpp"














 




 


void svc_sts (unsigned int index, char *svc_txt, int status);



class	RWTH_EXCH
{
	public:
		RWTH_EXCH(void);
		~RWTH_EXCH();
		int put_puff(void);
		int get_puff(void);
		int Main_Control(void);
		int running_flag;
		int finish_flag;

        TeDat4_type     TeDat;

        uint * get_pCountBlinker(void){return(&CountBlinker);} 
        uint * get_pBlinker(void){return(&Blinker);}           

	protected:
		uint Sema_PowerSendID;
		uint Sema_PowerRecID;
		uint TRT_Mail_id;
		int	 Status;
		RmMailboxStruct TRT_Mail;
		RmEntryStruct   Entry;

        uint  CountBlinker;
        uint  Blinker;
    
};

#line 36 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\rwth_task.hpp"
#line 1 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\rpw.hpp"















 




 




 
#line 1 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\iniFile.h"



#line 1 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\rpw.hpp"















 




 
#line 763 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\rpw.hpp"




#line 5 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\iniFile.h"
#line 1 "c:\\rm3dev\\incplus\\string"
 



















  





#pragma noarguments_in_registers(push)



		
inline string operator+(const string& __L, const string& _R)
	{return (string(__L) += _R); }
inline string operator+(const char *__L, const string& _R)
	{return (string(__L) += _R); }
inline string operator+(const char __L, const string& _R)
	{return (string(1, __L) += _R); }
inline string operator+(const string& __L, const char *_R)
	{return (string(__L) += _R); }
inline string operator+(const string& __L, const char _R)
	{return (string(__L) += _R); }
inline bool operator==(const string& __L, const string& _R)
	{return (__L.compare(_R) == 0); }
inline bool operator==(const char * __L, const string& _R)
	{return (_R.compare(__L) == 0); }
inline bool operator==(const string& __L, const char *_R)
	{return (__L.compare(_R) == 0); }
inline bool operator!=(const string& __L, const string& _R)
	{return (!(__L == _R)); }
inline bool operator!=(const char *__L, const string& _R)
	{return (!(__L == _R)); }
inline bool operator!=(const string& __L, const char *_R)
	{return (!(__L == _R)); }
inline bool operator<(const string& __L, const string& _R)
	{return (__L.compare(_R) < 0); }
inline bool operator<(const char * __L, const string& _R)
	{return (_R.compare(__L) > 0); }
inline bool operator<(const string& __L, const char *_R)
	{return (__L.compare(_R) < 0); }
inline bool operator>(const string& __L, const string& _R)
	{return (_R < __L); }
inline bool operator>(const char * __L, const string& _R)
	{return (_R < __L); }
inline bool operator>(const string& __L, const char *_R)
	{return (_R < __L); }
inline bool operator<=(const string& __L, const string& _R)
	{return (!(_R < __L)); }
inline bool operator<=(const char * __L, const string& _R)
	{return (!(_R < __L)); }
inline bool operator<=(const string& __L, const char *_R)
	{return (!(_R < __L)); }
inline bool operator>=(const string& __L, const string& _R)
	{return (!(__L < _R)); }
inline bool operator>=(const char * __L, const string& _R)
	{return (!(__L < _R)); }
inline bool operator>=(const string& __L, const char *_R)
	{return (!(__L < _R)); }
		
inline istream& operator>>(istream& _I, string& __X)
	{typedef char_traits _Tr;
	typedef char_allocator _A;
	typedef ctype _Ctype;
	typedef istream _Myis;
	typedef string _Mystr;
	ios_base::iostate _St = ios_base::goodbit;
	bool _Chg = false;
	__X.erase();
	const _Myis::sentry _Ok(_I);
	if (_Ok)
		{const _Ctype& _Fac = _Ctype();
		try {
		_Mystr::size_type __N = 0 < _I.width()
			&& _I.width() < __X.max_size()
				? _I.width() : __X.max_size();
		_Tr::int_type __C = _I.rdbuf()->sgetc();
		for (; 0 < --__N; __C = _I.rdbuf()->snextc())
			if(_Tr::eq_int_type(_Tr::eof(), __C))
				{_St |= ios_base::eofbit;
				break; }
			else if (_Fac.is(_Ctype::space,
				_Tr::to_char_type(__C)))
				break;
			else
				{__X.append(1, _Tr::to_char_type(__C));
				_Chg = true; }
		} catch (...) { (_I). setstate(ios_base::badbit, true); }; }
	_I.width(0);
	if (!_Chg)
		_St |= ios_base::failbit;
	_I.setstate(_St);
	return (_I); }
inline istream& getline(istream& _I, string& __X,
	const char _D = '\n')
	{typedef char_traits _Tr;
	typedef istream _Myis;
	ios_base::iostate _St = ios_base::goodbit;
	bool _Chg = false;
	__X.erase();
	const _Myis::sentry _Ok(_I, true);
	if (_Ok)
		{try {
		_Tr::int_type __C = _I.rdbuf()->sgetc();
		for (; ; __C = _I.rdbuf()->snextc())
			if (_Tr::eq_int_type(_Tr::eof(), __C))
				{_St |= ios_base::eofbit;
				break; }
			else if (_Tr::eq(__C, _D))
				{_Chg = true;
				_I.rdbuf()->snextc();
				break; }
			else if (__X.max_size() <= __X.size())
				{_St |= ios_base::failbit;
				break; }
			else
				__X += _Tr::to_char_type(__C), _Chg = true;
		} catch (...) { (_I). setstate(ios_base::badbit, true); }; }
	if (!_Chg)
		_St |= ios_base::failbit;
	_I.setstate(_St);
	return (_I); }
inline ostream& operator<<(ostream& _O, const string& __X)
	{typedef char_traits _Tr;
	typedef char_allocator _A;
	typedef ostream _Myos;
	typedef string _Mystr;
	ios_base::iostate _St = ios_base::goodbit;
	_Mystr::size_type __N = __X.size();
	_Mystr::size_type _M =
		_O.width() <= 0 || _O.width() <= __N
			? 0 : _O.width() - __N;
	const _Myos::sentry _Ok(_O);
	if (!_Ok)
		_St |= ios_base::badbit;
	else
		{try {
		if ((_O.flags() & ios_base::adjustfield)
			!= ios_base::left)
			for (; 0 < _M; --_M)
				if (_Tr::eq_int_type(_Tr::eof(),
					_O.rdbuf()->sputc(_O.fill())))
					{_St |= ios_base::badbit;
					break; }
		if (_St == ios_base::goodbit)
			for (_Mystr::size_type _I = 0;
				_I < __N; ++_I)
				if (_Tr::eq_int_type(_Tr::eof(),
					_O.rdbuf()->sputc(__X[_I])))
					{_St |= ios_base::badbit;
					break; }
		if (_St == ios_base::goodbit)
			for (; 0 < _M; --_M)
				if (_Tr::eq_int_type(_Tr::eof(),
					_O.rdbuf()->sputc(_O.fill())))
					{_St |= ios_base::badbit;
					break; }
		_O.width(0);
		} catch (...) { (_O). setstate(ios_base::badbit, true); } }
	_O.setstate(_St);
	return (_O); }


#pragma arguments_in_registers(pop)






 
#line 6 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\iniFile.h"
#line 1 "c:\\rm3dev\\incplus\\vector"
 



















  






#line 1 "c:\\rm3dev\\incplus\\iterator"
 



















  






#line 1 "c:\\rm3dev\\incplus\\xutility"
 



















  






#line 1 "c:\\rm3dev\\incplus\\utility"
 



















  








		
template<class _T1, class _T2> struct pair {
	typedef _T1 first_type;
	typedef _T2 second_type;
	pair()
		: first(_T1()), second(_T2()) {}
	pair(const _T1& _V1, const _T2& _V2)
		: first(_V1), second(_V2) {}
	template<class _U1, class _U2>
		pair(const pair<_U1, _U2>& __X)
		: first(__X.first), second(__X.second) {}
	_T1 first;
	_T2 second;
	};
template<class _T1, class _T2> inline
	bool operator==(const pair<_T1, _T2>& __X,
		const pair<_T1, _T2>& _Y)
	{return (__X.first == _Y.first && __X.second == _Y.second); }
template<class _T1, class _T2> inline
	bool operator!=(const pair<_T1, _T2>& __X,
		const pair<_T1, _T2>& _Y)
	{return (!(__X == _Y)); }
template<class _T1, class _T2> inline
	bool operator<(const pair<_T1, _T2>& __X,
		const pair<_T1, _T2>& _Y)
	{return (__X.first < _Y.first ||
		!(_Y.first < __X.first) && __X.second < _Y.second); }
template<class _T1, class _T2> inline
	bool operator>(const pair<_T1, _T2>& __X,
		const pair<_T1, _T2>& _Y)
	{return (_Y < __X); }
template<class _T1, class _T2> inline
	bool operator<=(const pair<_T1, _T2>& __X,
		const pair<_T1, _T2>& _Y)
	{return (!(_Y < __X)); }
template<class _T1, class _T2> inline
	bool operator>=(const pair<_T1, _T2>& __X,
		const pair<_T1, _T2>& _Y)
	{return (!(__X < _Y)); }
template<class _T1, class _T2> inline
	pair<_T1, _T2> make_pair(const _T1& __X, const _T2& _Y)
	{return (pair<_T1, _T2>(__X, _Y)); }
#line 90 "c:\\rm3dev\\incplus\\utility"








 
















 
#line 29 "c:\\rm3dev\\incplus\\xutility"


		
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag
	: public input_iterator_tag {};
struct bidirectional_iterator_tag
	: public forward_iterator_tag {};
struct random_access_iterator_tag
	: public bidirectional_iterator_tag  {};
struct _Int_iterator_tag {};
		
template<class __C, class _Ty, class _D = ptrdiff_t,
	class _Pt = _Ty *, class _Rt = _Ty&>
	struct iterator {
	typedef __C iterator_category;
	typedef _Ty value_type;
	typedef _D difference_type;
	typedef _Pt pointer;
	typedef _Rt reference;
	};
template<class _Ty, class _D, class _Pt, class _Rt>
	struct _Bidit : public iterator<bidirectional_iterator_tag,
		_Ty, _D, _Pt, _Rt> {};
template<class _Ty, class _D, class _Pt, class _Rt>
	struct _Ranit : public iterator<random_access_iterator_tag,
		_Ty, _D, _Pt, _Rt> {};
struct _Outit : public iterator<output_iterator_tag,
	void, void, void, void> {};
		
template<class _It>
	struct iterator_traits {
	typedef  _It::iterator_category iterator_category;
	typedef  _It::value_type value_type;
	typedef  _It::difference_type difference_type;
	typedef  _It::pointer pointer;
	typedef  _It::reference reference;
	};
		
template<class __C, class _Ty, class _D,
	class _Pt, class _Rt> inline
	__C _Iter_cat(const iterator<__C, _Ty, _D, _Pt, _Rt>&)
	{__C __X;
	return (__X); }
template<class _Ty> inline
	random_access_iterator_tag _Iter_cat(const _Ty *)
	{random_access_iterator_tag __X;
	return (__X); }
		
inline _Int_iterator_tag _Iter_cat(_Bool)
	{_Int_iterator_tag __X;
	return (__X); }
inline _Int_iterator_tag _Iter_cat(char)
	{_Int_iterator_tag __X;
	return (__X); }
inline _Int_iterator_tag _Iter_cat(signed char)
	{_Int_iterator_tag __X;
	return (__X); }
inline _Int_iterator_tag _Iter_cat(unsigned char)
	{_Int_iterator_tag __X;
	return (__X); }
inline _Int_iterator_tag _Iter_cat(wchar_t)
	{_Int_iterator_tag __X;
	return (__X); }
inline _Int_iterator_tag _Iter_cat(short)
	{_Int_iterator_tag __X;
	return (__X); }
inline _Int_iterator_tag _Iter_cat(unsigned short)
	{_Int_iterator_tag __X;
	return (__X); }
inline _Int_iterator_tag _Iter_cat(int)
	{_Int_iterator_tag __X;
	return (__X); }
inline _Int_iterator_tag _Iter_cat(unsigned int)
	{_Int_iterator_tag __X;
	return (__X); }
inline _Int_iterator_tag _Iter_cat(long)
	{_Int_iterator_tag __X;
	return (__X); }
inline _Int_iterator_tag _Iter_cat(unsigned long)
	{_Int_iterator_tag __X;
	return (__X); }
		
template<class _II> inline
	ptrdiff_t distance(_II _F, _II __L)
	{ptrdiff_t __N = 0;
	_Distance2(_F, __L, __N, _Iter_cat(_F));
	return (__N); }
template<class _II, class _D> inline
	void _Distance(_II _F, _II __L, _D& __N)
	{_Distance2(_F, __L, __N, _Iter_cat(_F)); }
template<class _II, class _D> inline
	void _Distance2(_II _F, _II __L, _D& __N,
		input_iterator_tag)
	{for (; _F != __L; ++_F)
		++__N; }
template<class _II, class _D> inline
	void _Distance2(_II _F, _II __L, _D& __N,
		forward_iterator_tag)
	{for (; _F != __L; ++_F)
		++__N; }
template<class _II, class _D> inline
	void _Distance2(_II _F, _II __L, _D& __N,
		bidirectional_iterator_tag)
	{for (; _F != __L; ++_F)
		++__N; }
template<class _RI, class _D> inline
	void _Distance2(_RI _F, _RI __L, _D& __N,
		random_access_iterator_tag)
	{__N += __L - _F; }
		
template<class _Ty, class _D, class _Pt, class _Rt,
	class _Pt2, class _Rt2>
	class _Ptrit : public iterator<random_access_iterator_tag,
		_Ty, _D, _Pt, _Rt> {
public:
	typedef _Ptrit<_Ty, _D, _Pt, _Rt, _Pt2, _Rt2> _Myt;
	_Ptrit()
		{}
	explicit _Ptrit(_Pt __P)
		: current(__P) {}
	_Ptrit(const _Ptrit<_Ty, _D, _Pt2, _Rt2, _Pt2, _Rt2>& __X)
		: current(__X.base()) {}
	_Pt base() const
		{return (current); }
	_Rt operator*() const
		{return (*current); }
	_Myt& operator++()
		{++current;
		return (*this); }
	_Myt operator++(int)
		{_Myt _Tmp = *this;
		++current;
		return (_Tmp); }
	_Myt& operator--()
		{--current;
		return (*this); }
	_Myt operator--(int)
		{_Myt _Tmp = *this;
		--current;
		return (_Tmp); }
	bool operator==(int _Y) const
		{return (current == _Y); }
	bool operator==(const _Myt& _Y) const
		{return (current == _Y.current); }
	bool operator!=(const _Myt& _Y) const
		{return (!(*this == _Y)); }
	_Myt& operator+=(_D __N)
		{current += __N;
		return (*this); }
	_Myt operator+(_D __N) const
		{return (_Myt(current + __N)); }
	_Myt& operator-=(_D __N)
		{current -= __N;
		return (*this); }
	_Myt operator-(_D __N) const
		{return (_Myt(current - __N)); }
	_Rt operator[](_D __N) const
		{return (*(*this + __N)); }
	bool operator<(const _Myt& _Y) const
		{return (current < _Y.current); }
	bool operator>(const _Myt& _Y) const
		{return (_Y < *this); }
	bool operator<=(const _Myt& _Y) const
		{return (!(_Y < *this)); }
	bool operator>=(const _Myt& _Y) const
		{return (!(*this < _Y)); }
	_D operator-(const _Myt& _Y) const
		{return (current - _Y.current); }
protected:
	_Pt current;
	};
template<class _Ty, class _D, class _Pt, class _Rt,
	class _Pt2, class _Rt2> inline
	_Ptrit<_Ty, _D, _Pt, _Rt, _Pt2, _Rt2>
		operator+(_D __N,
			const _Ptrit<_Ty, _D, _Pt, _Rt, _Pt2, _Rt2>& _Y)
	{return (_Y + __N); }
		
template<class _RI>
	class reverse_iterator : public iterator<
		 iterator_traits<_RI>::iterator_category,
		 iterator_traits<_RI>::value_type,
		 iterator_traits<_RI>::difference_type,
		 iterator_traits<_RI>::pointer,
		 iterator_traits<_RI>::reference> {
public:
	typedef reverse_iterator<_RI> _Myt;
	typedef  iterator_traits<_RI>::difference_type _D;
	typedef  iterator_traits<_RI>::pointer _Pt;
	typedef  iterator_traits<_RI>::reference _Rt;
	typedef _RI iterator_type;
	reverse_iterator()
		{}
	explicit reverse_iterator(_RI __X)
		: current(__X) {}
	template<class __U>
		reverse_iterator(const reverse_iterator<__U>& __X)
		: current(__X.base()) {}
	_RI base() const
		{return (current); }
	_Rt operator*() const
		{_RI _Tmp = current;
		return (*--_Tmp); }
	_Myt& operator++()
		{--current;
		return (*this); }
	_Myt operator++(int)
		{_Myt _Tmp = *this;
		--current;
		return (_Tmp); }
	_Myt& operator--()
		{++current;
		return (*this); }
	_Myt operator--(int)
		{_Myt _Tmp = *this;
		++current;
		return (_Tmp); }
	bool _Eq(const _Myt& _Y) const
		{return (current == _Y.current); }
		
	_Myt& operator+=(_D __N)
		{current -= __N;
		return (*this); }
	_Myt operator+(_D __N) const
		{return (_Myt(current - __N)); }
	_Myt& operator-=(_D __N)
		{current += __N;
		return (*this); }
	_Myt operator-(_D __N) const
		{return (_Myt(current + __N)); }
	_Rt operator[](_D __N) const
		{return (*(*this + __N)); }
	bool _Lt(const _Myt& _Y) const
		{return (_Y.current < current); }
	_D _Mi(const _Myt& _Y) const
		{return (_Y.current - current); }
protected:
	_RI current;
	};
template<class _RI, class _D> inline
	reverse_iterator<_RI> operator+(_D __N,
		const reverse_iterator<_RI>& _Y)
	{return (_Y + __N); }
template<class _RI> inline
	reverse_iterator<_RI>::_D
		operator-(const reverse_iterator<_RI>& __X,
		const reverse_iterator<_RI>& _Y)
	{return (__X._Mi(_Y)); }
template<class _RI> inline
	bool operator==(const reverse_iterator<_RI>& __X,
		const reverse_iterator<_RI>& _Y)
	{return (__X._Eq(_Y)); }
template<class _RI> inline
	bool operator!=(const reverse_iterator<_RI>& __X,
		const reverse_iterator<_RI>& _Y)
	{return (!(__X == _Y)); }
template<class _RI> inline
	bool operator<(const reverse_iterator<_RI>& __X,
		const reverse_iterator<_RI>& _Y)
	{return (__X._Lt(_Y)); }
template<class _RI> inline
	bool operator>(const reverse_iterator<_RI>& __X,
		const reverse_iterator<_RI>& _Y)
	{return (_Y < __X); }
template<class _RI> inline
	bool operator<=(const reverse_iterator<_RI>& __X,
		const reverse_iterator<_RI>& _Y)
	{return (!(_Y < __X)); }
template<class _RI> inline
	bool operator>=(const reverse_iterator<_RI>& __X,
		const reverse_iterator<_RI>& _Y)
	{return (!(__X < _Y)); }
		
template<class _E, class _Tr = char_traits>
	class istreambuf_iterator
		: public iterator<input_iterator_tag,
			_E,  _Tr::off_type, _E *, _E&> {
public:
	typedef istreambuf_iterator<_E, _Tr> _Myt;
	typedef char char_type;
	typedef char_traits traits_type;
	typedef streambuf streambuf_type;
	typedef istream istream_type;
	typedef  traits_type::int_type int_type;
	istreambuf_iterator(streambuf_type *_Sb = 0) throw ()
		: _Sbuf(_Sb), _Got(_Sb == 0) {}
	istreambuf_iterator(istream_type& _I) throw ()
		: _Sbuf(_I.rdbuf()), _Got(_I.rdbuf() == 0) {}
	const _E& operator*() const
		{if (!_Got)
			((_Myt *)this)->_Peek();
		return (_Val); }
	_Myt& operator++()
		{_Inc();
		return (*this); }
	_Myt operator++(int)
		{if (!_Got)
			_Peek();
		_Myt _Tmp = *this;
		_Inc();
		return (_Tmp); }
	bool equal(const _Myt& __X) const
		{if (!_Got)
			((_Myt *)this)->_Peek();
		if (!__X._Got)
			((_Myt *)&__X)->_Peek();
		return (_Sbuf == 0 && __X._Sbuf == 0
			|| _Sbuf != 0 && __X._Sbuf != 0); }
private:
	void _Inc()
		{if (_Sbuf == 0
			|| traits_type::eq_int_type(traits_type::eof(),
				_Sbuf->sbumpc()))
			_Sbuf = 0, _Got = true;
		else
			_Got = false; }
	_E _Peek()
		{int_type __C;
		if (_Sbuf == 0
			|| traits_type::eq_int_type(traits_type::eof(),
				__C = _Sbuf->sgetc()))
			_Sbuf = 0;
		else
			_Val = traits_type::to_char_type(__C);
		_Got = true;
		return (_Val); }
	streambuf_type *_Sbuf;
	bool _Got;
	_E _Val;
	};
template<class _E, class _Tr> inline
	bool operator==(const istreambuf_iterator<_E, _Tr>& __X,
		const istreambuf_iterator<_E, _Tr>& _Y)
	{return (__X.equal(_Y)); }
template<class _E, class _Tr> inline
	bool operator!=(const istreambuf_iterator<_E, _Tr>& __X,
		const istreambuf_iterator<_E, _Tr>& _Y)
	{return (!(__X == _Y)); }
		
template<class _E, class _Tr>
	class ostreambuf_iterator
		: public _Outit {
	typedef ostreambuf_iterator<_E, _Tr> _Myt;
public:
	typedef char char_type;
	typedef char_traits traits_type;
	typedef streambuf streambuf_type;
	typedef ostream ostream_type;
	ostreambuf_iterator(streambuf_type *_Sb) throw ()
		: _Failed(false), _Sbuf(_Sb) {}
	ostreambuf_iterator(ostream_type& _O) throw ()
		: _Failed(false), _Sbuf(_O.rdbuf()) {}
	_Myt& operator=(_E __X)
		{if (_Sbuf == 0
			|| traits_type::eq_int_type(_Tr::eof(),
				_Sbuf->sputc(__X)))
			_Failed = true;
		return (*this); }
	_Myt& operator*()
		{return (*this); }
	_Myt& operator++()
		{return (*this); }
	_Myt& operator++(int)
		{return (*this); }
	bool failed() const throw ()
		{return (_Failed); }
private:
	bool _Failed;
	streambuf_type *_Sbuf;
	};


		
template<class _II, class _OI> inline
	_OI copy(_II _F, _II __L, _OI __X)
	{for (; _F != __L; ++__X, ++_F)
		*__X = *_F;
	return (__X); }
		
template<class _BI1, class _BI2> inline
	_BI2 copy_backward(_BI1 _F, _BI1 __L, _BI2 __X)
	{while (_F != __L)
		*--__X = *--__L;
	return (__X); }
		
template<class _II1, class _II2> inline
	bool equal(_II1 _F, _II1 __L, _II2 __X)
	{return (mismatch(_F, __L, __X).first == __L); }
		
template<class _II1, class _II2, class _Pr> inline
	bool equal(_II1 _F, _II1 __L, _II2 __X, _Pr __P)
	{return (mismatch(_F, __L, __X, __P).first == __L); }
		
template<class _FI, class _Ty> inline
	void fill(_FI _F, _FI __L, const _Ty& __X)
	{for (; _F != __L; ++_F)
		*_F = __X; }
		
template<class _OI, class _Sz, class _Ty> inline
	void fill_n(_OI _F, _Sz __N, const _Ty& __X)
	{for (; 0 < __N; --__N, ++_F)
		*_F = __X; }
		
template<class _II1, class _II2> inline
	bool lexicographical_compare(_II1 _F1, _II1 _L1,
		_II2 _F2, _II2 _L2)
	{for (; _F1 != _L1 && _F2 != _L2; ++_F1, ++_F2)
		if (*_F1 < *_F2)
			return (true);
		else if (*_F2 < *_F1)
			return (false);
	return (_F1 == _L1 && _F2 != _L2); }
		
template<class _II1, class _II2, class _Pr> inline
	bool lexicographical_compare(_II1 _F1, _II1 _L1,
		_II2 _F2, _II2 _L2, _Pr __P)
	{for (; _F1 != _L1 && _F2 != _L2; ++_F1, ++_F2)
		if (__P(*_F1, *_F2))
			return (true);
		else if (__P(*_F2, *_F1))
			return (false);
	return (_F1 == _L1 && _F2 != _L2); }
		




template<class _Ty> inline
	const _Ty& (max)(const _Ty& __X, const _Ty& _Y)
	{return (__X < _Y ? _Y : __X); }
		
template<class _Ty, class _Pr> inline
	const _Ty& (max)(const _Ty& __X, const _Ty& _Y, _Pr __P)
	{return (__P(__X, _Y) ? _Y : __X); }
		
template<class _Ty> inline
	const _Ty& (min)(const _Ty& __X, const _Ty& _Y)
	{return (_Y < __X ? _Y : __X); }
		
template<class _Ty, class _Pr> inline
	const _Ty& (min)(const _Ty& __X, const _Ty& _Y, _Pr __P)
	{return (__P(_Y, __X) ? _Y : __X); }
		
template<class _II1, class _II2> inline
	pair<_II1, _II2> mismatch(_II1 _F, _II1 __L, _II2 __X)
	{for (; _F != __L && *_F == *__X; ++_F, ++__X)
		;
	return (pair<_II1, _II2>(_F, __X)); }
		
template<class _II1, class _II2, class _Pr> inline
	pair<_II1, _II2> mismatch(_II1 _F, _II1 __L, _II2 __X, _Pr __P)
	{for (; _F != __L && __P(*_F, *__X); ++_F, ++__X)
		;
	return (pair<_II1, _II2>(_F, __X)); }
		
template<class _Ty> inline
	void swap(_Ty& __X, _Ty& _Y)
	{_Ty _Tmp = __X;
	__X = _Y, _Y = _Tmp; }








 
















 
#line 29 "c:\\rm3dev\\incplus\\iterator"

		
template<class __C>
	class back_insert_iterator
		: public _Outit {
public:
	typedef __C container_type;
	typedef  __C::reference reference;
	typedef  __C::value_type value_type;
	explicit back_insert_iterator(__C& __X)
		: container(&__X) {}
	back_insert_iterator<__C>& operator=(
		 __C::const_reference _V)
		{container->push_back(_V);
		return (*this); }
	back_insert_iterator<__C>& operator*()
		{return (*this); }
	back_insert_iterator<__C>& operator++()
		{return (*this); }
	back_insert_iterator<__C> operator++(int)
		{return (*this); }
protected:
	__C *container;
	};
template<class __C> inline
	back_insert_iterator<__C> back_inserter(__C& __X)
	{return (back_insert_iterator<__C>(__X)); }
		
template<class __C>
	class front_insert_iterator
		: public _Outit {
public:
	typedef __C container_type;
	typedef  __C::reference reference;
	typedef  __C::value_type value_type;
	explicit front_insert_iterator(__C& __X)
		: container(&__X) {}
	front_insert_iterator<__C>& operator=(
		 __C::const_reference _V)
		{container->push_front(_V);
		return (*this); }
	front_insert_iterator<__C>& operator*()
		{return (*this); }
	front_insert_iterator<__C>& operator++()
		{return (*this); }
	front_insert_iterator<__C> operator++(int)
		{return (*this); }
protected:
	__C *container;
	};
template<class __C> inline
	front_insert_iterator<__C> front_inserter(__C& __X)
	{return (front_insert_iterator<__C>(__X)); }
		
template<class __C>
	class insert_iterator
		: public _Outit {
public:
	typedef __C container_type;
	typedef  __C::reference reference;
	typedef  __C::value_type value_type;
	insert_iterator(__C& __X,  __C::iterator _I)
		: container(&__X), iter(_I) {}
	insert_iterator<__C>& operator=(
		 __C::const_reference _V)
		{iter = container->insert(iter, _V);
		++iter;
		return (*this); }
	insert_iterator<__C>& operator*()
		{return (*this); }
	insert_iterator<__C>& operator++()
		{return (*this); }
	insert_iterator<__C>& operator++(int)
		{return (*this); }
protected:
	__C *container;
	 __C::iterator iter;
	};
template<class __C, class _XI> inline
	insert_iterator<__C> inserter(__C& __X, _XI _I)
	{return (insert_iterator<__C>(__X, __C::iterator(_I))); }
		
template<class _Ty, class _E = char,
	class _Tr = char_traits,
	class _Dist = ptrdiff_t>
	class istream_iterator
		: public iterator<input_iterator_tag, _Ty, _Dist,
			_Ty *, _Ty&> {
public:
	typedef istream_iterator<_Ty, _E, _Tr, _Dist> _Myt;
	typedef _E char_type;
	typedef _Tr traits_type;
	typedef istream istream_type;
	istream_iterator()
		: _Istr(0) {}
	istream_iterator(istream_type& _I)
		: _Istr(&_I) {_Getval(); }
	const _Ty& operator*() const
		{return (_Val); }
	_Myt& operator++()
		{_Getval();
		return (*this); }
	_Myt operator++(int)
		{_Myt _Tmp = *this;
		_Getval();
		return (_Tmp); }
	bool _Equal(const _Myt& __X) const
		{return (_Istr == __X._Istr); }
protected:
	void _Getval()
		{if (_Istr != 0 && !(*_Istr >> _Val))
			_Istr = 0; }
	istream_type *_Istr;
	_Ty _Val;
	};
template<class _Ty, class _E, class _Tr, class _Dist> inline
	bool operator==(
		const istream_iterator<_Ty, _E, _Tr, _Dist>& __X,
		const istream_iterator<_Ty, _E, _Tr, _Dist>& _Y)
	{return (__X._Equal(_Y)); }
template<class _Ty, class _E, class _Tr, class _Dist> inline
	bool operator!=(
		const istream_iterator<_Ty, _E, _Tr, _Dist>& __X,
		const istream_iterator<_Ty, _E, _Tr, _Dist>& _Y)
	{return (!(__X == _Y)); }
		
template<class _Ty, class _E = char,
	class _Tr = char_traits >
	class ostream_iterator
		: public _Outit {
public:
	typedef _Ty value_type;
	typedef _E char_type;
	typedef _Tr traits_type;
	typedef ostream ostream_type;
	ostream_iterator(ostream_type& _O,
		const _E *_D = 0)
		: _Ostr(&_O), _Delim(_D) {}
	ostream_iterator<_Ty, _E, _Tr>& operator=(const _Ty& __X)
		{*_Ostr << __X;
		if (_Delim != 0)
			*_Ostr << _Delim;
		return (*this); }
	ostream_iterator<_Ty, _E, _Tr>& operator*()
		{return (*this); }
	ostream_iterator<_Ty, _E, _Tr>& operator++()
		{return (*this); }
	ostream_iterator<_Ty, _E, _Tr> operator++(int)
		{return (*this); }
protected:
	const _E *_Delim;
	ostream_type *_Ostr;
	};
		
template<class __C, class _Ty, class _D,
	class _Pt, class _Rt> inline
	_Ty *_Val_type(const iterator<__C, _Ty, _D, _Pt, _Rt>&)
	{return ((_Ty *)0); }
template<class _Ty> inline
	_Ty *_Val_type(const _Ty *)
	{return ((_Ty *)0); }
		
template<class _II, class _D> inline
	void advance(_II& _I, _D __N)
	{_Advance(_I, __N, _Iter_cat(_I)); }
template<class _II, class _D> inline
	void _Advance(_II& _I, _D __N, input_iterator_tag)
	{for (; 0 < __N; --__N)
		++_I; }
template<class _FI, class _D> inline
	void _Advance(_FI& _I, _D __N, forward_iterator_tag)
	{for (; 0 < __N; --__N)
		++_I; }
template<class _BI, class _D> inline
	void _Advance(_BI& _I, _D __N, bidirectional_iterator_tag)
	{for (; 0 < __N; --__N)
		++_I;
	for (; __N < 0; ++__N)
		--_I; }
template<class _RI, class _D> inline
	void _Advance(_RI& _I, _D __N, random_access_iterator_tag)
	{_I += __N; }
		
template<class __C, class _Ty, class _D,
	class _Pt, class _Rt> inline
	_D *_Dist_type(const iterator<__C, _Ty, _D, _Pt, _Rt>&)
	{return ((_D *)0); }
template<class _Ty> inline
	ptrdiff_t *_Dist_type(const _Ty *)
	{return ((ptrdiff_t *)0); }








 
















 
#line 29 "c:\\rm3dev\\incplus\\vector"
#line 1 "c:\\rm3dev\\incplus\\memory"
 



















  






#line 1 "c:\\rm3dev\\incplus\\xmemory"
 



















  






#line 1 "c:\\rm3dev\\incplus\\new"
 



















  





#pragma noarguments_in_registers(push)




#pragma arguments_in_registers(pop)






 
#line 30 "c:\\rm3dev\\incplus\\xmemory"
#line 44 "c:\\rm3dev\\incplus\\xmemory"

		
template<class _Ty> inline
	_Ty  *_Allocate(size_t __N, _Ty  *)
	{return ((_Ty  *)operator new(__N * sizeof (_Ty))); }
		
template<class _T1, class _T2> inline
	void _Construct(_T1  *__P, const _T2& _V)
	{new ((void  *)__P) _T1(_V); }
		
template<class _Ty> inline
	void _Destroy(_Ty  *__P)
	{(__P)->~_Ty(); }
template<> inline void _Destroy(char  *__P)
	{}
template<> inline void _Destroy(wchar_t  *__P)
	{}
		
template<class _Ty>
	class allocator {
public:
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef _Ty  *pointer;
	typedef const _Ty  *const_pointer;
	typedef _Ty & reference;
	typedef const _Ty & const_reference;
	typedef _Ty value_type;
	pointer address(reference __X) const
		{return (&__X); }
	const_pointer address(const_reference __X) const
		{return (&__X); }
	allocator()
		{}
	allocator(const allocator<_Ty>&)
		{}
	template<class __U>
		allocator(const allocator<__U>&)
		{}
	template<class __U>
		allocator<_Ty>& operator=(const allocator<__U>&)
		{return (*this); }
	template<class __U>
		struct rebind {
			typedef allocator<__U> other;
		};
	template<class __U>
		pointer allocate(size_type __N, const __U *)
		{return (_Allocate(__N, (pointer)0)); }
	pointer allocate(size_type __N)
		{return (_Allocate(__N, (pointer)0)); }
	void deallocate(pointer __P, size_type)
		{operator delete(__P); }
	void construct(pointer __P, const _Ty& _V)
		{_Construct(__P, _V); }
	void destroy(pointer __P)
		{_Destroy(__P); }
	size_t max_size() const
		{size_t __N = (size_t)(-1) / sizeof (_Ty);
		return (0 < __N ? __N : 1); }
	};
template<class _Ty, class __U> inline
	bool operator==(const allocator<_Ty>&, const allocator<__U>&)
	{return (true); }
template<class _Ty, class __U> inline
	bool operator!=(const allocator<_Ty>&, const allocator<__U>&)
	{return (false); }
		
template<> class allocator<void> {
public:
	typedef void _Ty;
	typedef _Ty  *pointer;
	typedef const _Ty  *const_pointer;
	typedef _Ty value_type;
	allocator(const allocator<_Ty>&)
		{}
	template<class __U>
		allocator(const allocator<__U>&)
		{}
	template<class __U>
		allocator<_Ty>& operator=(const allocator<__U>&)
		{return (*this); }
	template<class __U>
		struct rebind {
			typedef allocator<__U> other;
		};
	};








 
















 
#line 29 "c:\\rm3dev\\incplus\\memory"

		
template<class _Ty> inline
	pair<_Ty  *, ptrdiff_t>
		get_temporary_buffer(ptrdiff_t __N, _Ty  *)
	{_Ty  *__P;
	for (__P = 0; 0 < __N; __N /= 2)
		if ((__P = (_Ty  *)operator new(
			(size_t)__N * sizeof (_Ty), nothrow)) != 0)
			break;
	return (pair<_Ty  *, ptrdiff_t>(__P, __N)); }
		
template<class _Ty> inline
	void return_temporary_buffer(_Ty *__P)
	{operator delete(__P); }
		
template<class _II, class _FI> inline
	_FI uninitialized_copy(_II _F, _II __L, _FI __X)
	{for (; _F != __L; ++__X, ++_F)
		_Construct(&*__X, *_F);
	return (__X); }
		
template<class _FI, class _Ty> inline
	void uninitialized_fill(_FI _F, _FI __L, const _Ty& __X)
	{for (; _F != __L; ++_F)
		_Construct(&*_F, __X); }
		
template<class _FI, class __S, class _Ty> inline
	void uninitialized_fill_n(_FI _F, __S __N, const _Ty& __X)
	{for (; 0 < __N; --__N, ++_F)
		_Construct(&*_F, __X); }
		
template<class _OI, class _Ty>
	class raw_storage_iterator
		: public _Outit {
public:
	typedef _OI iter_type;
	typedef _Ty element_type;
	explicit raw_storage_iterator(_OI __X)
		: _Next(__X) {}
	raw_storage_iterator<_OI, _Ty>& operator*()
		{return (*this); }
	raw_storage_iterator<_OI, _Ty>& operator=(const _Ty& __X)
		{_Construct(&*_Next, __X);
		return (*this); }
	raw_storage_iterator<_OI, _Ty>& operator++()
		{++_Next;
		return (*this); }
	raw_storage_iterator<_OI, _Ty> operator++(int)
		{raw_storage_iterator<_OI, _Ty> _Ans = *this;
		++_Next;
		return (_Ans); }
private:
	_OI _Next;
	};
		
template<class _Ty>
	class _Temp_iterator
		: public _Outit {
public:
	typedef _Ty  *_Pty;
	_Temp_iterator(ptrdiff_t __N = 0)
		{pair<_Pty, ptrdiff_t> _Pair =
			get_temporary_buffer(__N, (_Pty)0);
		_Buf._Begin = _Pair.first;
		_Buf._Cur = _Pair.first;
		_Buf._Hiwater = _Pair.first;
		_Buf._Len = _Pair.second;
		_Pb = &_Buf; }
	_Temp_iterator(const _Temp_iterator<_Ty>& __X)
		{_Buf._Begin = 0;
		_Buf._Cur = 0;
		_Buf._Hiwater = 0;
		_Buf._Len = 0;
		*this = __X; }
	~_Temp_iterator()
		{if (_Buf._Begin != 0)
			{for (_Pty _F = _Buf._Begin;
				_F != _Buf._Hiwater; ++_F)
				_Destroy(&*_F);
			return_temporary_buffer(_Buf._Begin); }}
	_Temp_iterator<_Ty>& operator=(const _Temp_iterator<_Ty>& __X)
		{_Pb = __X._Pb;
		return (*this); }
	_Temp_iterator<_Ty>& operator=(const _Ty& _V)
		{if (_Pb->_Cur < _Pb->_Hiwater)
			*_Pb->_Cur++ = _V;
		else
			{_Construct(&*_Pb->_Cur, _V);
			_Pb->_Hiwater = ++_Pb->_Cur; }
		return (*this); }
	_Temp_iterator<_Ty>& operator*()
		{return (*this); }
	_Temp_iterator<_Ty>& operator++()
		{return (*this); }
	_Temp_iterator<_Ty>& operator++(int)
		{return (*this); }
	_Temp_iterator<_Ty>& _Init()
		{_Pb->_Cur = _Pb->_Begin;
		return (*this); }
	_Pty _First() const
		{return (_Pb->_Begin); }
	_Pty _Last() const
		{return (_Pb->_Cur); }
	ptrdiff_t _Maxlen() const
		{return (_Pb->_Len); }
private:
	struct _Bufpar {
		_Pty _Begin;
		_Pty _Cur;
		_Pty _Hiwater;
		ptrdiff_t _Len;
		} _Buf, *_Pb;
	};
		
template<class _Ty>
	class auto_ptr {
			
	template<class __U>
		struct auto_ptr_ref {
		auto_ptr_ref(auto_ptr<__U>& _Y)
			: _Ref(_Y) {}
		auto_ptr<__U>& _Ref;
		};
public:
	typedef _Ty element_type;
	explicit auto_ptr(_Ty *__P = 0) throw ()
		: _Ptr(__P) {}
	auto_ptr(auto_ptr<_Ty>& _Y) throw ()
		: _Ptr(_Y.release()) {}
	auto_ptr(auto_ptr_ref<_Ty> _Y) throw ()
		: _Ptr(_Y._Ref.release()) {}
	template<class __U>
		auto_ptr(auto_ptr<__U>& _Y) throw ()
		: _Ptr(_Y.release()) {}
	template<class __U>
		operator auto_ptr<__U>() throw ()
		{return (auto_ptr<__U>(*this)); }
	template<class __U>
		operator auto_ptr_ref<__U>() throw ()
		{return (auto_ptr_ref<__U>(*this)); }
	template<class __U>
		auto_ptr<_Ty>& operator=(auto_ptr<__U>& _Y) throw ()
		{reset(_Y.release());
		return (*this); }
	auto_ptr<_Ty>& operator=(auto_ptr<_Ty>& _Y) throw ()
		{reset(_Y.release());
		return (*this); }
	~auto_ptr()
		{delete _Ptr; }
	_Ty& operator*() const throw ()
		{return (*get()); }
	_Ty *operator->() const throw ()
		{return (get()); }
	_Ty *get() const throw ()
		{return (_Ptr); }
	_Ty *release() throw ()
		{_Ty *_Tmp = _Ptr;
		_Ptr = 0;
		return (_Tmp); }
	void reset(_Ty* __P = 0)
		{if (__P != _Ptr)
			delete _Ptr;
		_Ptr = __P; }
private:
	_Ty *_Ptr;
	};








 
















 
#line 30 "c:\\rm3dev\\incplus\\vector"



		
template<class _Ty, class _A>
	class _Vector_val {
protected:
	_Vector_val(_A _Al = _A())
		: _Alval(_Al) {}
	typedef  _A::
		rebind<_Ty>::other _Alty;
	_Alty _Alval;
	};

		
template<class _Ty, class _Ax = allocator<_Ty> >
	class vector : public _Vector_val<_Ty, _Ax> {
public:
	typedef vector<_Ty, _Ax> _Myt;
	typedef _Vector_val<_Ty, _Ax> _Mybase;
	typedef  _Mybase::_Alty _A;
	typedef _A allocator_type;
	typedef  _A::size_type size_type;
	typedef  _A::difference_type difference_type;
	typedef  _A::pointer _Tptr;
	typedef  _A::const_pointer _Ctptr;
	typedef _Tptr pointer;
	typedef _Ctptr const_pointer;
	typedef  _A::reference reference;
	typedef  _A::const_reference const_reference;
	typedef  _A::value_type value_type;
	typedef _Ptrit<value_type, difference_type, _Tptr,
		reference, _Tptr, reference> iterator;
	typedef _Ptrit<value_type, difference_type, _Ctptr,
		const_reference, _Tptr, reference> const_iterator;
	typedef :: reverse_iterator<iterator>
		reverse_iterator;
	typedef :: reverse_iterator<const_iterator>
		const_reverse_iterator;
	vector()
		: _Mybase()
		{_Buy(0); }
	explicit vector(const _A& _Al)
		: _Mybase(_Al)
		{_Buy(0); }
	explicit vector(size_type __N)
		: _Mybase()
		{if (_Buy(__N))
			_Last = _Ufill(_First, __N, _Ty()); }
	vector(size_type __N, const _Ty& _V)
		: _Mybase()
		{if (_Buy(__N))
			_Last = _Ufill(_First, __N, _V); }
	vector(size_type __N, const _Ty& _V, const _A& _Al)
		: _Mybase(_Al)
		{if (_Buy(__N))
			_Last = _Ufill(_First, __N, _V); }
	vector(const _Myt& __X)
		: _Mybase(__X._Alval)
		{if (_Buy(__X.size()))
			_Last = _Ucopy(__X.begin(), __X.end(), _First); }
	template<class _It>
		vector(_It _F, _It __L)
		: _Mybase()
		{_Construct(_F, __L, _Iter_cat(_F)); }
	template<class _It>
		vector(_It _F, _It __L, const _A& _Al)
		: _Mybase(_Al)
		{_Construct(_F, __L, _Iter_cat(_F)); }
	template<class _It>
		void _Construct(_It _F, _It __L, _Int_iterator_tag)
		{size_type __N = (size_type)_F;
		if (_Buy(__N))
			_Last = _Ufill(_First, __N, (_Ty)__L); }
	template<class _It>
		void _Construct(_It _F, _It __L, input_iterator_tag)
		{_Buy(0);
		insert(begin(), _F, __L); }
	~vector()
		{_Clear(); }
	_Myt& operator=(const _Myt& __X)
		{if (this == &__X)
			;
		else if (__X.size() == 0)
			{_Clear(); }
		else if (__X.size() <= size())
			{pointer _Q = copy(__X.begin(), __X.end(), _First);
			_Destroy(_Q, _Last);
			_Last = _First + __X.size(); }
		else if (__X.size() <= capacity())
			{const_iterator __S = __X.begin() + size();
			copy(__X.begin(), __S, _First);
			_Last = _Ucopy(__S, __X.end(), _Last); }
		else
			{_Destroy(_First, _Last);
			_Alval.deallocate(_First, _End - _First);
			if (_Buy(__X.size()))
				_Last = _Ucopy(__X.begin(), __X.end(), _First); }
		return (*this); }
	void reserve(size_type __N)
		{if (max_size() < __N)
			_Xlen();
		else if (capacity() < __N)
			{pointer _Q = _Alval.allocate(__N, (void *)0);
			try {
			_Ucopy(begin(), end(), _Q);
			} catch (...) {
			_Alval.deallocate(_Q, __N);
			throw;
			}
			if (_First != 0)
				{_Destroy(_First, _Last);
				_Alval.deallocate(_First, _End - _First); }
			_End = _Q + __N;
			_Last = _Q + size();
			_First = _Q; }}
	size_type capacity() const
		{return (_First == 0 ? 0 : _End - _First); }
	iterator begin()
		{return (iterator(_First)); }
	const_iterator begin() const
		{return (const_iterator(_First)); }
	iterator end()
		{return (iterator(_Last)); }
	const_iterator end() const
		{return (const_iterator(_Last)); }
	reverse_iterator rbegin()
		{return (reverse_iterator(end())); }
	const_reverse_iterator rbegin() const
		{return (const_reverse_iterator(end())); }
	reverse_iterator rend()
		{return (reverse_iterator(begin())); }
	const_reverse_iterator rend() const
		{return (const_reverse_iterator(begin())); }
	void resize(size_type __N)
		{resize(__N, _Ty()); }
	void resize(size_type __N, _Ty __X)
		{if (size() < __N)
			insert(end(), __N - size(), __X);
		else if (__N < size())
			erase(begin() + __N, end()); }
	size_type size() const
		{return (_First == 0 ? 0 : _Last - _First); }
	size_type max_size() const
		{return (_Alval.max_size()); }
	bool empty() const
		{return (size() == 0); }
	_A get_allocator() const
		{return (_Alval); }
	const_reference at(size_type __P) const
		{if (size() <= __P)
			_Xran();
		return (*(begin() + __P)); }
	reference at(size_type __P)
		{if (size() <= __P)
			_Xran();
		return (*(begin() + __P)); }
	const_reference operator[](size_type __P) const
		{return (*(begin() + __P)); }
	reference operator[](size_type __P)
		{return (*(begin() + __P)); }
	reference front()
		{return (*begin()); }
	const_reference front() const
		{return (*begin()); }
	reference back()
		{return (*(end() - 1)); }
	const_reference back() const
		{return (*(end() - 1)); }
	void push_back(const _Ty& __X)
		{insert(end(), __X); }
	void pop_back()
		{erase(end() - 1); }
	template<class _It>
		void assign(_It _F, _It __L)
		{_Assign(_F, __L, _Iter_cat(_F)); }
	template<class _It>
		void _Assign(_It _F, _It __L, _Int_iterator_tag)
		{assign((size_type)_F, (_Ty)__L); }
	template<class _It>
		void _Assign(_It _F, _It __L, input_iterator_tag)
		{erase(begin(), end());
		insert(begin(), _F, __L); }
	void assign(size_type __N, const _Ty& __X)
		{_Ty _Tx = __X;
		erase(begin(), end());
		insert(begin(), __N, _Tx); }
	iterator insert(iterator __P, const _Ty& __X)
		{size_type _Off = size() == 0 ? 0 : __P - begin();
		insert(__P, (size_type)1, __X);
		return (begin() + _Off); }
	void insert(iterator __P, size_type _M, const _Ty& __X)
		{_Ty _Tx = __X;
		size_type __N = capacity();
		if (_M == 0)
			;
		else if (max_size() - size() < _M)
			_Xlen();
		else if (__N < size() + _M)
			{__N = max_size() - __N < __N ? 0 : __N + __N;
			if (__N < size() + _M)
				__N = size() + _M;
			pointer __S = _Alval.allocate(__N, (void *)0);
			pointer _Q;
			try {
			_Q = _Ucopy(begin(), __P, __S);
			_Q = _Ufill(_Q, _M, _Tx);
			_Ucopy(__P, end(), _Q);
			} catch (...) {
			_Destroy(__S, _Q);
			_Alval.deallocate(__S, __N);
			throw;
			}
			if (_First != 0)
				{_Destroy(_First, _Last);
				_Alval.deallocate(_First, _End - _First); }
			_End = __S + __N;
			_Last = __S + size() + _M;
			_First = __S; }
		else if (end() - __P < _M)
			{_Ucopy(__P, end(), &*__P + _M);
			try {
			_Ufill(_Last, _M - (end() - __P), _Tx);
			} catch (...) {
			_Destroy(&*__P + _M, _Last + _M);
			throw;
			}
			_Last += _M;
			fill(__P, end() - _M, _Tx); }
		else
			{iterator _Oend = end();
			_Last = _Ucopy(_Oend - _M, _Oend, _Last);
			copy_backward(__P, _Oend - _M, _Oend);
			fill(__P, __P + _M, _Tx); }}
	template<class _It>
		void insert(iterator __P, _It _F, _It __L)
		{_Insert(__P, _F, __L, _Iter_cat(_F)); }
	template<class _It>
		void _Insert(iterator __P, _It _F, _It __L,
			_Int_iterator_tag)
		{insert(__P, (size_type)_F, (_Ty)__L); }
	template<class _It>
		void _Insert(iterator __P, _It _F, _It __L,
			input_iterator_tag)
		{for (; _F != __L; ++_F, ++__P)
			__P = insert(__P, *_F); }
	template<class _It>
		void _Insert(iterator __P, _It _F, _It __L,
			forward_iterator_tag)
		{size_type _M = 0;
		_Distance(_F, __L, _M);
		size_type __N = capacity();
		if (_M == 0)
			;
		else if (max_size() - size() < _M)
			_Xlen();
		else if (__N < size() + _M)
			{__N = max_size() - __N < __N ? 0 : __N + __N;
			if (__N < size() + _M)
				__N = size() + _M;
			pointer __S = _Alval.allocate(__N, (void *)0);
			pointer _Q;
			try {
			_Q = _Ucopy(begin(), __P, __S);
			_Q = _Ucopy(_F, __L, _Q);
			_Ucopy(__P, end(), _Q);
			} catch (...) {
			_Destroy(__S, _Q);
			_Alval.deallocate(__S, __N);
			throw;
			}
			if (_First != 0)
				{_Destroy(_First, _Last);
				_Alval.deallocate(_First, _End - _First); }
			_End = __S + __N;
			_Last = __S + size() + _M;
			_First = __S; }
		else if (end() - __P < _M)
			{_Ucopy(__P, end(), &*__P + _M);
			_It _Mid = _F;
			advance(_Mid, end() - __P);
			try {
			_Ucopy(_Mid, __L, _Last);
			} catch (...) {
			_Destroy(&*__P + _M, _Last + _M);
			throw;
			}
			_Last += _M;
			copy(_F, _Mid, __P); }
		else if (0 < _M)
			{iterator _Oend = end();
			_Last = _Ucopy(_Oend - _M, _Oend, _Last);
			copy_backward(__P, _Oend - _M, _Oend);
			copy(_F, __L, __P); }}
	iterator erase(iterator __P)
		{copy(__P + 1, end(), __P);
		_Destroy(_Last - 1, _Last);
		--_Last;
		return (__P); }
	iterator erase(iterator _F, iterator __L)
		{if (_F != __L)
			{pointer __S = copy(__L, end(), &*_F);
			_Destroy(__S, _Last);
			_Last = __S; }
		return (_F); }
	void clear()
		{erase(begin(), end()); }
	bool _Eq(const _Myt& __X) const
		{return (size() == __X.size()
			&& equal(begin(), end(), __X.begin())); }
	bool _Lt(const _Myt& __X) const
		{return (lexicographical_compare(begin(), end(),
			__X.begin(), __X.end())); }
	void swap(_Myt& __X)
		{if (_Alval == __X._Alval)
			{:: swap(_First, __X._First);
			:: swap(_Last, __X._Last);
			:: swap(_End, __X._End); }
		else
			{_Myt _Ts = *this; *this = __X, __X = _Ts; }}
protected:
	bool _Buy(size_type __N)
		{_First = 0, _Last = 0, _End = 0;
		if (__N == 0)
			return (false);
		else
			{_First = _Alval.allocate(__N, (void *)0);
			_Last = _First;
			_End = _First + __N;
			return (true); }}
	void _Clear()
		{if (_First != 0)
			{_Destroy(_First, _Last);
			_Alval.deallocate(_First, _End - _First); }
		_First = 0, _Last = 0, _End = 0; }
	void _Destroy(pointer _F, pointer __L)
		{for (; _F != __L; ++_F)
			_Alval.destroy(_F); }
	template<class _It>
	pointer _Ucopy(_It _F, _It __L, pointer _Q)
		{pointer _Qs = _Q;
		try {
		for (; _F != __L; ++_Q, ++_F)
			_Alval.construct(_Q, *_F);
		} catch (...) {
		_Destroy(_Qs, _Q);
		throw;
		}
		return (_Q); }
	pointer _Ufill(pointer _Q, size_type __N, const _Ty &__X)
		{pointer _Qs = _Q;
		try {
		for (; 0 < __N; --__N, ++_Q)
			_Alval.construct(_Q, __X);
		} catch (...) {
		_Destroy(_Qs, _Q);
		throw;
		}
		return (_Q); }
	void _Xlen() const
		{throw length_error("vector<T> too long"); }
	void _Xran() const
		{throw out_of_range("invalid vector<T> subscript"); }
	pointer _First, _Last, _End;
	};
		
template<class _Ty, class _A> inline
	bool operator==(const vector<_Ty, _A>& __X,
		const vector<_Ty, _A>& _Y)
	{return (__X._Eq(_Y)); }
template<class _Ty, class _A> inline
	bool operator!=(const vector<_Ty, _A>& __X,
		const vector<_Ty, _A>& _Y)
	{return (!(__X == _Y)); }
template<class _Ty, class _A> inline
	bool operator<(const vector<_Ty, _A>& __X,
		const vector<_Ty, _A>& _Y)
	{return (__X._Lt(_Y)); }
template<class _Ty, class _A> inline
	bool operator>(const vector<_Ty, _A>& __X,
		const vector<_Ty, _A>& _Y)
	{return (_Y < __X); }
template<class _Ty, class _A> inline
	bool operator<=(const vector<_Ty, _A>& __X,
		const vector<_Ty, _A>& _Y)
	{return (!(_Y < __X)); }
template<class _Ty, class _A> inline
	bool operator>=(const vector<_Ty, _A>& __X,
		const vector<_Ty, _A>& _Y)
	{return (!(__X < _Y)); }
template<class _Ty, class _A> inline
	void swap(vector<_Ty, _A>& __X, vector<_Ty, _A>& _Y)
	{__X.swap(_Y); }

		
typedef unsigned int _Vbase;
const int _VBITS = 8 * sizeof (_Vbase);	
typedef allocator<_Vbase> _Bool_allocator;
template<> class vector<_Bool, _Bool_allocator> {
public:
	typedef _Bool_allocator _A;
	typedef _A::size_type size_type;
	typedef _A::difference_type _Dift;
	typedef :: vector<_Vbase, _A> _Vbtype;
	typedef :: vector<_Bool, _A> _Myt;
	typedef _Dift difference_type;
	typedef _Bool _Ty;
	typedef _A allocator_type;
		
	class reference {
	public:
		reference()
			: _Mask(0), _Ptr(0) {}
		reference(size_t _Off, _Vbase *__P)
			: _Mask((_Vbase)1 << _Off), _Ptr(__P) {}
		reference& operator=(const reference& __X)
			{return (*this = bool(__X)); }
		reference& operator=(bool _V)
			{if (_V)
				*_Ptr |= _Mask;
			else
				*_Ptr &= ~_Mask;
			return (*this); }
		void flip()
			{*_Ptr ^= _Mask; }
		bool operator~() const
			{return (!bool(*this)); }
		operator bool() const
			{return ((*_Ptr & _Mask) != 0); }
	protected:
		_Vbase _Mask, *_Ptr;
		};
	typedef reference _Reft;
	typedef bool const_reference;
	typedef bool value_type;
		
	class const_iterator;
	class iterator
		: public _Ranit<_Bool, _Dift, _Reft *, _Reft> {
	public:
		typedef _Ranit<_Bool, _Dift, _Reft *, _Reft> _Mybase;
		typedef _Mybase::iterator_category
			iterator_category;
		typedef _Mybase::value_type value_type;
		typedef _Mybase::difference_type
			difference_type;
		typedef _Mybase::pointer pointer;
		typedef _Mybase::reference reference;
		friend class const_iterator;
		iterator()
			: _Off(0), _Ptr(0) {}
		iterator(size_t _O, _Vbtype::iterator __P)
			: _Off(_O), _Ptr(__P.base()) {}
		reference operator*() const
			{return (_Reft(_Off, _Ptr)); }
		iterator& operator++()
			{_Inc();
			return (*this); }
		iterator operator++(int)
			{iterator _Tmp = *this;
			_Inc();
			return (_Tmp); }
		iterator& operator--()
			{_Dec();
			return (*this); }
		iterator operator--(int)
			{iterator _Tmp = *this;
			_Dec();
			return (_Tmp); }
		iterator& operator+=(difference_type __N)
			{_Off += __N;
			_Ptr += _Off / _VBITS;
			_Off %= _VBITS;
			return (*this); }
		iterator& operator-=(difference_type __N)
			{return (*this += -__N); }
		iterator operator+(difference_type __N) const
			{iterator _Tmp = *this;
			return (_Tmp += __N); }
		iterator operator-(difference_type __N) const
			{iterator _Tmp = *this;
			return (_Tmp -= __N); }
		difference_type operator-(const iterator __X) const
			{return (_VBITS * (_Ptr - __X._Ptr)
				+ (difference_type)_Off
				- (difference_type)__X._Off); }
		reference operator[](difference_type __N) const
			{return (*(*this + __N)); }
		bool operator==(const iterator& __X) const
			{return (_Ptr == __X._Ptr && _Off == __X._Off); }
		bool operator!=(const iterator& __X) const
			{return (!(*this == __X)); }
		bool operator<(const iterator& __X) const
			{return (_Ptr < __X._Ptr
				|| _Ptr == __X._Ptr && _Off < __X._Off); }
		bool operator>(const iterator& __X) const
			{return (__X < *this); }
		bool operator<=(const iterator& __X) const
			{return (!(__X < *this)); }
		bool operator>=(const iterator& __X) const
			{return (!(*this < __X)); }
	protected:
		void _Dec()
			{if (_Off != 0)
				--_Off;
			else
				_Off = _VBITS - 1, --_Ptr; }
		void _Inc()
			{if (_Off < _VBITS - 1)
				++_Off;
			else
				_Off = 0, ++_Ptr; }
		size_t _Off;
		_Vbase *_Ptr;
		};
	typedef iterator _Myit;
		
	class const_iterator : public _Ranit<_Bool, _Dift,
		const_reference *, const_reference> {
	public:
		typedef _Ranit<_Bool, _Dift,
			const_reference *, const_reference> _Mybase;
		typedef _Mybase::iterator_category
			iterator_category;
		typedef _Mybase::value_type value_type;
		typedef _Mybase::difference_type
			difference_type;
		typedef _Mybase::pointer pointer;
		typedef _Mybase::reference reference;
		const_iterator()
			: _Off(0), _Ptr(0) {}
		const_iterator(size_t _O, _Vbtype::const_iterator __P)
			: _Off(_O), _Ptr(__P.base()) {}
		const_iterator(const _Myit& __X)
			: _Off(__X._Off), _Ptr(__X._Ptr) {}
		const_reference operator*() const
			{return (_Reft(_Off, (_Vbase *)_Ptr)); }
		const_iterator& operator++()
			{_Inc();
			return (*this); }
		const_iterator operator++(int)
			{const_iterator _Tmp = *this;
			_Inc();
			return (_Tmp); }
		const_iterator& operator--()
			{_Dec();
			return (*this); }
		const_iterator operator--(int)
			{const_iterator _Tmp = *this;
			_Dec();
			return (_Tmp); }
		const_iterator& operator+=(difference_type __N)
			{_Off += __N;
			_Ptr += _Off / _VBITS;
			_Off %= _VBITS;
			return (*this); }
		const_iterator& operator-=(difference_type __N)
			{return (*this += -__N); }
		const_iterator operator+(difference_type __N) const
			{const_iterator _Tmp = *this;
			return (_Tmp += __N); }
		const_iterator operator-(difference_type __N) const
			{const_iterator _Tmp = *this;
			return (_Tmp -= __N); }
		difference_type operator-(const const_iterator __X) const
			{return (_VBITS * (_Ptr - __X._Ptr)
				+ (difference_type)_Off
				- (difference_type)__X._Off); }
		const_reference operator[](difference_type __N) const
			{return (*(*this + __N)); }
		bool operator==(const const_iterator& __X) const
			{return (_Ptr == __X._Ptr && _Off == __X._Off); }
		bool operator!=(const const_iterator& __X) const
			{return (!(*this == __X)); }
		bool operator<(const const_iterator& __X) const
			{return (_Ptr < __X._Ptr
				|| _Ptr == __X._Ptr && _Off < __X._Off); }
		bool operator>(const const_iterator& __X) const
			{return (__X < *this); }
		bool operator<=(const const_iterator& __X) const
			{return (!(__X < *this)); }
		bool operator>=(const const_iterator& __X) const
			{return (!(*this < __X)); }
	protected:
		void _Dec()
			{if (_Off != 0)
				--_Off;
			else
				_Off = _VBITS - 1, --_Ptr; }
		void _Inc()
			{if (_Off < _VBITS - 1)
				++_Off;
			else
				_Off = 0, ++_Ptr; }
		size_t _Off;
		const _Vbase *_Ptr;
		};
	typedef iterator pointer;
	typedef const_iterator const_pointer;
	typedef :: reverse_iterator<iterator>
		reverse_iterator;
	typedef :: reverse_iterator<const_iterator>
		const_reverse_iterator;
	vector()
		: _Size(0), _Vec() {}
	explicit vector(const _A& _Al)
		: _Size(0), _Vec(_Al) {}
	explicit vector(size_type __N, const bool _V = false)
		: _Size(0), _Vec(_Nw(__N), _V ? -1 : 0)
		{_Trim(__N); }
	vector(size_type __N, const bool _V, const _A& _Al)
		: _Size(0), _Vec(_Nw(__N), _V ? -1 : 0, _Al)
		{_Trim(__N); }
	template<class _It>
		vector(_It _F, _It __L)
		: _Size(0), _Vec()
		{_BConstruct(_F, __L, _Iter_cat(_F)); }
	template<class _It>
		vector(_It _F, _It __L, const _A& _Al)
		: _Size(0), _Vec(_Al)
		{_BConstruct(_F, __L, _Iter_cat(_F)); }
	template<class _It>
		void _BConstruct(_It _F, _It __L, _Int_iterator_tag)
		{size_type __N = (size_type)_F;
		_Vec.assign(__N, (_Ty)__L ? -1 : 0);
		_Trim(__N); }
	template<class _It>
		void _BConstruct(_It _F, _It __L, input_iterator_tag)
		{insert(begin(), _F, __L); }
	~vector()
		{_Size = 0; }
	void reserve(size_type __N)
		{_Vec.reserve(_Nw(__N)); }
	size_type capacity() const
		{return (_Vec.capacity() * _VBITS); }
	iterator begin()
		{return (iterator(0, _Vec.begin())); }
	const_iterator begin() const
		{return (const_iterator(0, _Vec.begin())); }
	iterator end()
		{iterator _Tmp = begin();
		if (0 < _Size)
			_Tmp += _Size;
		return (_Tmp); }
	const_iterator end() const
		{const_iterator _Tmp = begin();
		if (0 < _Size)
			_Tmp += _Size;
		return (_Tmp); }
	reverse_iterator rbegin()
		{return (reverse_iterator(end())); }
	const_reverse_iterator rbegin() const
		{return (const_reverse_iterator(end())); }
	reverse_iterator rend()
		{return (reverse_iterator(begin())); }
	const_reverse_iterator rend() const
		{return (const_reverse_iterator(begin())); }
	void resize(size_type __N, bool __X = false)
		{if (size() < __N)
			insert(end(), __N - size(), __X);
		else if (__N < size())
			erase(begin() + __N, end()); }
	size_type size() const
		{return (_Size); }
	size_type max_size() const
		{return (_Vec.max_size() * _VBITS); }
	bool empty() const
		{return (size() == 0); }
	_A get_allocator() const
		{return (_Vec.get_allocator()); }
	const_reference at(size_type __P) const
		{if (size() <= __P)
			_Xran();
		return (*(begin() + __P)); }
	reference at(size_type __P)
		{if (size() <= __P)
			_Xran();
		return (*(begin() + __P)); }
	const_reference operator[](size_type __P) const
		{return (*(begin() + __P)); }
	reference operator[](size_type __P)
		{return (*(begin() + __P)); }
	reference front()
		{return (*begin()); }
	const_reference front() const
		{return (*begin()); }
	reference back()
		{return (*(end() - 1)); }
	const_reference back() const
		{return (*(end() - 1)); }
	void push_back(const bool __X)
		{insert(end(), __X); }
	void pop_back()
		{erase(end() - 1); }
	template<class _It>
		void assign(_It _F, _It __L)
		{_Assign(_F, __L, _Iter_cat(_F)); }
	template<class _It>
		void _Assign(_It _F, _It __L, _Int_iterator_tag)
		{assign((size_type)_F, (_Ty)__L); }
	template<class _It>
		void _Assign(_It _F, _It __L, input_iterator_tag)
		{erase(begin(), end());
		insert(begin(), _F, __L); }
	void assign(size_type __N, const _Ty& __X)
		{_Ty _Tx = __X;
		erase(begin(), end());
		insert(begin(), __N, _Tx); }
	iterator insert(iterator __P, const bool __X)
		{size_type _Off = __P - begin();
		insert(__P, (size_type)1, __X);
		return (begin() + _Off); }
	void insert(iterator __P, size_type _M, const bool __X)
		{if (_M == 0)
			;
		else if (max_size() - size() < _M)
			_Xlen();
		else
			{if (size() + _M <= capacity())
				;
			else if (size() == 0)
				{_Vec.resize(_Nw(size() + _M), 0);
				__P = begin(); }
			else
				{size_type _Off = __P - begin();
				_Vec.resize(_Nw(size() + _M), 0);
				__P = begin() + _Off;
				copy_backward(__P, end(), end() + _M); }
			fill(__P, __P + _M, __X);
			_Size += _M; }}
	template<class _It>
		void insert(iterator __P, _It _F, _It __L)
		{_Insert(__P, _F, __L, _Iter_cat(_F)); }
	template<class _It>
		void _Insert(iterator __P, _It _F, _It __L,
			_Int_iterator_tag)
		{insert(__P, (size_type)_F, (_Ty)__L); }
	template<class _It>
		void _Insert(iterator __P, _It _F, _It __L,
			input_iterator_tag)
		{size_type _Off = __P - begin();
		for (; _F != __L; ++_F, ++_Off)
			insert(begin() + _Off, *_F); }
	template<class _It>
		void _Insert(iterator __P, _It _F, _It __L,
			forward_iterator_tag)
		{size_type _M = 0;
		_Distance(_F, __L, _M);
		if (_M == 0)
			;
		else if (max_size() - size() < _M)
			_Xlen();
		else
			{if (size() + _M <= capacity())
				;
			else if (size() == 0)
				{_Vec.resize(_Nw(size() + _M), 0);
				__P = begin(); }
			else
				{size_type _Off = __P - begin();
				_Vec.resize(_Nw(size() + _M), 0);
				__P = begin() + _Off;
				copy_backward(__P, end(), end() + _M); }
			copy(_F, __L, __P);
			_Size += _M; }}
	iterator erase(iterator __P)
		{copy(__P + 1, end(), __P);
		_Trim(_Size - 1);
		return (__P); }
	iterator erase(iterator _F, iterator __L)
		{iterator __S = copy(__L, end(), _F);
		_Trim(__S - begin());
		return (_F); }
	void clear()
		{erase(begin(), end()); }
	void flip()
		{for (_Vbtype::iterator __S = _Vec.begin();
			__S != _Vec.end(); ++__S)
			*__S = ~*__S;
		_Trim(_Size); }
	bool _Eq(const _Myt& __X) const
		{return (_Size == __X._Size && _Vec == __X._Vec); }
	bool _Lt(const _Myt& __X) const
		{return (lexicographical_compare(begin(), end(),
			__X.begin(), __X.end())); }
	void swap(_Myt& __X)
		{:: swap(_Size, __X._Size);
		_Vec.swap(__X._Vec); }
	static void swap(reference __X, reference _Y)
		{bool _V = __X;
		__X = _Y;
		_Y = _V; }
protected:
	static size_type _Nw(size_type __N)
		{return ((__N + _VBITS - 1) / _VBITS); }
	void _Trim(size_type __N)
		{if (size() < __N && max_size() <= __N)
			_Xlen();
		size_type _M = _Nw(__N);
		if (_M < _Vec.size())
			_Vec.erase(_Vec.begin() + _M, _Vec.end());
		_Size = __N;
		__N %= _VBITS;
		if (0 < __N)
			_Vec[_M - 1] &= ((_Vbase)1 << __N) - 1; }
	void _Xlen() const
		{throw out_of_range("vector<bool> too long"); }
	void _Xran() const
		{throw out_of_range("invalid vector<bool> subscript"); }
	size_type _Size;
	_Vbtype _Vec;
	};
typedef vector<_Bool, _Bool_allocator> _Bvector;








 
















 
#line 7 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\iniFile.h"







class CIniFile   
{
private:
  bool   caseInsensitive;
  string path;
  struct key {
    vector<string> names;
    vector<string> values; 
    vector<string> comments;
  };
  vector<key>    keys; 
  vector<string> names; 
  vector<string> comments;
  string CheckCase( string s) const;

public:
  enum errors{ noID = -1};
  CIniFile( string const iniPath = "");
  virtual ~CIniFile()                            {}

  void CaseSensitive()                           {caseInsensitive = false;}
  void CaseInsensitive()                         {caseInsensitive = true;}

  void Path(string const newPath)                {path = newPath;}
  string Path() const                            {return path;}
  void SetPath(string const newPath)             {Path( newPath);}

  bool ReadFile();
  
  bool WriteFile(); 
  
  void Erase();
  void Clear()                                   {Erase();}
  void Reset()                                   {Erase();}

  long FindKey( string const keyname) const;

  long FindValue( unsigned const keyID, string const valuename) const;

  unsigned NumKeys() const                       {return names.size();}
  unsigned GetNumKeys() const                    {return NumKeys();}


  unsigned AddKeyName( string const keyname);

  string KeyName( unsigned const keyID) const;
  string GetKeyName( unsigned const keyID) const {return KeyName(keyID);}

  unsigned NumValues( unsigned const keyID);
  unsigned GetNumValues( unsigned const keyID)   {return NumValues( keyID);}
  unsigned NumValues( string const keyname);
  unsigned GetNumValues( string const keyname)   {return NumValues( keyname);}

  string ValueName( unsigned const keyID, unsigned const valueID) const;
  string GetValueName( unsigned const keyID, unsigned const valueID) const {
    return ValueName( keyID, valueID);
  }
  string ValueName( string const keyname, unsigned const valueID) const;
  string GetValueName( string const keyname, unsigned const valueID) const {
    return ValueName( keyname, valueID);
  }

  string GetValue( unsigned const keyID, unsigned const valueID, string const defValue = "") const;
  string GetValue(string const keyname, string const valuename, string const defValue = "") const; 
  int    GetValueI(string const keyname, string const valuename, int const defValue = 0) const;
  double   GetValueF(string const keyname, string const valuename, double const defValue) const;

  unsigned GetValueV( string const keyname, string const valuename, char *format,
		      void *v1 = 0, void *v2 = 0, void *v3 = 0, void *v4 = 0,
  		      void *v5 = 0, void *v6 = 0, void *v7 = 0, void *v8 = 0,
  		      void *v9 = 0, void *v10 = 0, void *v11 = 0, void *v12 = 0,
  		      void *v13 = 0, void *v14 = 0, void *v15 = 0, void *v16 = 0);


  bool SetValue( unsigned const keyID, unsigned const valueID, string const value);
  bool SetValue( string const keyname, string const valuename, string const value, bool const create = true);
  bool SetValueI( string const keyname, string const valuename, int const value, bool const create = true);
  bool SetValueB( string const keyname, string const valuename, bool const value, bool const create = true) {
    return SetValueI( keyname, valuename, int(value), create);
  }
  bool SetValueF( string const keyname, string const valuename, double const value, bool const create = true);
  bool SetValueV( string const keyname, string const valuename, char *format, ...);

  bool DeleteValue( string const keyname, string const valuename);
  

  bool DeleteKey(string keyname);


  unsigned NumHeaderComments()                  {return comments.size();}

  void     HeaderComment( string const comment);

  string   HeaderComment( unsigned const commentID) const;

  bool     DeleteHeaderComment( unsigned commentID);

  void     DeleteHeaderComments()               {comments.clear();}


  unsigned NumKeyComments( unsigned const keyID) const;
  unsigned NumKeyComments( string const keyname) const;
 
  bool     KeyComment( unsigned const keyID, string const comment);
  bool     KeyComment( string const keyname, string const comment);

  string   KeyComment( unsigned const keyID, unsigned const commentID) const;
  string   KeyComment( string const keyname, unsigned const commentID) const;

  bool     DeleteKeyComment( unsigned const keyID, unsigned const commentID);
  bool     DeleteKeyComment( string const keyname, unsigned const commentID);

  bool     DeleteKeyComments( unsigned const keyID);
  bool     DeleteKeyComments( string const keyname);
};

#line 29 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\rpw.hpp"












#line 1 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\teso.hpp"







   
#line 24 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\teso.hpp"




	
	
 

	
 

	
 

	
 

	
 

	
 

	
 






#line 73 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\teso.hpp"












#line 91 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\teso.hpp"












#line 110 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\teso.hpp"

#line 172 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\teso.hpp"



#line 42 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\rpw.hpp"
#line 1 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\IBF_struct.hpp"

















 




 













 
 
 
#line 1 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\ibf_tool.hpp"

















 





 
#line 1 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\IBF_struct.hpp"

















 




 

#line 28 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\ibf_tool.hpp"





#line 1 "c:\\rm3dev\\incplus\\sstream"
 



















  





#pragma noarguments_in_registers(push)



enum __Strstate {_Allocated = 1, _Constant = 2, _Noread = 4};
typedef int _Strstate;

		



#pragma       align   (stringbuf=4)                   

class stringbuf : public streambuf {
public:
	typedef char _E;
	typedef char_traits _Tr;
	typedef char_allocator _A;
	typedef streambuf _Mysb;
	typedef string _Mystr;
	explicit stringbuf(
		ios_base::openmode _W = ios_base::in | ios_base::out)
		{_Init(0, 0, _Mode(_W)); }
	explicit stringbuf(const _Mystr& __S,
		ios_base::openmode _W = ios_base::in | ios_base::out)
		{_Init(__S.c_str(), __S.size(), _Mode(_W)); }
	virtual ~stringbuf()
		{_Tidy(); }
	typedef _Tr::int_type int_type;
	typedef _Tr::pos_type pos_type;
	typedef _Tr::off_type off_type;
	_Mystr str() const
		{if (!(_Strmode & _Constant) && _Mysb::pptr() != 0)
			{_Mystr _Str(_Mysb::pbase(),
				(_Seekhigh < _Mysb::pptr()
				? _Mysb::pptr() : _Seekhigh) - _Mysb::pbase());
			return (_Str); }
		else if (!(_Strmode & _Noread) && _Mysb::gptr() != 0)
			{_Mystr _Str(_Mysb::eback(),
				_Mysb::egptr() - _Mysb::eback());
			return (_Str); }
		else
			{_Mystr _Nul;
			return (_Nul); }}
	void str(const _Mystr& __S)
		{_Tidy();
		_Init(__S.c_str(), __S.size(), _Strmode); }
protected:
	virtual int_type overflow(int_type __C = _Tr::eof())
		{if (_Tr::eq_int_type(_Tr::eof(), __C))
			return (_Tr::not_eof(__C));
		else if (_Mysb::pptr() != 0
			&& _Mysb::pptr() < _Mysb::epptr())
			{*_Mysb::_Pninc() = _Tr::to_char_type(__C);
			return (__C); }
		else if (_Strmode & _Constant)
			return (_Tr::eof());
		else
			{size_t _Os = _Mysb::gptr() == 0
				? 0 : _Mysb::epptr() - _Mysb::eback();
			size_t _Ns = _Os + _Alsize;
			_E *__P = _Al.allocate(_Ns, (void *)0);
			if (0 < _Os)
				_Tr::copy(__P, _Mysb::eback(), _Os);
			else if (_ALSIZE < _Alsize)
				_Alsize = _ALSIZE;
			if (_Strmode & _Allocated)
				_Al.deallocate(_Mysb::eback(), _Os);
			_Strmode |= _Allocated;
			if (_Os == 0)
				{_Seekhigh = __P;
				_Mysb::setp(__P, __P + _Ns);
				_Mysb::setg(__P, __P, __P); }
			else
				{_Seekhigh = _Seekhigh - _Mysb::eback() + __P;
				_Mysb::setp(_Mysb::pbase() - _Mysb::eback() + __P,
					_Mysb::pptr() - _Mysb::eback() + __P,
					__P + _Ns);
				if (_Strmode & _Noread)
					_Mysb::setg(__P, __P, __P);
				else
					_Mysb::setg(__P,
						_Mysb::gptr() - _Mysb::eback() + __P,
						_Mysb::pptr() + 1); }
			*_Mysb::_Pninc() = _Tr::to_char_type(__C);
			return (__C); }}
	virtual int_type pbackfail(int_type __C = _Tr::eof())
		{if (_Mysb::gptr() == 0
			|| _Mysb::gptr() <= _Mysb::eback()
			|| !_Tr::eq_int_type(_Tr::eof(), __C)
			&& !_Tr::eq(_Tr::to_char_type(__C), _Mysb::gptr()[-1])
			&& _Strmode & _Constant)
			return (_Tr::eof());
		else
			{_Mysb::gbump(-1);
			if (!_Tr::eq_int_type(_Tr::eof(), __C))
				*_Mysb::gptr() = _Tr::to_char_type(__C);
			return (_Tr::not_eof(__C)); }}
	virtual int_type underflow()
		{if (_Mysb::gptr() == 0)
			return (_Tr::eof());
		else if (_Mysb::gptr() < _Mysb::egptr())
			return (_Tr::to_int_type(*_Mysb::gptr()));
		else if (_Strmode & _Noread || _Mysb::pptr() == 0
			|| _Mysb::pptr() <= _Mysb::gptr()
				&& _Seekhigh <= _Mysb::gptr())
			return (_Tr::eof());
		else
			{if (_Seekhigh < _Mysb::pptr())
				_Seekhigh = _Mysb::pptr();
			_Mysb::setg(_Mysb::eback(), _Mysb::gptr(), _Seekhigh);
			return (_Tr::to_int_type(*_Mysb::gptr())); }}
	virtual pos_type seekoff(off_type _O, ios_base::seekdir _Way,
		ios_base::openmode _Which = ios_base::in | ios_base::out)
		{if (_Mysb::pptr() != 0 && _Seekhigh < _Mysb::pptr())
			_Seekhigh = _Mysb::pptr();
		if (_Which & ios_base::in && _Mysb::gptr() != 0)
			{if (_Way == ios_base::end)
				_O += _Seekhigh - _Mysb::eback();
			else if (_Way == ios_base::cur
				&& !(_Which & ios_base::out))
				_O += _Mysb::gptr() - _Mysb::eback();
			else if (_Way != ios_base::beg)
				_O = _BADOFF;
			if (0 <= _O && _O <= _Seekhigh - _Mysb::eback())
				{_Mysb::gbump(_Mysb::eback()
					- _Mysb::gptr() + _O);
				if (_Which & ios_base::out && _Mysb::pptr() != 0)
					_Mysb::setp(_Mysb::pbase(), _Mysb::gptr(),
						_Mysb::epptr()); }
			else
				_O = _BADOFF; }
		else if (_Which & ios_base::out && _Mysb::pptr() != 0)
			{if (_Way == ios_base::end)
				_O += _Seekhigh - _Mysb::eback();
			else if (_Way == ios_base::cur)
				_O += _Mysb::pptr() - _Mysb::eback();
			else if (_Way != ios_base::beg)
				_O = _BADOFF;
			if (0 <= _O && _O <= _Seekhigh - _Mysb::eback())
				_Mysb::pbump(_Mysb::eback() - _Mysb::pptr() + _O);
			else
				_O = _BADOFF; }
		else
			_O = _BADOFF;
		return (pos_type(_O)); }
	virtual pos_type seekpos(pos_type __P,
		ios_base::openmode _Which = ios_base::in | ios_base::out)
		{streamoff _O = (streamoff)__P;
		if (_Mysb::pptr() != 0 && _Seekhigh < _Mysb::pptr())
			_Seekhigh = _Mysb::pptr();
		if (_O == _BADOFF)
			;
		else if (_Which & ios_base::in && _Mysb::gptr() != 0)
			{if (0 <= _O && _O <= _Seekhigh - _Mysb::eback())
				{_Mysb::gbump(_Mysb::eback()
					- _Mysb::gptr() + _O);
				if (_Which & ios_base::out && pptr() != 0)
					_Mysb::setp(_Mysb::pbase(), _Mysb::gptr(),
						_Mysb::epptr()); }
			else
				_O = _BADOFF; }
		else if (_Which & ios_base::out && _Mysb::pptr() != 0)
			{if (0 <= _O && _O <= _Seekhigh - _Mysb::eback())
				_Mysb::pbump(_Mysb::eback() - _Mysb::pptr() + _O);
			else
				_O = _BADOFF; }
		else
			_O = _BADOFF;
		return (streampos(_O)); }
	void _Init(const _E *__S, size_t __N, _Strstate _M)
		{_Pendsave = 0, _Seekhigh = 0;
		_Alsize = _MINSIZE, _Strmode = _M;
		if (__N == 0 || (_Strmode & (_Noread | _Constant))
			== (_Noread | _Constant))
			{_Mysb::setg(0, 0, 0);
			_Mysb::setp(0, 0); }
		else
			{_E *__P = _Al.allocate(__N, (void *)0);
			_Tr::copy(__P, __S, __N);
			_Seekhigh = __P + __N;
			if (!(_Strmode & _Noread))
				_Mysb::setg(__P, __P, __P + __N);
			if (!(_Strmode & _Constant))
				{_Mysb::setp(__P, __P + __N);
				if (_Mysb::gptr() == 0)
					_Mysb::setg(__P, __P, __P); }
			_Strmode |= _Allocated; }}
	void _Tidy()
		{if (_Strmode & _Allocated)
			_Al.deallocate(_Mysb::eback(),
				(_Mysb::pptr() != 0 ? _Mysb::epptr()
					: _Mysb::egptr()) - _Mysb::eback());
		_Seekhigh = 0;
		_Strmode &= ~_Allocated; }
private:
	enum {_ALSIZE = 512, _MINSIZE = 32};
	_Strstate _Mode(ios_base::openmode _W)
		{_Strstate _St = (_Strstate)0;
		if (!(_W & ios_base::in))
			_St |= _Noread;
		if (!(_W & ios_base::out))
			_St |= _Constant;
		return (_St); }
	_E *_Pendsave, *_Seekhigh;
	int _Alsize;
	_Strstate _Strmode;
	_A _Al;
	};
		



#pragma       align   (istringstream=4)               

class istringstream : public istream {
public:
	typedef char_traits _Tr;
	typedef stringbuf _Mysb;
	typedef string _Mystr;
	explicit istringstream(ios_base::openmode _M = ios_base::in)
		: istream(&_Sb), _Sb(_M | ios_base::in) {}
	explicit istringstream(const _Mystr& __S,
		ios_base::openmode _M = ios_base::in)
		: istream(&_Sb), _Sb(__S, _M | ios_base::in) {}
	virtual ~istringstream()
		{}
	_Mysb *rdbuf() const
		{return ((_Mysb *)&_Sb); }
	_Mystr str() const
		{return (_Sb.str()); }
	void str(const _Mystr& __S)
		{_Sb.str(__S); }
private:
	_Mysb _Sb;
	};
		



#pragma       align   (ostringstream=4)               

class ostringstream : public ostream {
public:
	typedef char_traits _Tr;
	typedef stringbuf _Mysb;
	typedef string _Mystr;
	explicit ostringstream(ios_base::openmode _M = ios_base::out)
		: ostream(&_Sb), _Sb(_M | ios_base::out) {}
	explicit ostringstream(const _Mystr& __S,
		ios_base::openmode _M = ios_base::out)
		: ostream(&_Sb), _Sb(__S, _M | ios_base::out) {}
	virtual ~ostringstream()
		{}
	_Mysb *rdbuf() const
		{return ((_Mysb *)&_Sb); }
	_Mystr str() const
		{return (_Sb.str()); }
	void str(const _Mystr& __S)
		{_Sb.str(__S); }
private:
	_Mysb _Sb;
	};


#pragma arguments_in_registers(pop)






 
#line 37 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\ibf_tool.hpp"
#line 1 "c:\\rm3dev\\incplus\\iostream"
 



















  





#pragma noarguments_in_registers(push)



		
static ios_base::Init _Ios_init;
extern istream cin;
extern ostream cout;


#pragma arguments_in_registers(pop)






 
#line 38 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\ibf_tool.hpp"









    
    
    
    

    

	
 
    float KW_Drehzahl_axial  (struct Def_Ist_Inter Ist_Inter, struct Def_IBF_Allgemein_IST  *Ist_IBF);
    float KW_Drehzahl_unten (struct Def_Ist_Inter Ist_Inter, struct Def_IBF_Allgemein_IST  *Ist_IBF);
    
    
    
    void rs_aso_mode(struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF, int Funktionswahl);

    
    void Axialkraft     (struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);
    void Kraftsteuerung (struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);
    void Anwalzen_Radial(struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);
    void Anwalzen_Axial (struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF); 


    
    void IBF_Abschaltung(struct Def_Soll_Inter *Soll_Inter,struct Def_IBF_Allgemein_IST Ist_IBF);
    
    
    
    
    
    void Breitungsexp(struct Def_IBF_Allgemein_IST *Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);
    void Durchme_t2  (struct Def_Ist_Inter Ist_Inter, struct Def_IBF_Allgemein_IST *Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);

    void Volumenbestimmung(struct Def_IBF_Allgemein_IST *Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);
    void Hoehenzunahme(struct Def_Ist_Inter Ist_Inter, struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);

    
    
    int   AGR_Pr_Wanddicken_Verhaeltnis_proz(struct Def_Ist_Inter Ist_Inter, struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);
    char  AGR_Nachfuehr_Entscheider         (struct Def_Ist_Inter Ist_Inter, struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);
    float AGR_Soll_Pos                      (struct Def_Ist_Inter Ist_Inter, struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);
    void AGR_Soll_Pos_delta_Tr             (struct Def_Ist_Inter Ist_Inter, struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);
    
    
    


                                                               



#line 41 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\IBF_struct.hpp"
#line 1 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\IBF_radflex.hpp"
















 




 





 
 
 
#line 1 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\ibf_tool.hpp"

















 





 




#line 96 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\ibf_tool.hpp"


#line 32 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\IBF_radflex.hpp"
        
    
  
 
 

  struct Cr_Berechnung
    {
      
 
      float a;            
	   	
 
      float b;            
	   	
 
      float c;            
	   	
 
      float d;      		
	   	
 
      float e;             

      
 
	   	float o;
	   	
 
	   	float u;             

	   	
 
	   	float g;             
	   	
 
      float f;             

       

      
 
      int os_i;            
      
 
      float Array[2];      
		                
    };

    


 
    struct Breitung
    {
	  
 
        float mr;
        
 
        float qf;
        
 
        float ga;
        
 
        float e_mr;

        
 
        float Da_t2;
        
 
        float Di_t2;
        
 
        float Da_t2_h2;
        
 
        float Di_t2_h2;


        
 
        float Volumen_t1;
        
 
        float Volumen_t2;
        
 
        float Volumen_diff; 
        
 
        float delta_h;
    };

    
    struct Filter
    {
        float yF_neu;
        float yF_alt;        
    };

    
 
    struct Radial_Flex_Prof
    {
         
	




 
        int Schalter_Kont_DisKo; 
        int t_warte_flag;
        


 
	int Profilflag;


         

         

        
 
        float delta_h;
        
 
        float delta_s;              
        
 
        float abnahme_s;            


        
 
        float Soll_Wanddicke;       


         

        
 
        float t_dis_h;               
        
 
        int Umdrehungen;              
        
 
        float t_warte;               

        
         

        
 
        float s_f;                 
        
 
        float s_f_alt;              

        
 
        struct Filter s_f_Filter;   
        
        
 
        float Werkzeugbreite;       

        
 
        float Anfangsposition_DW;   

        
 
        float Stegstaerke;          

        
 
        float Rohlinghoehe;        
        
       

         
        
 
        float Vorschubgeschw_Dw;   
        
 
        float Vorschubgeschw_ASO;  
        
 
        float eps_Vorschub;        
        
        
 
        float dw_vn;               

         

        
 
        float Walzspalt_Cr;          
        
        struct Cr_Berechnung Cr;     
        
        
 
        struct Breitung Breitung;   
    };


#line 42 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\IBF_struct.hpp"
#line 1 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\IBF_axproflex.hpp"
















 




 






 
 
 





   

  

    

    

 
    struct Def_Kragen_Geo
    {
    	
 
        float Kr_Br;
        
 
        float Kr_d_nenn_mitte;
        
 
        float Kr_d_nenn_vorne;
        
 
        float Kr_d_nenn_hinten;
        
 
        float Del_Kr_AGR;

        
 
        float max_Pr_Tiefe;
        
 
        float sin_kw_winkel_halbe;
        
 
        float l_fehlende_spitze_ukw;
        

 
        float l_mantel_ukw_o_fehlende_spitze;
        
    };

    

 
    struct Def_Biss_Ver
    {
        float Verhaeltnis;
        
        float AG_Pos_alt;
        
        
        
        int Position;
        
        int Anzahl;
        
        int Anzahl_zweite_Ebene;
        

        float AGR_Pr_Merker;
        
        int AG_Pos_Erreicht;
        

    };
    
    struct Def_Turbine
    {
        int Turbinenscheibe;          
                
        int Ebene1_fertig;
        
        int AG_Pos_Erreicht;
        
        
        float s_akt_Merker;
        
        
        int Stufe_erreicht;
        
        int zweite_Ebene_erreicht;
        
    };


    

 
    struct Axial_Flex_Prof
    {
       










 
        int Profilflag;

        
 
        float Anfahrdurchm;
        
 
        int Umdrehungen;

        
        

 
        struct Def_Kragen_Geo Kr_geo;

        
 
        struct Def_Biss_Ver Biss;
        
        struct Def_Turbine Turbine;
        

        
 
        int Profilanzahl;
        
 
        int Pr_Num;
        

        
 
        float AGR_Pr[6];
        
 
        float Pr_Tiefe[6];
        
 
        float Vorschub;


        
 
        float Verh_pr_sf_proz_start;
        
 
        float Verh_pr_sf_proz;
        

 
        int Wert;

    };


#line 43 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\IBF_struct.hpp"
#line 1 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\IBF_stuetz.hpp"

















 




 









 




 




void stuetzstellen(struct Def_Ist_Inter Ist_Inter, struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);

void konst_cr_radial(struct Def_Ist_Inter Ist_Inter, struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);
void konst_cr_axial(struct Def_Ist_Inter Ist_Inter, struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);



 
struct stuetzstellen_var
{
	

	
 
	float t_U; 					       
	
 
	float crtimer;                     


	
 
	float stellen[2][25];	  
	
 
	int merker;		                  
	
 
	int skip_faktor;	              
  
 
  float kontrollmerker;
	
 
	float cr;      
	
 
	float ca;      

	
 
    float delta_h;  
    
 
    float delta_s;  

};


#line 44 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\IBF_struct.hpp"
#line 1 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\IBF_dw_regelung.hpp"

















 




 







		
 




		
 




		
 




		
 





 
 void Beta                     (struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);
 void Alpha                    (struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);
 void Gamma                    (struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);
 void T_Einlauf                (struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);
 void Axial_Wanddicke_bestimmen(struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);
 void T_V                      (struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);
 void DW_Regelalgo             (struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);
 void DA_Jenkouk_Regler        (struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);

 
 void RS_nach_Messwert_Fahren  (struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);

 
 void AG_Regelalgo             (struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);
 void DA_Jenkouk_Regler_AG     (struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);
 void DA_Jenkouk_Regler        (struct Def_IBF_Allgemein_IST Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF);









 
struct Def_DW_Regelung_DA_Jenkouk
{
    
  int Funktios_Iter;         
  
  
  
 
  float Messwert_A;          
  

 
  float Messwert_A_mf;       
  
 
  float Messwert_A_alt_mf;   

  
 
  float Messwert_A_unten;          
  
 
  float Messwert_A_unten_mf;       
  
 
  float Messwert_A_unten_alt_mf;   
 
 
 
 
  
  
 
  float Abstand_C;           
  
  
  
 
  float Tastrollen_Radius;   
  
 
  float Offset; 

  
 
  float Messwert_Nullpunkt;  
  
 
  float Messwert_Nullpunkt_unten; 
  
 
  float U_v_HW;              
  
 
  float DW_Durchmesser;      
  

  
  
 
  float Wanddicke_berechnet;
  
 
  float DW_Pos_soll;
  
 
  float T_Einlauf;
  



 
  float T_Verzoegerung;
  

 
  int Anzahl_Zeitschritte;

  
  
 
  float Beta;
  
 
  float Alpha;
  
 
  float Gamma;

  
 
  float ri;
  
 
  float DW_soll_Pos[20];
  
 
  float DW_soll_Pos_Hilf[20];
  
 
  float Aufrufzeit_Regelzykl;

  
  float ri_block1;

  float ri_block2;


  
 
  float TestOffset;
  
 
  float Wanddicke_MS;

  
 
  float Startmesswert;
  
 
  float Messwertdifferenz;          
 
  
};



 
struct Axialgeruest_Regelung
{
	
 
    float Sollaxialwanddicke;
    
 
    float psi;
    
 
    float Wanddicke_axial_soll[20];
    
 
    float Wanddicke_axial_Hilf[20];
    
 
    float Wanddicke_axial_Aussensegment;
    
    
 
    int Aufrufzeit_Regelzykl;

    
 
    float Sprunghoehe;                              
    
 
    float Haltezeit;                                
    
    
 
    float wanddicke_hilf;

};




#line 45 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\IBF_struct.hpp"
#line 1 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\IBF_formenspek.hpp"


















 





 






 
 
 



struct Formenspektrum
{
 int Profilflag;
 float t_U_Viola;	
 float delta_s_Viola; 
 float t_Halte;  
 float proz_s;   
 float Soll_RS_Pos_end;
 float epsilon;  
};


#line 46 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\IBF_struct.hpp"
#line 1 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\ibf_Schuessel.hpp"
#line 1 "c:\\rm3dev\\inc\\time.h"






















 




#line 34 "c:\\rm3dev\\inc\\time.h"


#line 51 "c:\\rm3dev\\inc\\time.h"





            
            
#pragma fixedparams ("gmtime", "localtime", "ctime")
#pragma fixedparams ("asctime", "tzset", "difftime")
#pragma fixedparams ("mktime", "strftime", "x_cr_time")
#pragma fixedparams ("clock" ,"sleep")
#pragma fixedparams ("_xdaylight", "_xtimezone", "_xtzname" )
#pragma fixedparams ("x_cr_svc_time", "x_cr_svc_stime")

#pragma align (tm = 4)
















 
struct tm {
  int tm_sec;    
  int tm_min;    
  int tm_hour;   
  int tm_mday;   
  int tm_mon;    
  int tm_year;   
  int tm_wday;   
  int tm_yday;   
  int tm_isdst; 
 
};

typedef long time_t;     



extern "C" {


extern char      *  far asctime    (const struct tm *tm);
extern long         far clock      (void);
extern char      *  far ctime      (time_t *sincebot);
extern double       far difftime   (time_t t1, time_t t0);
extern struct tm *  far gmtime     (time_t *sincebot);
extern struct tm *  far localtime  (time_t *sincebot);
extern time_t       far mktime     (struct tm *tm);
extern unsigned     far sleep      (unsigned secs);
extern size_t       far strftime   (char *s, size_t maxsize, char *fmtstr, struct tm *tm);
extern void         far tzset      (void);

extern time_t       far x_cr_time  (time_t *ptr);
extern int       *  far _xdaylight (void);
extern long      *  far _xtimezone (void);
extern char     **  far _xtzname   (void);

extern void         far x_cr_svc_time  (int fmt_type, void *timeInfo, unsigned int *sts);
extern void         far x_cr_svc_stime (int fmt_type, void *timeInfo, unsigned int *sts);


}
























#line 2 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\ibf_Schuessel.hpp"




















 




 




  

  
  
  
 

  


 


  

 


  
 

 
  

 


  

 


  
 

   
 

  

 


  

 


  
 


  
 


 
  
 



  


 

  



 

  


 

  




 

  




 





  

 
  struct Def_IBF_Schuessel{
  
    

 
    int ringKlettert;

    

 
    int abbruchRinghoehenDifferenz;

	

 
	int ringDurchmesserKlettern;
    
    
 
    int zentrierrollenOffen;

	
 
	int endWandhoehe_Schuessel;

  };
  	



  class ibf_Schuessel
  {

      friend class Schuessel_Test;

      public:


        void static Main(
                  struct Def_IBF_Allgemein_IST Ist_IBF,
                  struct Def_IBF_Allgemein_SOLL *Soll_IBF,
                  struct Def_Ist_Inter Ist_Inter,																	    	
                  struct Def_Soll_Inter *Soll_Inter);

  		private:


        static void radialSchlittenAnfahren(
                struct Def_IBF_Allgemein_IST Ist_IBF,
                struct Def_IBF_Allgemein_SOLL *Soll_IBF,
                struct Def_Ist_Inter Ist_Inter,
                struct Def_Soll_Inter *Soll_Inter);

        static void axialGeruestAnfahren(
                struct Def_IBF_Allgemein_IST Ist_IBF,
                struct Def_IBF_Allgemein_SOLL *Soll_IBF,
                struct Def_Ist_Inter Ist_Inter,
                struct Def_Soll_Inter *Soll_Inter);

        static void axialSchlittenAnfahren(	
								struct Def_IBF_Allgemein_IST Ist_IBF,
								struct Def_IBF_Allgemein_SOLL *Soll_IBF,
								struct Def_Ist_Inter Ist_Inter,
								struct Def_Soll_Inter *Soll_Inter);


    	  static int berechneRingdurchmesser(	
                struct Def_IBF_Allgemein_IST *Ist_IBF,
								struct Def_Ist_Inter Ist_Inter);

    		static void steuerungZentrierrollen( 
                struct Def_IBF_Allgemein_IST Ist_IBF,
                struct Def_IBF_Allgemein_SOLL *Soll_IBF,
                struct Def_Ist_Inter Ist_Inter,
                struct Def_Soll_Inter *Soll_Inter);

    		static void zentrierRollenOeffnen(
								struct Def_IBF_Allgemein_IST *Ist_IBF,
                struct Def_IBF_Allgemein_SOLL *Soll_IBF,
                struct Def_Ist_Inter Ist_Inter);


    		static void zentrierRollenSchliessen(  
								struct Def_IBF_Allgemein_IST *Ist_IBF,
                struct Def_IBF_Allgemein_SOLL *Soll_IBF,
                struct Def_Ist_Inter Ist_Inter);


    		static int zentrierrollenPositionBerechnen(
								struct Def_Ist_Inter Ist_Inter,
                int armseite,
                int offset,
                int oeffnen);

    		static int berechneAlpha(  
								struct Def_Ist_Inter,
                int offset,
                int armseite);

    		static int berechneBeta1(
								struct Def_Ist_Inter Ist_Inter, 
                int armseite);

    		static int berechneBeta2(  
								struct Def_Ist_Inter Ist_Inter,
                int offset,
                int armseite);

    		static int berechneBeta3(
								struct Def_Ist_Inter Ist_Inter,
								int offset,
                int armseite);

    		static int berechneBeta4(
								struct Def_Ist_Inter Ist_Inter,
                int armseite);

    		static int ringKlettert(
							struct Def_IBF_Allgemein_IST *Ist_IBF,
              struct Def_Ist_Inter Ist_Inter);
	
       					      
  };

#line 47 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\IBF_struct.hpp"

    
  
 
 
    


 
    struct IBF_Testfahrt
    {
    	
 
      int Flag;
      
 
      float Ring_AD;
    };
 
    

 
    struct Geometrie
    {
      
 
      float D_Null;              
      
 
      float Wandstaerke_Null;    
      
 
      float Start_Ringhoehe;     
    };


    



 
    struct IBF_Flag
    {
    	
 
      int rs_kraftregler_aktiv;
      
 
      int as_kraftregler_aktiv;

      
 
      int ag_kraftregler_aktiv;
      
 
      int zal_kraftregler_aktiv;
      
 
      int zar_kraftregler_aktiv;

      
 
      int rs_kraftanfahren_aktiv;
      
 
      int as_kraftanfahren_aktiv;

      
 
      int as_kraft_anfahren_erreicht;
      
 
      int rs_kraft_anfahren_erreicht;  

      
 
      int ag_mode;                 






 
      int ag_act;

      
 
      int aso_mode;

      
 
      int rs_mode;

      
 
      int Axial_Radialwalzen;     
 
      
 
      int IBF_Abschaltung;        

      
 
      int AG_Start_erreicht;
      

 
      int Bissverhaeltnis;       
      
      


 
      int DA_Jenkouk_DW_Regelung;
      
      
 
      int DA_Jenkouk_Messen_ohne_Fahren; 
       
      
      
 
      int DA_Jenkouk_AG_Analyse;       

    };

    
 
    struct Def_Zeit
    {
    	
 
        float Ringumdrehung;
        
 
        float Halbe_Ringumdrehung;
        

 
        float t_Halte;
    };


 

 
 
 





 
struct Def_IBF_Allgemein_IST
{

	

 
	int debug_InnerSwitchCase;

         
         
         
         
         

        
 
		int counter;

		
 
		int countDebug;
 
      

    	

 
        int StartPos;
        
 
        char ManAuswahl;

        
 
        int  Profilflag;
        
 
        char InitAchse;
        

 
        short InitAchse_gecastet;
        
 
        char ExitAchse;
    
     
        
 
        float FR;
        
 
        float FA;
        
 
        float FR_f;
        
 
        float FA_f;
    
     
        
 
        float RS_Pos;
        
 
        float AG_Pos;
        
 
        float ASO_Pos;
        
 
        float TR_Pos;
        
 
        float ZAR_Pos;
        
 
        float ZAL_Pos;
        
     






     

        
 
        float RS_Pos_Null;
        
 
        float ASO_Pos_Null;
        
 
        float AG_Pos_Null;
        
 
        float RS_Pos_Start;
        
 
        float AG_Pos_Start;
        
 
        float ASO_Pos_Start;
        
        



 
        float ASO_Pos_Differenz;    

    
      
       
        
 
       float Wanddicke_Ist;
       
 
       float Rohling_h_angefahren;
       
 
       float Rohling_s_angefahren;
       
  
       float da;
       
 
       float di;


     
     
     

     
        
     struct IBF_Flag Flag;

     
     
     
     
     
     
        
     
     
    
     
    
    

  
    float delta_tr;


     
        
 
        struct Geometrie Vorring;

     
        
 
    float eps_Vorschub; 
    
    
    
 
    struct Def_Zeit Zeit;

     

    

 
    struct Radial_Flex_Prof Radial;
    

 
    struct Axial_Flex_Prof Axial;
	  
 
    struct Formenspektrum Formen;

     
     
     
     
     
    
    
 
    struct stuetzstellen_var stuetz_var;
    

 
    struct Def_DW_Regelung_DA_Jenkouk DW_Regelung;
    

 
    struct Axialgeruest_Regelung AG_Regelung;        
   
    


 
    struct Def_IBF_Schuessel IBF_Schuessel;

    struct IBF_Testfahrt Test;


};











 
struct Def_IBF_Allgemein_SOLL
{





   
    		 
	
 
    int  Profilflag;
    
 
    char InitAchse;
    
 
    char ExitAchse;

    
     
    
    
     
    
 
    float RS_Kraft;
    
 
    float AS_Kraft;
    
 
    float AG_Kraft;
    
 
    float ZAL_Kraft;
    
 
    float ZAR_Kraft;

     
    
 
    float RS_Pos;
    
 
    float ASO_Pos;
    
 
    float AG_Pos;
    
    
 
    float ZAR_Pos;
    
 
    float ZAL_Pos;

    
 
    float RS_Pos_end;

    
 
    float min_RS_Pos;
    
 
    float min_ASO_Pos;
    
  
    float tr_pos;
    

 
    float delta_tr;

     
    
 
    float RS_V;
    
 
    float ASO_V;
    
 
    float AG_V;
    
 
    float ZAR_V;
    
 
    float ZAL_V;

     
    
 
    float RS_Pos_Null;
    
 
    float RS_Pos_Start;
    
 
    float Soll_RS_Pos_end;  

    
 
    float Soll_ASO_Pos_alt;
    
 
    float ASO_Pos_Null;
    
 
    float ASO_Pos_Start;

    
    float AG_Pos_Null;
    
 
    float AG_Pos_Start;

     
    
    
    
 
    struct Def_Zeit Zeit;


     

    
 
    float Rohling_h_angefahren;
    
 
    float Rohling_s_angefahren;
    


     
     
     

     
    
 
    struct IBF_Flag Flag;

    
    
 
    struct Radial_Flex_Prof Radial;
    
 
    struct Axial_Flex_Prof Axial;
    
 
    struct Formenspektrum Formen;
    
 
    struct stuetzstellen_var stuetz_var;   
    	

    
     
    
 
     float RS_Kraft_Vorgabe;
     
 
     float AS_Kraft_Vorgabe;
     
 
     float AG_Kraft_Vorgabe;
     
 
     float ZAR_Kraft_Vorgabe;
     
 
     float ZAL_Kraft_Vorgabe;
     
 
     float RS_Kraft_Anfahren;
     
 
     float AS_Kraft_Anfahren;
 
    
    
     

     
  
    
   
     





    
 
    float Soll_ASU_Pos;
    
 
    float Soll_ASU_V;
  

     
     
     
     
     
    

  
    struct Def_DW_Regelung_DA_Jenkouk DW_Regelung;
    

 
    struct Axialgeruest_Regelung AG_Regelung;

    


 
    struct Def_IBF_Schuessel IBF_Schuessel;
};




#line 45 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\rpw.hpp"
#line 1 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\ibf_Schuessel.hpp"





















 




 

#line 46 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\rpw.hpp"



 
 
 
   



 
   struct Testfahrt
    {
	   

 
        int Flag;                
        

 
        float Ring_AD;           
    };



 
   struct Rohling
   {
	   
 
	   float sm;
	   
 
	   float hm;
	   
 
	   float da;
   };

   


 
    struct Antriebe
    {
	   
 
        float ma_ist;
        
 
        float ma_soll;                

    };

 
    



 
    struct Def_Werkzeug_Zentrierarm_Rolle
    {
      


 
      int dist_Hauptwalze_SenkrechteZentrierarmfixpunkt;

      
 
      int durchmesser_zr;

      

 
      int dist_Mittelachse_Zentrierarmfixpunkt;

      

 
      int dist_Kolbenende_Zentrierarmfixpunkt;

      

 
      int dist_Fixpunkt_Zentrierrolle;

      

 
      int dist_Kolben_Zentrierarm;

      

 
      int dist_Kolbenende_Zentrierrolle;

      

 
      int dist_Mittelachse_Kolbenfixpunkt;


    };

    



 
    struct Werkzeug
    {
    	
 
        float Durchmesser_HW;
        
 
        float Durchmesser_DW;
        
 
        float Winkelgeschw_omega_HW;
        
 
        float Drehzahl_HW;
        
 
        float tU_HW;
        
 
        float Winkel_grad_tU_HW;
        
 
        float U_v_HW;

        
 
        float Ringumdrehung;
        
 
        float omega_Ring;
        
 
        float Winkel_grad_tU_Ring;


        
 
        float l_fehlende_spitze;

        
 
        struct Antriebe Antrieb_ASO;
        
 
        struct Antriebe Antrieb_ASU;   

        


 
        struct Def_Werkzeug_Zentrierarm_Rolle werkzeug_zr;

        


 
        struct Def_Werkzeug_Zentrierarm_Rolle werkzeug_zl;


        
    };



    










 
   struct Def_Ist_Inter
   {  
      
 
      double Systemzeit;
    	 
    	
 
    	float rs_pos;
    	
 
    	float aso_pos;
    	
 
    	float asu_pos;
    	
 
    	float ag_pos;
    	
 
    	float zal_pos;
    	
 
    	float zar_pos;
    	
 
    	float tr_pos;

    	 
    	
 
    	float rs_soll;
    	
 
    	float aso_soll;
    	
 
    	float asu_soll;
    	
 
    	float ag_soll;
    	
 
    	float zal_soll;
    	
 
    	float zar_soll;          


       
    	
 
    	float rs_f;
    	
 
    	float as_f;
    	
 
    	float ag_f;
    	
 
    	float	zal_fx;
    	
 
    	float	zal_fy;
    	
 
    	float zal_f;
    	
 
    	float zar_fx;
    	
 
    	float zar_fy;
    	
 
    	float zar_f;


       
    	
 
    	float hw_i;
    	
 
    	float kwo_i;
    	
 
    	float kwu_i;


       
    	
 
    	float hw_n;           
    	
 
    	float kwo_n;          
    	
 
    	float kwu_n;          

    	
 
    	float n_hw_motor_ist;
    	
 
    	float n_kwo_motor_ist;
    	
 
    	float n_kwu_motor_ist;

    	 
    	unsigned char poti_kw_n_255;                    
    	unsigned char poti_za_d_255;                    

    	unsigned char poti_vrelproz_255;                
    	unsigned char poti_endphase_255;                

    	unsigned char poti_hand_r_255;                  
    	unsigned char poti_dpmax_255;                   

    	unsigned char poti_fz_255;                      
    	unsigned char poti_hand_a_255;                  

    	unsigned char poti_kw_n_oben_unten_255;         
    	unsigned char poti_reserve_255;                 


    	 
    	short taster_poti_kw_n;                 
    	short taster_poti_za_d;                 

    	short taster_poti_vrelproz;            
    	short taster_abschaltung_aus;          

    	short taster_poti_hand_r;              
    	short taster_power;                    

    	short taster_poti_fz;                  
    	short taster_poti_hand_a;              

    	short taster_poti_kw_n_oben_unten;     
    	short taster_poti_reserve;             

    	unsigned char poti_taster[2];                  

    	 
    	float za_x_abstand;      

       
    	
 
    	float da;
    	
    	float da_of;
    	
 
    	float di;
    	
    	float di_of;
    	
 
    	float dm;
    	
    	float dm_of;
    	
    	  
    	float fertig_ho_soll;
    	 
    	float fertig_wd_soll;
    	
 
    	float h0a;
    	
 
    	float h0r;
    	
 
    	float h1r;
    	
 
    	float h1a;
    	
    	float h1a_of;
    	
 
    	float s0a;
    	
 
    	float s0r;
    	
 
    	float s1a;
    	
 
    	float s1r;
    	
    	float s1r_of;
    	
 
    	float sfh;
    	
    	float skw;
    	
    	float skw_of;
    	
 
    	float wa_dvol;

    	 
    	
 
    	struct  Rohling Vorform;
    	
 
    	struct Werkzeug Werkzeug;
    		 
    	
 
    	float hw_ir;
    	
 
    	float kw_ia;

    	
 
    	float Ibf_Achse1;
    	
 
    	float Ibf_Achse2;
    	
 
    	float Ibf_Achse3;
    	
 
    	float Ibf_Achse4;

    	
 
    	float ag_pos_real;    

    	
 
    	struct Testfahrt Test;



    	
    	float h1a_o_of; 
    	float h1a_u_of; 

    	 
    	char  dummy[522];

    	
    	
   };

 
 
 











 
   struct Def_Soll_Inter
   { 
	   	   	    
	   
 
      float rs_v;
      
 
      float aso_v;
      
 
      float asu_v;
      
 
      float ag_v;
      
 
      float zal_v;
      
 
      float zar_v;


      	  	  	   
      
      
 
      float rs_pos;
      
 
      float aso_pos;
      
 
      float asu_pos;
      
 
      float ag_pos;
      
 
      float zal_pos;
      
 
      float zar_pos;
      		 	

      	  	  	  	   
      
 
      float hw_n;
      
 
      float kwo_n;
      
 
      float kwu_n;
      
      
 
      short schritt_nr;			
      
      
 
      float za_x_abstand;


      
 
      int   rs_kraftregler_aktiv;    
      
 
      int   aso_kraftregler_aktiv;
      
 
      int   asu_kraftregler_aktiv;
      
 
      int   ag_kraftregler_aktiv;
      
 
      int   zal_kraftregler_aktiv;
      
 
      int   zar_kraftregler_aktiv;


      
 
      float rs_kraft;
      
 
      float aso_kraft;
      
 
      float asu_kraft;
      
 
      float ag_kraft;
      
 
      float zal_kraft;
      
 
      float zar_kraft;

      
      int   ag_act;


      	  	   

      
 
      int   rs_mode;
      
 
      int   aso_mode;
      
 
      int   ag_mode;
      
 
      int   zen_mode;
   };

 
 
 

 
struct Def_Steuerbyte
{
	   




 
	   unsigned char modus;

	   








 
	   unsigned char freigabe;
};

int In_RWTH_LOG_Schreiben(char *buffer);

    



   class RPW
   {
      public:
        
		
 
        float  diam_dw;

        
        
        
 
        float  sin_kw_winkel_halbe;


        
 
        float offset_rs;
        
 
        float offset_agr;
        
 
        float offset_aso;
        
 
        float offset_asu;
        
 
        float offset_tr;	

      public:

      RPW();

      int Main_RAW(  int    ITER,
                     struct Def_Ein_Puff    Ein_Puff,
                     struct Def_Lokal_Puff  Lokal_Puff,
                     struct Def_Aus_Puff    Aus_Puff,
                     struct Def_Ein_Onli    Ein_Onli,
                     struct Def_Aus_Onli    Aus_Onli,
                     struct Def_Ist_Inter   *ist_inter,
                     struct Def_Soll_Inter  *soll_inter,
                     struct Def_IBF_Allgemein_SOLL *Soll_IBF,
                     struct Def_IBF_Allgemein_IST * Ist_IBF);


      int Istwerte_RAW(struct Def_Ein_Onli    Ein_Onli,
                       struct Def_Ein_Puff    Ein_Puff,
                       struct Def_Lokal_Puff  Lokal_Puff,
                       struct Def_Aus_Puff    Aus_Puff,
                       struct Def_Ist_Inter   *ist_inter);

      int IstIBF_IstInter(struct Def_Ist_Inter          Ist_Inter,
                          struct Def_IBF_Allgemein_IST  *Ist_IBF);


      int IstIBF_SollIBF(struct Def_IBF_Allgemein_SOLL  Soll_IBF,
                         struct Def_IBF_Allgemein_IST  *Ist_IBF);
                            

      int Main(struct Def_Ist_Inter          Ist_Inter,
               struct Def_IBF_Allgemein_IST  Ist_IBF, 
               struct Def_Soll_Inter         *Soll_Inter,
               struct Def_IBF_Allgemein_SOLL *Soll_IBF);


      
      int flexibel_Radial(struct Def_Ist_Inter          Ist_Inter,
                          struct Def_IBF_Allgemein_IST  Ist_IBF, 
                          struct Def_Soll_Inter         *Soll_Inter,
                          struct Def_IBF_Allgemein_SOLL *Soll_IBF);

      int flexibel_Axial(struct Def_Ist_Inter          Ist_Inter,
                         struct Def_IBF_Allgemein_IST  Ist_IBF, 
                         struct Def_Soll_Inter         *Soll_Inter,
                         struct Def_IBF_Allgemein_SOLL *Soll_IBF);

	  int formenspektrum(struct Def_Ist_Inter           Ist_Inter,
                       struct Def_IBF_Allgemein_IST   Ist_IBF,
					   struct Def_Soll_Inter          *Soll_Inter,
					   struct Def_IBF_Allgemein_SOLL  *Soll_IBF);

      
      int Modus_AG(struct Def_Soll_Inter        *Soll_Inter, 
                   struct Def_IBF_Allgemein_IST *Ist_IBF, 
                   int    Auswahl);

      int Kr_Geo_berechnen(struct Def_IBF_Allgemein_IST *Ist_IBF);
      int Kr_Geo_pruefen(struct Def_IBF_Allgemein_IST *Ist_IBF);

      int IBFPARA_auslesen(struct Def_IBF_Allgemein_IST *Ist_IBF, struct Def_IBF_Allgemein_SOLL *Soll_IBF, struct Def_Ist_Inter *Ist_Inter);

      

   };







#line 37 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\rwth_task.hpp"
   

#line 63 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\inc\\rwth_task.hpp"
      extern uint                    FlagId;
      extern RWTH_EXCH               *rwth_exch;
      extern LOGGER_RWTH             *Logger;
      
      extern Def_Ein_Puff            ein_puff;
      extern Def_Aus_Puff            aus_puff;
      extern Def_Ein_Onli            ein_onli;
      extern Def_Aus_Onli            aus_onli;
      extern Def_Lokal_Puff          lokal_puff;
      extern ofstream                MyLogFile;
      
      extern ulong                   TestCounter[20];
      
      extern RPW                            *rpw;
         
      extern int    iter_IBF;
      extern struct Def_Ist_Inter           Ist_Inter;
      extern struct Def_Soll_Inter          Soll_Inter;
      extern struct Def_IBF_Allgemein_SOLL  Soll_IBF;
      extern struct Def_IBF_Allgemein_IST   Ist_IBF;    
   
#line 29 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\source\\rwth_logger.cpp"



 
 
 
LOGGER_RWTH::LOGGER_RWTH(void)
{
    for(int i = 0; i < 300; i++)
    {
        TableLogRWTH[i].type = 0;
        TableLogRWTH[i].faktor = 0.0;
        TableLogRWTH[i].pAdresse = 0;
    }
}

 







 

int LOGGER_RWTH::Kanalliste(void)
{
#line 63 "C:\\rm3dev\\wagner\\raw\\RWTH_SMP\\RWTH_V109\\RWTH_SMP.bd\\source\\rwth_logger.cpp"
   
   

   
   TableLogRWTH[0].type     = 2;
   TableLogRWTH[0].faktor   = 0.0;
   TableLogRWTH[0].pAdresse = (void *)rwth_exch->get_pCountBlinker();

   
   TableLogRWTH[1].type     = 2;
   TableLogRWTH[1].faktor   = 0.0;
   TableLogRWTH[1].pAdresse = (void *)rwth_exch->get_pBlinker();

   
   TableLogRWTH[2].type     = 2;   
   TableLogRWTH[2].faktor   = 0.0;   
   TableLogRWTH[2].pAdresse = (void *)&TestCounter[0];

   
   TableLogRWTH[3].type     = 2;   
   TableLogRWTH[3].faktor   = 0.0;   
   TableLogRWTH[3].pAdresse = (void *)&TestCounter[1];

   
   TableLogRWTH[4].type     = 1;   
   TableLogRWTH[4].faktor   = 0.0;   
   TableLogRWTH[4].pAdresse = (void *)&iter_IBF; 

   
   TableLogRWTH[5].type     = 1;   
   TableLogRWTH[5].faktor   = 0.0;   
   TableLogRWTH[5].pAdresse = (void *)&Soll_IBF.Profilflag;

   
   TableLogRWTH[6].type     = 1;   
   TableLogRWTH[6].faktor   = 0.0;   
   TableLogRWTH[6].pAdresse = (void *)&Ist_IBF.Profilflag;

   
   TableLogRWTH[7].type     = 1;   
   TableLogRWTH[7].faktor   = 0.0;   
   TableLogRWTH[7].pAdresse = (void *)&Ist_IBF.InitAchse_gecastet;

   
   TableLogRWTH[8].type     = 1;   
   TableLogRWTH[8].faktor   = 0.0;   
   TableLogRWTH[8].pAdresse = (void *)&Ist_IBF.InitAchse;

   
   TableLogRWTH[9].type     = 3;   
   TableLogRWTH[9].faktor   = 1000.0;   
   TableLogRWTH[9].pAdresse = (void *)&Ist_IBF.FR;

   
   TableLogRWTH[10].type     = 3;   
   TableLogRWTH[10].faktor   = 1000.0;   
   TableLogRWTH[10].pAdresse = (void *) &aus_onli.ds_dh_sp_hp.s_punkt;
   
   
   TableLogRWTH[11].type     = 3;   
   TableLogRWTH[11].faktor   = 1000.0;   
   TableLogRWTH[11].pAdresse = (void *)&Soll_IBF.RS_Kraft;

   
   TableLogRWTH[12].type     = 3;   
   TableLogRWTH[12].faktor   = 1000.0;   
   TableLogRWTH[12].pAdresse = (void *)&Ist_IBF.FA;

   
   TableLogRWTH[13].type     = 3;   
   TableLogRWTH[13].faktor   = 1000.0;   
   TableLogRWTH[13].pAdresse = (void *)&Soll_IBF.AS_Kraft;

   
   TableLogRWTH[14].type     = 3;   
   TableLogRWTH[14].faktor   = 100.0;   
   TableLogRWTH[14].pAdresse = (void *)&Ist_IBF.Zeit.Ringumdrehung;

   
   TableLogRWTH[15].type     = 3;   
   TableLogRWTH[15].faktor   = 100.0;   
   TableLogRWTH[15].pAdresse = (void *)&Soll_IBF.min_ASO_Pos;

   
   TableLogRWTH[16].type     = 3;   
   TableLogRWTH[16].faktor   = 1000.0;   
   TableLogRWTH[16].pAdresse = (void *)&Soll_IBF.RS_V;

   
   TableLogRWTH[17].type     = 3;   
   TableLogRWTH[17].faktor   = 1000.0;   
   TableLogRWTH[17].pAdresse = (void *)&Soll_IBF.ASO_V;

   
   TableLogRWTH[18].type     = 3;   
   TableLogRWTH[18].faktor   = 1000.0;   
   TableLogRWTH[18].pAdresse = (void *)&Soll_IBF.AG_V;

   
   TableLogRWTH[19].type     = 3;   
   TableLogRWTH[19].faktor   = 100.0;   
   TableLogRWTH[19].pAdresse = (void *)&Soll_IBF.RS_Pos;

   
   TableLogRWTH[20].type     = 3;   
   TableLogRWTH[20].faktor   = 100.0;   
   TableLogRWTH[20].pAdresse = (void *)&Soll_IBF.RS_Pos_end;

   
   TableLogRWTH[21].type     = 3;   
   TableLogRWTH[21].faktor   = 100.0;   
   TableLogRWTH[21].pAdresse = (void *)&Ist_IBF.RS_Pos;

   
   TableLogRWTH[22].type     = 3;   
   TableLogRWTH[22].faktor   = 100.0;   
   TableLogRWTH[22].pAdresse = (void *)&Soll_IBF.ASO_Pos;

   
   TableLogRWTH[23].type     = 3;   
   TableLogRWTH[23].faktor   = 100.0;   
   TableLogRWTH[23].pAdresse = (void *)&Ist_IBF.ASO_Pos;

   
   TableLogRWTH[24].type     = 3;   
   TableLogRWTH[24].faktor   = 100.0;   
   TableLogRWTH[24].pAdresse = (void *)&Soll_IBF.AG_Pos;

   
   TableLogRWTH[25].type     = 3;   
   TableLogRWTH[25].faktor   = 100.0;   
   TableLogRWTH[25].pAdresse = (void *)&Ist_IBF.AG_Pos;

   
   TableLogRWTH[26].type     = 3;   
   TableLogRWTH[26].faktor   = 1000.0;   
   TableLogRWTH[26].pAdresse = (void *)&Soll_IBF.AG_Kraft;

   
   TableLogRWTH[27].type     = 3;   
   TableLogRWTH[27].faktor   = 1000.0;   
   TableLogRWTH[27].pAdresse = (void *)&Ist_Inter.ag_f;

   
   TableLogRWTH[28].type     = 3;   
   TableLogRWTH[28].faktor   = 1000.0;   
   TableLogRWTH[28].pAdresse = (void *)&aus_onli.ds_dh_sp_hp.h_punkt;
   
   
   TableLogRWTH[29].type     = 3;   
   TableLogRWTH[29].faktor   = 100.0;   
   TableLogRWTH[29].pAdresse = (void *)&Soll_IBF.Zeit.t_Halte;

   
   TableLogRWTH[30].type     = 3;   
   TableLogRWTH[30].faktor   = 100.0;   
   TableLogRWTH[30].pAdresse = (void *)&Soll_IBF.Radial.delta_h;

   
   TableLogRWTH[31].type     = 3;   
   TableLogRWTH[31].faktor   = 100.0;   
   TableLogRWTH[31].pAdresse = (void *)&Soll_IBF.Radial.delta_s;

   
   TableLogRWTH[32].type     = 3;   
   TableLogRWTH[32].faktor   = 100.0;   
   TableLogRWTH[32].pAdresse = (void *)&Soll_IBF.Radial.abnahme_s;

   
   TableLogRWTH[33].type     = 3;   
   TableLogRWTH[33].faktor   = 100.0;   
   TableLogRWTH[33].pAdresse = (void *)&Soll_IBF.Radial.Soll_Wanddicke;

   
   TableLogRWTH[34].type     = 3;   
   TableLogRWTH[34].faktor   = 100.0;   
   TableLogRWTH[34].pAdresse = (void *)&Ist_IBF.Radial.s_f;

   
   TableLogRWTH[35].type     = 3;   
   TableLogRWTH[35].faktor   = 100.0;   
   TableLogRWTH[35].pAdresse = (void *)&Ist_IBF.Radial.s_f_alt;

   
   TableLogRWTH[36].type     = 3;   
   TableLogRWTH[36].faktor   = 100.0;   
   TableLogRWTH[36].pAdresse = (void *)&Ist_IBF.Radial.Anfangsposition_DW;

   
   TableLogRWTH[37].type     = 3;   
   TableLogRWTH[37].faktor   = 1000.0;   
   TableLogRWTH[37].pAdresse = (void *)&Soll_IBF.Radial.Vorschubgeschw_Dw;

   
   TableLogRWTH[38].type     = 3;   
   TableLogRWTH[38].faktor   = 1000.0;   
   TableLogRWTH[38].pAdresse = (void *)&Soll_IBF.Radial.dw_vn;
   
   
   TableLogRWTH[39].type     = 3;   
   TableLogRWTH[39].faktor   = 100.0;   
   TableLogRWTH[39].pAdresse = (void *)&Soll_IBF.Radial.t_dis_h;
   
   
   TableLogRWTH[40].type     = 0;   
   TableLogRWTH[40].faktor   = 0.0;   
   TableLogRWTH[40].pAdresse = 0;
   
   
   TableLogRWTH[41].type     = 3;   
   TableLogRWTH[41].faktor   = 100.0;   
   TableLogRWTH[41].pAdresse = (void *)&Ist_Inter.Werkzeug.Drehzahl_HW;
   
   
   TableLogRWTH[42].type     = 3;   
   TableLogRWTH[42].faktor   = 100.0;   
   TableLogRWTH[42].pAdresse = (void *)&Ist_Inter.Werkzeug.Durchmesser_HW;
   
   
   TableLogRWTH[43].type     = 1;   
   TableLogRWTH[43].faktor   = 0.0;   
   TableLogRWTH[43].pAdresse = (void *)&Soll_IBF.Flag.ag_act;
   
   
   TableLogRWTH[44].type     = 1;   
   TableLogRWTH[44].faktor   = 0.0;   
   TableLogRWTH[44].pAdresse = (void*)&aus_onli.Ibf_nominal.AG_act;
   
   
   TableLogRWTH[45].type     = 1;   
   TableLogRWTH[45].faktor   = 0.0;   
   TableLogRWTH[45].pAdresse = (void*)&Soll_IBF.Flag.ag_mode;
   
   
   TableLogRWTH[46].type     = 1;   
   TableLogRWTH[46].faktor   = 0.0;   
   TableLogRWTH[46].pAdresse = (void*)&aus_onli.Ibf_nominal.AG_mode;
   
   
   TableLogRWTH[47].type     = 1;   
   TableLogRWTH[47].faktor   = 0.0;   
   TableLogRWTH[47].pAdresse = (void*)&aus_onli.Ibf_nominal.AG_mode;
   
   
   TableLogRWTH[48].type     = 3;   
   TableLogRWTH[48].faktor   = 100.0;   
   TableLogRWTH[48].pAdresse = (void *)&Soll_Inter.aso_pos;
   
   
   TableLogRWTH[49].type     = 3;   
   TableLogRWTH[49].faktor   = 100.0;   
   TableLogRWTH[49].pAdresse = (void *)&Ist_Inter.aso_pos;
   
   
   TableLogRWTH[50].type     = 3;   
   TableLogRWTH[50].faktor   = 100.0;   
   TableLogRWTH[50].pAdresse = (void*)&Soll_IBF.Radial.Cr.a;
   
   
   TableLogRWTH[51].type     = 3;   
   TableLogRWTH[51].faktor   = 100.0;   
   TableLogRWTH[51].pAdresse = (void*)&Soll_IBF.Radial.Cr.b;
   
   
   TableLogRWTH[52].type     = 3;   
   TableLogRWTH[52].faktor   = 100.0;   
   TableLogRWTH[52].pAdresse = (void*)&Soll_IBF.Radial.Cr.c;
   
   
   TableLogRWTH[53].type     = 3;   
   TableLogRWTH[53].faktor   = 100.0;   
   TableLogRWTH[53].pAdresse = (void*)&Soll_IBF.Radial.Cr.d;
   
   
   TableLogRWTH[54].type     = 3;   
   TableLogRWTH[54].faktor   = 1000.0;   
   TableLogRWTH[54].pAdresse = (void*)&Soll_IBF.Radial.Cr.e;
   
   
   TableLogRWTH[55].type     = 3;   
   TableLogRWTH[55].faktor   = 1000.0;   
   TableLogRWTH[55].pAdresse = (void*)&Soll_IBF.Radial.Cr.o;
   
   
   TableLogRWTH[56].type     = 3;   
   TableLogRWTH[56].faktor   = 1000.0;   
   TableLogRWTH[56].pAdresse = (void*)&Soll_IBF.Radial.Cr.u;
   
   
   TableLogRWTH[57].type     = 3;   
   TableLogRWTH[57].faktor   = 1000.0;   
   TableLogRWTH[57].pAdresse = (void*)&Soll_IBF.Radial.Cr.g;
   
   
   TableLogRWTH[58].type     = 3;   
   TableLogRWTH[58].faktor   = 1000.0;   
   TableLogRWTH[58].pAdresse = (void*)&Soll_IBF.Radial.Cr.f;
   
   
   TableLogRWTH[59].type     = 1;   
   TableLogRWTH[59].faktor   = 0;   
   TableLogRWTH[59].pAdresse = (void*)&Soll_IBF.Radial.Cr.os_i;
   
   
   TableLogRWTH[60].type     = 3;   
   TableLogRWTH[60].faktor   = 100.0;   
   TableLogRWTH[60].pAdresse = (void*)&Soll_IBF.Radial.Cr.Array[0];
   
   
   TableLogRWTH[61].type     = 3;   
   TableLogRWTH[61].faktor   = 100.0;   
   TableLogRWTH[61].pAdresse = (void*)&Soll_IBF.Radial.Cr.Array[1];
   
   
   TableLogRWTH[62].type     = 3;   
   TableLogRWTH[62].faktor   = 100.0;   
   TableLogRWTH[62].pAdresse = (void*)&Ist_IBF.ASO_Pos_Start;
   
   
   TableLogRWTH[63].type     = 3;   
   TableLogRWTH[63].faktor   = 100.0;   
   TableLogRWTH[63].pAdresse = (void*)&Ist_IBF.Rohling_s_angefahren;
   
   
   TableLogRWTH[64].type     = 3;   
   TableLogRWTH[64].faktor   = 100.0;   
   TableLogRWTH[64].pAdresse = (void*)&Ist_IBF.Rohling_h_angefahren;



   

   
   
   TableLogRWTH[70].type     = 3;   
   TableLogRWTH[70].faktor   = 1000.0;   
   TableLogRWTH[70].pAdresse = (void*)&Ist_Inter.da;

   
   TableLogRWTH[71].type     = 3;   
   TableLogRWTH[71].faktor   = 1000.0;   
   TableLogRWTH[71].pAdresse = (void*)&Ist_Inter.di;
   
   
   TableLogRWTH[72].type     = 3;   
   TableLogRWTH[72].faktor   = 1000.0;   
   TableLogRWTH[72].pAdresse = (void*)&Ist_Inter.s1r;
   
   
   TableLogRWTH[73].type     = 3;   
   TableLogRWTH[73].faktor   = 1000.0;   
   TableLogRWTH[73].pAdresse = (void*)&Ist_Inter.h1a_of;
  
   


   
   TableLogRWTH[100].type     = 3;   
   TableLogRWTH[100].faktor   = 1.0;   
   TableLogRWTH[100].pAdresse = (void*)&Ist_IBF.Axial.Verh_pr_sf_proz_start;

   
   TableLogRWTH[101].type     = 3;   
   TableLogRWTH[101].faktor   = 1.0;   
   TableLogRWTH[101].pAdresse = (void*)&Ist_IBF.Axial.Verh_pr_sf_proz;

   
   TableLogRWTH[102].type     = 2;   
   TableLogRWTH[102].faktor   = 0.0;   
   TableLogRWTH[102].pAdresse = (void*)&Ist_IBF.Axial.Pr_Num;

   
   TableLogRWTH[103].type     = 3;   
   TableLogRWTH[103].faktor   = 100.0;   
   TableLogRWTH[103].pAdresse = (void*)&Soll_Inter.kwo_n;

   
   TableLogRWTH[104].type     = 3;   
   TableLogRWTH[104].faktor   = 100.0;   
   TableLogRWTH[104].pAdresse = (void*)&Soll_Inter.kwu_n;

   
   TableLogRWTH[105].type     = 3;   
   TableLogRWTH[105].faktor   = 100.0;   
   TableLogRWTH[105].pAdresse = (void*)&Ist_Inter.kwo_n;
   
   
   TableLogRWTH[106].type     = 3;   
   TableLogRWTH[106].faktor   = 100.0;   
   TableLogRWTH[106].pAdresse = (void*)&Ist_Inter.kwu_n;

   
   TableLogRWTH[107].type     = 2;   
   TableLogRWTH[107].faktor   = 0.0;   
   TableLogRWTH[107].pAdresse = (void*)&Ist_IBF.Axial.Profilflag;

   
   TableLogRWTH[108].type     = 3;   
   TableLogRWTH[108].faktor   = 100.0;   
   TableLogRWTH[108].pAdresse = (void*)&Ist_IBF.Rohling_h_angefahren;

   
   TableLogRWTH[109].type     = 2;   
   TableLogRWTH[109].faktor   = 0.0;   
   TableLogRWTH[109].pAdresse = (void*)&Ist_IBF.Axial.Pr_Num;
  
   
   TableLogRWTH[110].type     = 3;   
   TableLogRWTH[110].faktor   = 100.0;   
   TableLogRWTH[110].pAdresse = (void*)&Ist_IBF.Axial.Pr_Tiefe[Ist_IBF.Axial.Pr_Num];

   
   TableLogRWTH[111].type     = 3;   
   TableLogRWTH[111].faktor   = 100.0;   
   TableLogRWTH[111].pAdresse = (void*)&Ist_IBF.Axial.AGR_Pr[Ist_IBF.Axial.Pr_Num];
  
   
   TableLogRWTH[112].type     = 3;   
   TableLogRWTH[112].faktor   = 1000.0;   
   TableLogRWTH[112].pAdresse = (void*)&Ist_IBF.Axial.Vorschub;
   
   
   TableLogRWTH[113].type     = 3;   
   TableLogRWTH[113].faktor   = 1000.0;   
   TableLogRWTH[113].pAdresse = (void*)&Ist_Inter.hw_n;

   
   TableLogRWTH[114].type     = 3;   
   TableLogRWTH[114].faktor   = 1000.0;   
   TableLogRWTH[114].pAdresse = (void*)&Ist_Inter.kwo_n;
   
   
   TableLogRWTH[115].type     = 3;   
   TableLogRWTH[115].faktor   = 1000.0;   
   TableLogRWTH[115].pAdresse = (void*)&Ist_Inter.kwu_n;
   
   
   TableLogRWTH[116].type     = 3;   
   TableLogRWTH[116].faktor   = 1000.0;   
   TableLogRWTH[116].pAdresse = (void*)&Soll_Inter.kwo_n;
   
   
   TableLogRWTH[117].type     = 3;   
   TableLogRWTH[117].faktor   = 1000.0;   
   TableLogRWTH[117].pAdresse = (void*)&Soll_Inter.kwu_n;

  
   TableLogRWTH[118].type     = 2;   
   TableLogRWTH[118].faktor   = 0.0;   
   TableLogRWTH[118].pAdresse = (void*)&Soll_IBF.Axial.Pr_Num;

   
   TableLogRWTH[119].type     = 3;   
   TableLogRWTH[119].faktor   = 100.0;   
   TableLogRWTH[119].pAdresse = (void*)&Soll_IBF.Axial.Pr_Tiefe[Ist_IBF.Axial.Pr_Num];

   
   TableLogRWTH[120].type     = 3;   
   TableLogRWTH[120].faktor   = 100.0;   
   TableLogRWTH[120].pAdresse = (void*)&Soll_IBF.Axial.AGR_Pr[Ist_IBF.Axial.Pr_Num];

   
   TableLogRWTH[200].type     = 3;   
   TableLogRWTH[200].faktor   = 1000.0;   
   TableLogRWTH[200].pAdresse = (void*)&Ist_Inter.hw_ir;

   
   TableLogRWTH[201].type     = 3;   
   TableLogRWTH[201].faktor   = 1000.0;   
   TableLogRWTH[201].pAdresse = (void*)&Ist_Inter.kw_ia;
   
   
   TableLogRWTH[210].type     = 3;   
   TableLogRWTH[210].faktor   = 1000.0;   
   TableLogRWTH[210].pAdresse = (void*)&Ist_Inter.n_hw_motor_ist; 
   
   
   TableLogRWTH[211].type     = 3;   
   TableLogRWTH[211].faktor   = 1000.0;   
   TableLogRWTH[211].pAdresse = (void*)&Ist_Inter.n_kwo_motor_ist;
   
   
   TableLogRWTH[212].type     = 3;   
   TableLogRWTH[212].faktor   = 1000.0;   
   TableLogRWTH[212].pAdresse = (void*)&Ist_Inter.n_kwu_motor_ist;

   
   
   TableLogRWTH[213].type     = 3;   
   TableLogRWTH[213].faktor   = 100.0;   
   TableLogRWTH[213].pAdresse = (void*)&Ist_Inter.ag_pos_real;

   
   TableLogRWTH[214].type     = 3;   
   TableLogRWTH[214].faktor   = 1000.0;   
   TableLogRWTH[214].pAdresse = (void*)&Ist_Inter.Werkzeug.Winkelgeschw_omega_HW;

   
   TableLogRWTH[215].type     = 3;   
   TableLogRWTH[215].faktor   = 1000.0;   
   TableLogRWTH[215].pAdresse = (void*)&Ist_Inter.Werkzeug.Winkel_grad_tU_HW;

   
   TableLogRWTH[216].type     = 3;   
   TableLogRWTH[216].faktor   = 1000.0;   
   TableLogRWTH[216].pAdresse = (void*)&Ist_Inter.Werkzeug.tU_HW;

    
   TableLogRWTH[217].type     = 3;   
   TableLogRWTH[217].faktor   = 1000.0;   
   TableLogRWTH[217].pAdresse = (void*)&Ist_Inter.Werkzeug.U_v_HW;

    
   TableLogRWTH[218].type     = 3;   
   TableLogRWTH[218].faktor   = 1000.0;   
   TableLogRWTH[218].pAdresse = (void*)&Ist_Inter.Werkzeug.Ringumdrehung;

    
   TableLogRWTH[219].type     = 3;   
   TableLogRWTH[219].faktor   = 1000.0;   
   TableLogRWTH[219].pAdresse = (void*)&Ist_Inter.Werkzeug.omega_Ring;

    
   TableLogRWTH[220].type     = 3;   
   TableLogRWTH[220].faktor   = 1000.0;   
   TableLogRWTH[220].pAdresse = (void*)&Ist_Inter.Werkzeug.Winkel_grad_tU_Ring;
   
    
   TableLogRWTH[221].type     = 1;   
   TableLogRWTH[221].faktor   = 0.0;   
   TableLogRWTH[221].pAdresse = (void*)&Ist_IBF.Test.Flag;

    
   TableLogRWTH[222].type     = 3;   
   TableLogRWTH[222].faktor   = 100.0;   
   TableLogRWTH[222].pAdresse = (void*)&Ist_IBF.Test.Ring_AD;

   
   TableLogRWTH[223].type     = 3;   
   TableLogRWTH[223].faktor   = 100.0;   
   TableLogRWTH[223].pAdresse = (void*)&Ist_Inter.tr_pos; 
   
   
   TableLogRWTH[224].type     = 3;   
   TableLogRWTH[224].faktor   = 100.0;   
   TableLogRWTH[224].pAdresse = (void*)&Ist_Inter.Ibf_Achse1; 
   
   
   TableLogRWTH[225].type     = 3;   
   TableLogRWTH[225].faktor   = 100.0;   
   TableLogRWTH[225].pAdresse = (void*)&Ist_Inter.Ibf_Achse2;
    
   
   
   TableLogRWTH[226].type     = 3;   
   TableLogRWTH[226].faktor   = 100.0;   
   TableLogRWTH[226].pAdresse = (void*)&Ist_Inter.Ibf_Achse3;


   
   TableLogRWTH[227].type     = 3;   
   TableLogRWTH[227].faktor   = 100.0;   
   TableLogRWTH[227].pAdresse = (void*)&Ist_Inter.Ibf_Achse4;
   
   
   
   TableLogRWTH[228].type     = 3;   
   TableLogRWTH[228].faktor   = 100.0;   
   TableLogRWTH[228].pAdresse = (void*)&ein_onli.rwg_poti_wert;

   
   
   
   
   
   TableLogRWTH[230].type     = 1;   
   TableLogRWTH[230].faktor   = 0.0;   
   TableLogRWTH[230].pAdresse = (void*)&Soll_IBF.stuetz_var.merker;

   
   TableLogRWTH[231].type     = 3;   
   TableLogRWTH[231].faktor   = 100.0;   
   TableLogRWTH[231].pAdresse = (void*)&Soll_IBF.stuetz_var.kontrollmerker; 
   
   
   TableLogRWTH[232].type     = 3;   
   TableLogRWTH[232].faktor   = 100.0;   
   TableLogRWTH[232].pAdresse = (void*)&Soll_IBF.stuetz_var.stellen[0][0]; 

   
   TableLogRWTH[233].type     = 3;   
   TableLogRWTH[233].faktor   = 100.0;   
   TableLogRWTH[233].pAdresse = (void*)&Soll_IBF.stuetz_var.stellen[1][19]; 

   
   TableLogRWTH[234].type     = 3;   
   TableLogRWTH[234].faktor   = 100.0;   
   TableLogRWTH[234].pAdresse = (void*)&Soll_IBF.stuetz_var.stellen[1][0];                  

   
   TableLogRWTH[235].type     = 3;   
   TableLogRWTH[235].faktor   = 100.0;   
   TableLogRWTH[235].pAdresse = (void*)&Soll_IBF.stuetz_var.crtimer;                  

   
   TableLogRWTH[236].type     = 3;   
   TableLogRWTH[236].faktor   = 100.0;   
   TableLogRWTH[236].pAdresse = (void*)&Soll_IBF.stuetz_var.skip_faktor;                  

   
   TableLogRWTH[237].type     = 3;   
   TableLogRWTH[237].faktor   = 100.0;   
   TableLogRWTH[237].pAdresse = (void*)&Soll_IBF.stuetz_var.stellen[1][5];                  

   
   TableLogRWTH[238].type     = 3;   
   TableLogRWTH[238].faktor   = 100.0;   
   TableLogRWTH[238].pAdresse = (void*)&Soll_IBF.stuetz_var.stellen[1][8];                  
   
   
   TableLogRWTH[239].type     = 3;   
   TableLogRWTH[239].faktor   = 100.0;   
   TableLogRWTH[239].pAdresse = (void*)&Ist_IBF.stuetz_var.ca;                  
   
   
   TableLogRWTH[240].type     = 3;   
   TableLogRWTH[240].faktor   = 100.0;   
   TableLogRWTH[240].pAdresse = (void*)&Soll_IBF.stuetz_var.delta_h;             


   
   
   
   TableLogRWTH[260].type     = 3;   
   TableLogRWTH[260].faktor   = 1000.0;   
   TableLogRWTH[260].pAdresse = (void*)&aus_onli.nutz_leistungsgrenzen.ma_nenn;             

   TableLogRWTH[261].type     = 3;   
   TableLogRWTH[261].faktor   = 1000.0;   
   TableLogRWTH[261].pAdresse = (void*)&aus_onli.nutz_leistungsgrenzen.ma_max;             

   TableLogRWTH[262].type     = 3;   
   TableLogRWTH[262].faktor   = 1000.0;   
   TableLogRWTH[262].pAdresse = (void*)&ein_puff.awo_motor.ueberlastung_p;            
   
   TableLogRWTH[263].type     = 3;   
   TableLogRWTH[263].faktor   = 1000.0;   
   TableLogRWTH[263].pAdresse = (void*)&ein_puff.awu_motor.ueberlastung_p;            

   TableLogRWTH[264].type     = 3;   
   TableLogRWTH[264].faktor   = 100.0;   
   TableLogRWTH[264].pAdresse = (void*)&aus_puff.n_omega.n_aw_motor_g_o;             

   TableLogRWTH[265].type     = 3;   
   TableLogRWTH[265].faktor   = 100.0;   
   TableLogRWTH[265].pAdresse = (void*)&aus_puff.n_omega.n_aw_motor_g_u;             

   TableLogRWTH[266].type     = 3;   
   TableLogRWTH[266].faktor   = 100.0;   
   TableLogRWTH[266].pAdresse = (void*)&ein_puff.awo_motor.n_nenn;                   

   TableLogRWTH[267].type     = 3;   
   TableLogRWTH[267].faktor   = 1000.0;   
   TableLogRWTH[267].pAdresse = (void*)&ein_puff.awo_motor.m_max;                   

    
   TableLogRWTH[268].type     = 3;   
   TableLogRWTH[268].faktor   = 100.0;   
   TableLogRWTH[268].pAdresse = (void*)&Soll_IBF.DW_Regelung.Wanddicke_berechnet;          

   TableLogRWTH[269].type     = 3;   
   TableLogRWTH[269].faktor   = 100.0;   
   TableLogRWTH[269].pAdresse = (void*)&Soll_IBF.DW_Regelung.Messwert_A_mf;                
   
   
   TableLogRWTH[270].type     = 3;   
   TableLogRWTH[270].faktor   = 100.0;   
   TableLogRWTH[270].pAdresse = (void*)&Soll_IBF.DW_Regelung.T_Einlauf;                   
   
   TableLogRWTH[271].type     = 3;   
   TableLogRWTH[271].faktor   = 100.0;   
   TableLogRWTH[271].pAdresse = (void*)&Soll_IBF.delta_tr;                               

   TableLogRWTH[272].type     = 3;   
   TableLogRWTH[272].faktor   = 100.0;   
   TableLogRWTH[272].pAdresse = (void*)&Soll_IBF.tr_pos;                                

   TableLogRWTH[273].type     = 3;   
   TableLogRWTH[273].faktor   = 100.0;   
   TableLogRWTH[273].pAdresse = (void*)&Ist_IBF.Axial.Biss.Verhaeltnis;                 
   
   TableLogRWTH[274].type     = 3;   
   TableLogRWTH[274].faktor   = 100.0;   
   TableLogRWTH[274].pAdresse = (void*)&Soll_IBF.DW_Regelung.Alpha;                 
   
   TableLogRWTH[275].type     = 3;   
   TableLogRWTH[275].faktor   = 100.0;   
   TableLogRWTH[275].pAdresse = (void*)&Soll_IBF.DW_Regelung.Beta;                 

   TableLogRWTH[276].type     = 3;   
   TableLogRWTH[276].faktor   = 100.0;   
   TableLogRWTH[276].pAdresse = (void*)&Soll_IBF.DW_Regelung.ri;                 

   TableLogRWTH[277].type     = 3;   
   TableLogRWTH[277].faktor   = 100.0;   
   TableLogRWTH[277].pAdresse = (void*)&Soll_IBF.AG_Regelung.Wanddicke_axial_Aussensegment;                 

   TableLogRWTH[278].type     = 3;   
   TableLogRWTH[278].faktor   = 100.0;   
   TableLogRWTH[278].pAdresse = (void*)&Soll_IBF.AG_Regelung.wanddicke_hilf;                 

   
   TableLogRWTH[279].type     = 3;   
   TableLogRWTH[279].faktor   = 100.0;   
   TableLogRWTH[279].pAdresse = (void*)&Soll_IBF.AG_Regelung.psi;                 


	
	
   TableLogRWTH[280].type     = 3;   
   TableLogRWTH[280].faktor   = 100.0;   
   TableLogRWTH[280].pAdresse = (void*)&Soll_IBF.stuetz_var.delta_s;             

   
   TableLogRWTH[281].type     = 3;   
   TableLogRWTH[281].faktor   = 100.0;   
   TableLogRWTH[281].pAdresse = (void*)&Ist_IBF.stuetz_var.cr;                  

   
   TableLogRWTH[282].type     = 3;   
   TableLogRWTH[282].faktor   = 100.0;   
   TableLogRWTH[282].pAdresse = (void*)&Soll_IBF.stuetz_var.stellen[0][9]; 

   
   TableLogRWTH[283].type     = 3;   
   TableLogRWTH[283].faktor   = 100.0;   
   TableLogRWTH[283].pAdresse = (void*)&Soll_IBF.stuetz_var.stellen[0][18]; 

	
   TableLogRWTH[284].type     = 3;   
   TableLogRWTH[284].faktor   = 100.0;   
   TableLogRWTH[284].pAdresse = (void*)&Ist_Inter.zar_f; 

 	
   TableLogRWTH[285].type     = 3;   
   TableLogRWTH[285].faktor   = 100.0;   
   TableLogRWTH[285].pAdresse = (void*)&Ist_Inter.zal_f; 
      
 	
   TableLogRWTH[286].type     = 1;   
   TableLogRWTH[286].faktor   = 0.0;   
   TableLogRWTH[286].pAdresse = (void*)&Ist_IBF.Flag.zar_kraftregler_aktiv; 

 	
   TableLogRWTH[287].type     = 1;   
   TableLogRWTH[287].faktor   = 0.0;   
   TableLogRWTH[287].pAdresse = (void*)&Ist_IBF.Flag.zal_kraftregler_aktiv;


   




   return ((~0));
}
