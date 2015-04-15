#ifndef _iniFile_h
#define _iniFile_h

//#include "rpw.hpp"
#include <string.h>
#include <vector>

#include <stdlib.h>

#ifdef _WIN32
	#include <stdarg.h> //va_list, va_start(), va_end()
	using namespace std;
#endif

#define MAX_KEYNAME    128
#define MAX_VALUENAME  128
#define MAX_VALUEDATA 2048

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
  float  GetValueF(string const keyname, string const valuename, double const defValue) const;

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

#endif // _iniFile_h
