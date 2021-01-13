/*--------------------------------------------------------------------------------
Copyright (C) 2021 - Mustafa Ala
---------------------------------------------------------------------------------*/

#ifndef CONFIG_H_
#define CONFIG_H_

#define DEVELOPMENT

#ifdef HAVE_CONFIG_H

#include <config.h>

#ifdef DEV
#define DEVELOPMENT
#else
#ifdef TEST
#undef DEVELOPMENT
#define UTEST
#endif
#endif
#endif

#endif /* CONFIG_H_ */
