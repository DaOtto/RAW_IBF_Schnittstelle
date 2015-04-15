 /*(
 * The information  contained  herein is a trade secret of CAD-UL GmbH,
 * Ulm, Germany, and is confidential information. It is provided  under
 * a license agreement, and may be  copied or disclosed  only under the
 * terms of  that  agreement.  Any  reproduction or disclosure  of this
 * material  without  the express written  authorization of CAD-UL GmbH
 * or persuant to the license agreement is unlawful.
 *
 * Copyright (c) 1991-1998 CAD-UL GmbH
 * An unpublished work by CAD-UL GmbH, Germany
 * All rights reserved.
 *
 *
 * $Log: iostream.h,v $
 * Revision 1.2  2000/02/08 06:20:45  pla
 * LIBCXX V210
 *
 * Revision 1.1  1998/05/04 14:43:02  aki
 * Initial revision
 *
 */ 

// iostream.h standard header
#ifndef _IOSTREAM_H_
#define _IOSTREAM_H_

#pragma noarguments_in_registers(push)

#include <istream>
_STD_BEGIN
		// OBJECTS
static ios_base::Init _Ios_init0;
extern istream cin;
extern ostream cout;
_STD_END
 #if _HAS_NAMESPACE
using namespace std;
 #else
 #endif /* _HAS_NAMESPACE */

#pragma arguments_in_registers(pop)

#endif /* _IOSTREAM_H_ */

/*
 * Copyright (c) 1996 by P.J. Plauger.  ALL RIGHTS RESERVED. 
 * Consult your license regarding permissions and restrictions.
V2.2:0414 */
