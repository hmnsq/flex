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

#অন্তর্ভাব "flexdef.h"

scanflags_t* _sf_stk = ফাঁকা;
size_t sf_শীর্ষ_ix=0, _sf_max=0;

শূন্য
sf_ঠেলো (শূন্য)
{
    যদি (sf_শীর্ষ_ix + 1 >= _sf_max) {
        _sf_max += 32;
        _sf_stk = realloc(_sf_stk, আকার(scanflags_t) * _sf_max);
    }

    // copy the top element
    _sf_stk[sf_শীর্ষ_ix + 1] = _sf_stk[sf_শীর্ষ_ix];
    ++sf_শীর্ষ_ix;
}

শূন্য
sf_বের_করো (শূন্য)
{
    প্রতিজ্ঞা(sf_শীর্ষ_ix > 0);
    --sf_শীর্ষ_ix;
}

/* one-time initialization. Should be called before any sf_ functions. */
শূন্য
sf_init (শূন্য)
{
    প্রতিজ্ঞা(_sf_stk == ফাঁকা);
    _sf_max = 32;
    sf_শীর্ষ_ix = 0;
    _sf_stk = malloc(আকার(scanflags_t) * _sf_max);
    যদি (!_sf_stk)
        lerr_fatal(_("Unable to allocate %zu of stack"), আকার(scanflags_t));
    _sf_stk[sf_শীর্ষ_ix] = 0;
}

/* vim:set expandtab cindent tabstop=4 softtabstop=4 shiftwidth=4 textwidth=0: */
