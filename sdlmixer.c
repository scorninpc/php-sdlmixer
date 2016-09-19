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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_sdlmixer.h"
#include "SDL/SDL_mixer.h"

static int le_sdlmixer, le_sdlmixermusic, le_sdlmixersample, le_sdlmixer_config;

#define le_sdlmixermusic_name  "SDLmixer Music"
#define le_sdlmixersample_name  "SDLmixer Sample"

zend_function_entry sdlmixer_functions[] = {
	PHP_FE(Mix_OpenAudio, 				NULL)
	PHP_FE(Mix_LoadMUS, 				NULL)
	PHP_FE(Mix_PlayMusic, 				NULL)
	PHP_FE(Mix_HaltMusic, 				NULL)
	PHP_FE(Mix_FreeMusic, 				NULL)
	PHP_FE(Mix_CloseAudio, 				NULL)
	PHP_FE(Mix_PauseMusic,	 			NULL)
	PHP_FE(Mix_ResumeMusic,	 			NULL)
	PHP_FE(Mix_VolumeMusic,		 		NULL)
	PHP_FE(Mix_SetMusicPosition,		NULL)
	PHP_FE(Mix_FadeOutMusic,			NULL)
	PHP_FE(Mix_LoadWAV,					NULL)
	PHP_FE(Mix_PlayChannel,				NULL)
	{NULL, NULL, NULL}
};

zend_module_entry sdlmixer_module_entry = {
	#if ZEND_MODULE_API_NO >= 20010901
		STANDARD_MODULE_HEADER,
	#endif
		"sdlmixer",
		sdlmixer_functions,
		PHP_MINIT(sdlmixer),
		PHP_MSHUTDOWN(sdlmixer),
		PHP_RINIT(sdlmixer),
		PHP_RSHUTDOWN(sdlmixer),
		PHP_MINFO(sdlmixer),
	#if ZEND_MODULE_API_NO >= 20010901
		"0.1",
	#endif
		STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_SDLMIXER
	ZEND_GET_MODULE(sdlmixer)
#endif

static void php_sdlmixermusic_close(zend_rsrc_list_entry *rsrc TSRMLS_DC)
{
	Mix_Music *manager = (Mix_Music *)rsrc->ptr;
	Mix_FreeMusic(manager);
}

static void php_sdlmixersample_close(zend_rsrc_list_entry *rsrc TSRMLS_DC)
{
	Mix_Chunk *manager = (Mix_Chunk *)rsrc->ptr;
	Mix_FreeChunk(manager);
}

PHP_MINIT_FUNCTION(sdlmixer)
{
	le_sdlmixermusic = zend_register_list_destructors_ex(php_sdlmixermusic_close, NULL, le_sdlmixermusic_name, module_number);
	le_sdlmixersample = zend_register_list_destructors_ex(php_sdlmixersample_close, NULL, le_sdlmixersample_name, module_number);
	return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(sdlmixer)
{
	return SUCCESS;
}

PHP_RINIT_FUNCTION(sdlmixer)
{
	return SUCCESS;
}

PHP_RSHUTDOWN_FUNCTION(sdlmixer)
{
	return SUCCESS;
}

PHP_MINFO_FUNCTION(sdlmixer)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "sdlmixer support", "enabled");
	php_info_print_table_end();
}

PHP_FUNCTION(Mix_OpenAudio)
{
	int frequency;
	int channels;
	int chunksize;
	
	int result;
	
	result = zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lll", &frequency, &channels, &chunksize);
	
	if(result == FAILURE) 
	{
		return;
	}
	
	Mix_OpenAudio(frequency, MIX_DEFAULT_FORMAT, channels, chunksize);
}

PHP_FUNCTION(Mix_LoadMUS)
{
	char *filename;
	int filename_len;
	Mix_Music *musicResource = NULL;
	
	int result;
	
	result = zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &filename, &filename_len);
	
	if(result == FAILURE) 
	{
		return;
	}
	
	musicResource = Mix_LoadMUS(filename);
	
	ZEND_REGISTER_RESOURCE(return_value, musicResource, le_sdlmixermusic);
}

PHP_FUNCTION(Mix_PlayMusic)
{
	Mix_Music *musicResource = NULL;
	
	zval *resource;
	
	int result;
	int res_type = -1; 
	
	result = zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &resource);
	
	if(result == FAILURE) 
	{
		return;
	}
	
	musicResource = (Mix_Music *)zend_list_find(Z_RESVAL_P(resource), &res_type);
	
	Mix_PlayMusic(musicResource, -1);
	
	return;
}

PHP_FUNCTION(Mix_HaltMusic)
{
	Mix_HaltMusic();
}

PHP_FUNCTION(Mix_FreeMusic)
{
	Mix_Music *musicResource = NULL;
	
	zval *resource;
	
	int res_type = -1; 
	int result;
	
	result = zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &resource);
	
	if(result == FAILURE) 
	{
		return;
	}
	
	musicResource = (Mix_Music *)zend_list_find(Z_RESVAL_P(resource), &res_type);
	
	Mix_FreeMusic(musicResource);
}

PHP_FUNCTION(Mix_CloseAudio)
{
	Mix_CloseAudio();
}

PHP_FUNCTION(Mix_PauseMusic)
{
	
	Mix_PauseMusic();
}

PHP_FUNCTION(Mix_ResumeMusic)
{
	Mix_ResumeMusic();
}

PHP_FUNCTION(Mix_VolumeMusic)
{
	int volume = -1; 
	int result;
	
	result = zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &volume);
	
	if(result == FAILURE) 
	{
		return;
	}
	
	Mix_VolumeMusic(volume);
}

PHP_FUNCTION(Mix_SetMusicPosition)
{
	double position;
	int result;
	
	result = zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "d", &position);
	
	if(result == FAILURE) 
	{
		return;
	}
	
	Mix_SetMusicPosition(position);
}

PHP_FUNCTION(Mix_FadeOutMusic)
{
	int milisec = -1; 
	int result;
	
	result = zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &milisec);
	
	if(result == FAILURE) 
	{
		return;
	}
	
	Mix_FadeOutMusic(milisec);
}

PHP_FUNCTION(Mix_LoadWAV)
{
	char *filename;
	int filename_len;
	Mix_Chunk *sampleResource = NULL;
	
	int result;
	
	result = zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &filename, &filename_len);
	
	if(result == FAILURE) 
	{
		return;
	}
	
	sampleResource = Mix_LoadWAV(filename);
	
	ZEND_REGISTER_RESOURCE(return_value, sampleResource, le_sdlmixersample);
}

PHP_FUNCTION(Mix_PlayChannel)
{
	Mix_Chunk *sampleResource = NULL;
	int channel;
	int loops;
	
	zval *resource;
	
	int res_type = -1; 
	int result;
	
	result = zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lrl", &channel, &resource, &loops);
	
	if(result == FAILURE) 
	{
		return;
	}
	
	sampleResource = (Mix_Chunk *)zend_list_find(Z_RESVAL_P(resource), &res_type);
	
	Mix_PlayChannel(channel, sampleResource, loops);
}
