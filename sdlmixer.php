<?php 
	if(!extension_loaded("sdlmixer"))
	{
		if(!dl("sdlmixer." . PHP_SHLIB_SUFFIX))
		{
			die("Erro: sdlmixer not loaded\n");
		}
	}

	$file = "/media/backup/Musicas/Arch Enemy/Rare And Unreleased (EP)/01-arch_enemy_-_starbreaker.mp3";
	
	Mix_OpenAudio(22050, 2, 1024);
	$resource = Mix_LoadMUS($file);
	Mix_PlayMusic($resource);
	
	sleep(5);
