/* scanflags - flags used by scanning. */

/* SPDX-License-Identifier: BSD-3-Clause-flex */

/*  Copyright (c) 1990 The Regents of the University of California. */
/*  All rights reserved. */

/*  This code is derived from software contributed to Berkeley by */
/*  Vern Paxson. */

/*  The United States Government has rights in this work pursuant */
/*  to contract no. DE-AC03-76SF00098 between the United States */
/*  Department of Energy and the University of California. */

/*  This file is part of flex. */

/*  Redistribution and use in source and binary forms, with or without */
/*  modification, are permitted provided that the following conditions */
/*  are met: */

/*  1. Redistributions of source code must retain the above copyright */
/*     notice, this list of conditions and the following disclaimer. */
/*  2. Redistributions in binary form must reproduce the above copyright */
/*     notice, this list of conditions and the following disclaimer in the */
/*     documentation and/or other materials provided with the distribution. */

/*  Neither the name of the University nor the names of its contributors */
/*  may be used to endorse or promote products derived from this software */
/*  without specific prior written permission. */

/*  THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR */
/*  IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED */
/*  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR */
/*  PURPOSE. */

#समावेश "flexdef.h"

scanflags_t* _sf_stk = शून्य;
माप_प्रकार sf_शीर्ष_ix=0, _sf_max=0;

व्योम
sf_धकेलो (व्योम)
{
    अगर (sf_शीर्ष_ix + 1 >= _sf_max) {
        _sf_max += 32;
        _sf_stk = पुनः_स्मृति(_sf_stk, माप(scanflags_t) * _sf_max);
    }

    // copy the top element
    _sf_stk[sf_शीर्ष_ix + 1] = _sf_stk[sf_शीर्ष_ix];
    ++sf_शीर्ष_ix;
}

व्योम
sf_निकालो (व्योम)
{
    निश्चित(sf_शीर्ष_ix > 0);
    --sf_शीर्ष_ix;
}

/* one-time initialization. Should be called before any sf_ functions. */
व्योम
sf_init (व्योम)
{
    निश्चित(_sf_stk == शून्य);
    _sf_max = 32;
    sf_शीर्ष_ix = 0;
    _sf_stk = दो_स्मृति(माप(scanflags_t) * _sf_max);
    अगर (!_sf_stk)
        lerr_fatal(_("Unable to allocate %zu of stack"), माप(scanflags_t));
    _sf_stk[sf_शीर्ष_ix] = 0;
}

/* vim:set expandtab cindent tabstop=4 softtabstop=4 shiftwidth=4 textwidth=0: */
