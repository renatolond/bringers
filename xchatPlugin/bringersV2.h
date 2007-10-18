#ifndef _BRINGERS_DLL_H_
#define _BRINGERS_DLL_H_

#define PNAME "Bringers"
#define PDESC "Sorteio de usuários do canal #Bringers para jogo da verdade"
#define PVERSION "0.1"

extern "C"
{
	int xchat_plugin_init(xchat_plugin *plugin_handle,
			char **plugin_name,
			char **plugin_desc,
			char **plugin_version,
			char *arg);
	void xchat_plugin_get_info(char **name,
			char **desc,
			char **version,
			void **reserved);
}

#endif /* _BRINGERS_DLL_H_
