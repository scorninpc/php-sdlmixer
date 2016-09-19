/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2007 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Bruno Gonçalves                                              |
  +----------------------------------------------------------------------+
*/

#ifndef PHP_SDLMIXER_H
	#define PHP_SDLMIXER_H

extern zend_module_entry sdlmixer_module_entry;
#define phpext_sdlmixer_ptr &sdlmixer_module_entry

#ifdef PHP_WIN32
	#define PHP_SDLMIXER_API __declspec(dllexport)
#else
	#define PHP_SDLMIXER_API
#endif

#ifdef ZTS
	#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(sdlmixer);
PHP_MSHUTDOWN_FUNCTION(sdlmixer);
PHP_RINIT_FUNCTION(sdlmixer);
PHP_RSHUTDOWN_FUNCTION(sdlmixer);
PHP_MINFO_FUNCTION(sdlmixer);

PHP_FUNCTION(Mix_Test);
PHP_FUNCTION(Mix_OpenAudio);
PHP_FUNCTION(Mix_LoadMUS);
PHP_FUNCTION(Mix_PlayMusic);
PHP_FUNCTION(Mix_HaltMusic);
PHP_FUNCTION(Mix_FreeMusic);
PHP_FUNCTION(Mix_CloseAudio);
PHP_FUNCTION(Mix_PauseMusic);
PHP_FUNCTION(Mix_ResumeMusic);
PHP_FUNCTION(Mix_VolumeMusic);
PHP_FUNCTION(Mix_SetMusicPosition);
PHP_FUNCTION(Mix_FadeOutMusic);
PHP_FUNCTION(Mix_LoadWAV);
PHP_FUNCTION(Mix_PlayChannel);

#ifdef ZTS
	#define SDLMIXER_G(v) TSRMG(sdlmixer_globals_id, zend_sdlmixer_globals *, v)
#else
	#define SDLMIXER_G(v) (sdlmixer_globals.v)
#endif

#endif
