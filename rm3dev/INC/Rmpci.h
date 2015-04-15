/****************************************************************************/
/*  projekt:     RMOSPCI                                                    */
/****************************************************************************/
/*  header:      RMPCI.H                                                    */
/*  description: defines, typedefs and declarations from inside, but for    */
/*               use inside and outside the project                         */
/*  author:      he4862/mg4482                                              */
/*  date:        Jun 21, 01                                                 */
/*  version:     V1.00.03                                                   */
/*  copyright:   (c) siemens 2001, confidential, all rights reserved        */
/****************************************************************************/
/*  date         name     version   change                                  */
/*  Jun 21, 01   mg4482   0001      original issue                          */
/*  Jan  7, 03   nb2544   0002      pragma introduced                       */
/*  Sep 26, 03   nb2544   0003      c++ introduced                          */
/****************************************************************************/

#ifndef _RMPCI_H_
#define _RMPCI_H_


#if defined(_ARCHITECTURE_) || defined(CADUL)
 #pragma align( _PCI_CONFIG_SPACE = 1)
#endif  /* defined(_ARCHITECTURE_) || defined(CADUL) */

#ifdef _MSC_VER
#pragma pack(1)     /* Align on byte  */
#endif

#ifdef __BORLANDC__
#pragma option -a-	/* set all to byte alignment */
#endif /* __BORLANDC__ */

/****************************************************************************/
/*  typedefs                                                                */
/****************************************************************************/
typedef struct _PCI_CONFIG_SPACE
{
  uchar  PciBusNum;
  uchar  PciDeviceNum;
  uchar  PciFunctionNum;
  ushort VendorId;
  ushort DeviceId;
  ushort CmdReg;
  ushort StatReg;
  uchar  RevisionId;
  uchar  ClassCode[3];
  uchar  CacheLineSize;
  uchar  Latencytime;
  uchar  HeaderType;
  uchar  BIST;
  uint   BaseAdr0;
  uint   BaseAdr1;
  uint   BaseAdr2;
  uint   BaseAdr3;
  uint   BaseAdr4;
  uint   BaseAdr5;
  uint   CardbusCisPtr;
  ushort SubsysVendorId;
  ushort SubSysId;
  uint   ExpRomBaseAdr;
  uint   reserved[2];
  uchar  IntLine;
  uchar  IntPin;
  uchar  Min_Gnt;
  uchar  Max_Lat;
} PCI_CONFIG_SPACE;
  
/****************************************************************************/
/*  typedefs                                                                */
/****************************************************************************/
typedef struct {
  _FIXED _FAR int (*RmSetShIntISHandler1)(
    uint,
    int _FIXED _FAR (*)(void),
    int _FIXED _FAR (*)(void),
    int _FIXED _FAR (*)(void *),
    void            *,
    uint            *
  );
  _FIXED _FAR int (*RmSetShIntISHandler2)(
    uint,
    int _FIXED _FAR (*)(void *),
    int _FIXED _FAR (*)(void *),
    void            *,
    uint            *
  );
  _FIXED _FAR int (*RmClrShIntISHandler)(
    uint,
    uint
  );
} ISH_LTL_STRUC;
typedef struct {
  const ISH_LTL_STRUC far *ltlptr;
  char                    reserved[8];
} MAIL_LTLPTR;

#ifdef _MSC_VER
#pragma pack()
#endif

#ifdef __BORLANDC__
#pragma option -a.	/* reset alignment to commandline specification */
#endif /* __BORLANDC__ */


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/****************************************************************************/
/*  declarations                                                            */
/****************************************************************************/
int _FIXED _FAR RmClrShIntISHandler(
  uint,
  uint
);
int _FIXED _FAR RmInitShIntClient(void);
int _FIXED _FAR RmSetShIntISHandler1(
  uint,
  int _FIXED _FAR (*)(void),
  int _FIXED _FAR (*)(void),
  int _FIXED _FAR (*)(void *),
  void            *,
  uint            *
);
int _FIXED _FAR RmSetShIntISHandler2(
  uint,
  int _FIXED _FAR (*)(void *),
  int _FIXED _FAR (*)(void *),
  void            *,
  uint            *
);


  
/****************************************************************************/
/*  declarations                                                            */
/****************************************************************************/
int _FIXED _FAR RmPciSearchFunction(
  ushort, 
  ushort,
  PCI_CONFIG_SPACE [],
  ushort,
  ushort           *
);

int _FIXED _FAR RmPciSearchSubFunction(
  ushort, 
  ushort,
  ushort,
  ushort,
  PCI_CONFIG_SPACE [],
  ushort,
  ushort           *
);



/****************************************************************************/
/*  declarations                                                            */
/****************************************************************************/
int _FIXED _FAR RmIntShSrv(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
