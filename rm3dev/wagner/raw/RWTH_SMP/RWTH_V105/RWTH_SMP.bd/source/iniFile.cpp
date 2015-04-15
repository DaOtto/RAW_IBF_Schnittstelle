/*--FILE HEADER---------------------------------------------------------------
;   filename        : iniFile.hpp
;   version         : V1.0
;   contents        : Tool for IBF software 
;   author          : D. Michl, IBF RWTH Aachen
;   date            : October, 2006
;
;---FUNCTION AND ENVIRONMENT---------------------------------------------------
;
;   function:   iniFile.cpp allows reading of ASCII-Files, writen on 'Ini-File' format
;               Herewith the IBFPARA.ini should be readable ;               
;
;       RMOS3  Version 3.30
;       CAD-UL Version V120C
;
;---END OF  FILE HEADER------------------------------------------------------*/
/*--MODIFICATION HEADER--------------------------------------------------------
;   October , 21. 2006  0001  D.M.  original issue V1.0
;   
;
;---END OF MODIFICATION HEADER-----------------------------------------------*/


#include "ibf_tool.hpp"
#include "iniFile.h"




#if defined(WIN32)
#define iniEOL endl
#else
#define iniEOL '\r' << endl
#endif

CIniFile::CIniFile( string const iniPath)
{
  Path( iniPath);
  caseInsensitive = true;
}

bool CIniFile::ReadFile()
{

  //fstream f;
  ifstream f;
  string   line;
  string   keyname, valuename, value;
  string::size_type pLeft, pRight;
    
  
  
  f.open( path.c_str(), ios::in);
  if ( f.fail())
       return false;
    
  
  while( getline( f, line)) {

    if ( line[line.length() - 1] == '\r')
      line = line.substr( 0, line.length() - 1);
    
    if ( line.length()) {

      if ( !isprint( line[0])) {
	printf( "Failing on char %d\n", line[0]);
	f.close();
	return false;
      }
      if (( pLeft = line.find_first_of(";#[=")) != string::npos) {
	switch ( line[pLeft]) {
	case '[':
	  if ((pRight = line.find_last_of("]")) != string::npos &&
	      pRight > pLeft) {
	    keyname = line.substr( pLeft + 1, pRight - pLeft - 1);
	    AddKeyName( keyname);
	  }
	  break;
	  
	case '=':
	  valuename = line.substr( 0, pLeft);
	  value = line.substr( pLeft + 1);
	  SetValue( keyname, valuename, value);
	  break;
	  
	case ';':
	case '#':
	  if ( !names.size())
	    HeaderComment( line.substr( pLeft + 1));
	  else
	    KeyComment( keyname, line.substr( pLeft + 1));
	  break;
	}
      }
    }
  }

  f.close();
  if ( names.size())
    return true;
  return false;
}

bool CIniFile::WriteFile()
{
  unsigned commentID, keyID, valueID;

  ofstream wf; //w= writefile

  wf.open( path.c_str(), ios::out);
  if ( wf.fail())
    return false;
    

  for ( commentID = 0; commentID < comments.size(); ++commentID)
    wf << ' ; ' << comments[commentID] << iniEOL; //Test
  if ( comments.size())
    wf << iniEOL;


  for ( keyID = 0; keyID < keys.size(); ++keyID) {
    wf << '[' << names[keyID] << ']' << iniEOL;

    for ( commentID = 0; commentID < keys[keyID].comments.size(); ++commentID)
      wf << ';' << keys[keyID].comments[commentID] << iniEOL;

    for ( valueID = 0; valueID < keys[keyID].names.size(); ++valueID)
      wf << keys[keyID].names[valueID] << '=' << keys[keyID].values[valueID] << iniEOL;
    wf << iniEOL;
  }
  wf.close();
  
  return true;
}

long CIniFile::FindKey( string const keyname) const
{
  
   for ( unsigned int keyID = 0; keyID < sizeof(keyname) /*names.size()*/; ++keyID)
   
    if ( CheckCase( names[keyID]) == CheckCase( keyname))
      return long(keyID);
  return noID;
}

long CIniFile::FindValue( unsigned const keyID, string const valuename) const
{
  if ( !keys.size() || keyID >= keys.size())
    return noID;

  for ( unsigned valueID = 0; valueID < keys[keyID].names.size(); ++valueID)
    if ( CheckCase( keys[keyID].names[valueID]) == CheckCase( valuename))
      return long(valueID);
  return noID;
}

unsigned CIniFile::AddKeyName( string const keyname)
{
  names.resize( names.size() + 1, keyname);
  keys.resize( keys.size() + 1);
  return names.size() - 1;
}

string CIniFile::KeyName( unsigned const keyID) const
{
  if ( keyID < names.size())
    return names[keyID];
  else
    return "";
}

unsigned CIniFile::NumValues( unsigned const keyID)
{
  if ( keyID < keys.size())
    return keys[keyID].names.size();
  return 0;
}

unsigned CIniFile::NumValues( string const keyname)
{
  long keyID = FindKey( keyname);
  if ( keyID == noID)
    return 0;
  return keys[keyID].names.size();
}

string CIniFile::ValueName( unsigned const keyID, unsigned const valueID) const
{
  if ( keyID < keys.size() && valueID < keys[keyID].names.size())
    return keys[keyID].names[valueID];
  return "";
}

string CIniFile::ValueName( string const keyname, unsigned const valueID) const
{
  long keyID = FindKey( keyname);
  if ( keyID == noID)
    return "";
  return ValueName( keyID, valueID);
}

bool CIniFile::SetValue( unsigned const keyID, unsigned const valueID, string const value)
{
  if ( keyID < keys.size() && valueID < keys[keyID].names.size())
    keys[keyID].values[valueID] = value;

  return false;
}

bool CIniFile::SetValue( string const keyname, string const valuename, string const value, bool const create)
{
  long keyID = FindKey( keyname);
  if ( keyID == noID) {
    if ( create)
      keyID = long( AddKeyName( keyname));
    else
      return false;
  }

  long valueID = FindValue( unsigned(keyID), valuename);
  if ( valueID == noID) {
    if ( !create)
      return false;
    keys[keyID].names.resize( keys[keyID].names.size() + 1, valuename);
    keys[keyID].values.resize( keys[keyID].values.size() + 1, value);
  } else
    keys[keyID].values[valueID] = value;

  return true;
}

bool CIniFile::SetValueI( string const keyname, string const valuename, int const value, bool const create)
{
  char svalue[MAX_VALUEDATA];

  sprintf( svalue, "%d", value);
  return SetValue( keyname, valuename, svalue);
}

bool CIniFile::SetValueF( string const keyname, string const valuename, double const value, bool const create)
{
  char svalue[MAX_VALUEDATA];

  sprintf( svalue, "%f", value);
  return SetValue( keyname, valuename, svalue);
}

bool CIniFile::SetValueV( string const keyname, string const valuename, char *format, ...)
{
  va_list args;
  char value[MAX_VALUEDATA];

  va_start( args, format);
  vsprintf( value, format, args);
  va_end( args);
  return SetValue( keyname, valuename, value);
}

string CIniFile::GetValue( unsigned const keyID, unsigned const valueID, string const defValue) const
{
  if ( keyID < keys.size() && valueID < keys[keyID].names.size())
    return keys[keyID].values[valueID];
  return defValue;
}

string CIniFile::GetValue( string const keyname, string const valuename, string const defValue) const
{
  long keyID = FindKey( keyname);
  if ( keyID == noID)
    return defValue;

  long valueID = FindValue( unsigned(keyID), valuename);
  if ( valueID == noID)
    return defValue;

  return keys[keyID].values[valueID];
}

int CIniFile::GetValueI(string const keyname, string const valuename, int const defValue) const
{
  char svalue[MAX_VALUEDATA];

  sprintf( svalue, "%d", defValue);
  return atoi( GetValue( keyname, valuename, svalue).c_str()); 
}

double CIniFile::GetValueF(string const keyname, string const valuename, double const defValue) const
{
  char svalue[MAX_VALUEDATA];

  sprintf( svalue, "%f", defValue);
  return atof( GetValue( keyname, valuename, svalue).c_str()); 
}


unsigned CIniFile::GetValueV( string const keyname, string const valuename, char *format,
			      void *v1, void *v2, void *v3, void *v4,
  			      void *v5, void *v6, void *v7, void *v8,
  			      void *v9, void *v10, void *v11, void *v12,
  			      void *v13, void *v14, void *v15, void *v16)
{
  string   value;
  unsigned nVals;
  value = GetValue( keyname, valuename);
  if ( !value.length())
    return false;
  nVals = sscanf( value.c_str(), format,
		  v1, v2, v3, v4, v5, v6, v7, v8,
		  v9, v10, v11, v12, v13, v14, v15, v16);

  return nVals;
}

void CIniFile::HeaderComment( string const comment)
{
  comments.resize( comments.size() + 1, comment);
}

string CIniFile::HeaderComment( unsigned const commentID) const
{
  if ( commentID < comments.size())
    return comments[commentID];
  return "";
}

unsigned CIniFile::NumKeyComments( unsigned const keyID) const
{
  if ( keyID < keys.size())
    return keys[keyID].comments.size();
  return 0;
}

unsigned CIniFile::NumKeyComments( string const keyname) const
{
  long keyID = FindKey( keyname);
  if ( keyID == noID)
    return 0;
  return keys[keyID].comments.size();
}

bool CIniFile::KeyComment( unsigned const keyID, string const comment)
{
  if ( keyID < keys.size()) {
    keys[keyID].comments.resize( keys[keyID].comments.size() + 1, comment);
    return true;
  }
  return false;
}

bool CIniFile::KeyComment( string const keyname, string const comment)
{
  long keyID = FindKey( keyname);
  if ( keyID == noID)
    return false;
  return KeyComment( unsigned(keyID), comment);
}

string CIniFile::KeyComment( unsigned const keyID, unsigned const commentID) const
{
  if ( keyID < keys.size() && commentID < keys[keyID].comments.size())
    return keys[keyID].comments[commentID];
  return "";
}

string CIniFile::KeyComment( string const keyname, unsigned const commentID) const
{
  long keyID = FindKey( keyname);
  if ( keyID == noID)
    return "";
  return KeyComment( unsigned(keyID), commentID);
}

string CIniFile::CheckCase( string s) const
{
  if ( caseInsensitive)
    for ( string::size_type i = 0; i <= s.length(); ++i)
      s[i] = tolower(s[i]);
  return s;
}
