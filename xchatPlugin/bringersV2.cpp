/*******************************************************************************
 *                                                                             *
 *  Bringers - A truth or dare chooser program                                 *
 *  Copyright (C) 2007, Renato "Lond" Cerqueira                                *
 *                                                                             *
 *  This program is free software: you can redistribute it and/or modify       *
 *  it under the terms of the GNU General Public License as published by       *
 *  the Free Software Foundation, either version 3 of the License, or          *
 *  (at your option) any later version.                                        *
 *                                                                             *
 *  This program is distributed in the hope that it will be useful,            *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 *  GNU General Public License for more details.                               *
 *                                                                             *
 *  You should have received a copy of the GNU General Public License          *
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.      *
 *                                                                             *
 *******************************************************************************/

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include "xchat-plugin.h"
static xchat_plugin *ph;
#include "bringersV2.h"

using namespace std;

int sorteio ( char *word[], char *word_eol[], void *userdata )
{
	string teste;
	if ( !userdata )
	{
		char *cteste;
		teste = word[4];
		teste = teste.substr(1);
		cteste = xchat_strip(ph, teste.c_str(), -1, 1|2 );
		if ( !cteste )
			return XCHAT_EAT_NONE;
		teste = cteste;
		xchat_free(ph, cteste);

		if ( teste != "!sorteia" )
			return XCHAT_EAT_NONE;
	}
	else
	{
		teste = word[1];
		if ( teste != "!sorteia" )
			return XCHAT_EAT_NONE;
	}

	return XCHAT_EAT_PLUGIN; 
}

void xchat_plugin_get_info(char **name, char **desc, char **version, void **reserved)
{
   *name = PNAME;
   *desc = PDESC;
   *version = PVERSION;
}

int xchat_plugin_init(xchat_plugin *plugin_handle,
                      char **plugin_name,
                      char **plugin_desc,
                      char **plugin_version,
                      char *arg)
{
	/* we need to save this for use with any xchat_* functions */
	ph = plugin_handle;

	/* tell xchat our info */
	*plugin_name = PNAME;
	*plugin_desc = PDESC;
	*plugin_version = PVERSION;

	char *self = "Self";

	xchat_hook_server(ph, "PRIVMSG", XCHAT_PRI_NORM, sorteio, NULL);
	xchat_hook_command(ph, "", XCHAT_PRI_NORM, sorteio, "", self);

	//xchat_hook_command(ph, "CONFIG", XCHAT_PRI_NORM, config_lond, "Uso: config <opções>; referir ao manual para ver as opções", 0);
	xchat_printf(ph,"Bringers, Copyright (C) 2007, Renato \"Lond\" Cerqueira");
	xchat_printf(ph,"This program comes with ABSOLUTELY NO WARRANTY;'.");
	xchat_printf(ph,"This is free software, and you are welcome to redistribute it");
	xchat_printf(ph,"under certain conditions.");
	/*xchat_print(ph,"      :::        ::::::::  ::::    ::: :::::::::");
	xchat_print(ph,"     :+:       :+:    :+: :+:+:   :+: :+:    :+:");
	xchat_print(ph,"    +:+       +:+    +:+ :+:+:+  +:+ +:+     +:+");
	xchat_print(ph,"   +#+       +#+    +:+ +#+ +:+ +#+ +#+     +:+");
	xchat_print(ph,"  +#+       +#+    +#+ +#+  +#+#+# +#+     +#+");
	xchat_print(ph," #+#       #+#    #+# #+#   #+#+# #+#    #+#");
	xchat_print(ph,"########## ########  ###    #### #########");
	xchat_print(ph,"      ::::::::   ::::::::  :::::::::  ::::::::::: ::::::::: :::::::::::");
	xchat_print(ph,"    :+:    :+: :+:    :+: :+:    :+:     :+:     :+:    :+:    :+:");
	xchat_print(ph,"   +:+        +:+        +:+    +:+     +:+     +:+    +:+    +:+");
	xchat_print(ph,"  +#++:++#++ +#+        +#++:++#:      +#+     +#++:++#+     +#+");
	xchat_print(ph,"        +#+ +#+        +#+    +#+     +#+     +#+           +#+");
	xchat_print(ph,"#+#    #+# #+#    #+# #+#    #+#     #+#     #+#           #+#");
	xchat_print(ph,"########   ########  ###    ### ########### ###           ###");
	xchat_printf(ph,"                                                     V %s",PVERSION);*/
	//xchat_print(ph,"Pressione <f9> para configurar");

	return 1;       /* return 1 for success */
}

#ifdef WIN32
// Windows
#include "shlobj.h"

void gotoxy(int x, int y)
{
COORD scrn;
HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
scrn.X = x; scrn.Y = y;
SetConsoleCursorPosition(hOuput,scrn);
}

void clrscr()
{
system("cls");
}
#else
// Linux
void gotoxy(int x, int y)
{
	cout << "\33[" << y << ";"<< x << "H";
}

void clrscr()
{	
	cout << "\33[H\33[2J";
	cout << "***********************" << endl;
	cout << "*    Bringers V2.0    *" << endl;
	cout << "***********************" << endl;
	cout << endl;
}
#endif

int main (void)
{
	srand(time(NULL));
	string temp;
	clrscr();
	cout << "Para começar, digite o número de participantes." << endl;
	getline(cin, temp);
	int n;
	stringstream(temp) >> n;

	if ( n < 3 )
	{
		clrscr();
		cout << "Desculpe. O bringers só funciona com mais de 2 participantes. Arranje mais uns doidos e tente de novo." << endl;
		exit(1);
	}

	clrscr();
	cout << "Ótimo. Agora, digite o nome dos " << n << " participantes para que eles possam ser armazenados." << endl;

	vector<string> nomes;
	int maiorNome;

	maiorNome = 0;

	for ( int i = 0 ; i < n ; i++ )
	{
		getline(cin, temp);
		nomes.push_back(temp);
		if ( temp.size() > maiorNome )
			maiorNome = temp.size();
	}
	
	clrscr();
	int ratioP, ratioC;

	cout << "Certo, agora eu quero que você me diga a relação entre consequencias e perguntas. Ex: 1 2 --> 1 consequência, 2 perguntas, 1 consequencia, 2 perguntas.." << endl;

	getline(cin, temp);
	stringstream(temp) >> ratioC >> ratioP;

	clrscr();
	cout << "Muito bem. Agora, quando vocês estiverem prontos, pressione enter." << endl;
	cout << "Quando quiserem terminar o jogo, digitem \"Fim\"." << endl;
	getline(cin, temp);
	
	int rodadas;
	rodadas = 0;
	int nPerguntaram, nResponderam;
	nPerguntaram = nResponderam = 0;
	vector<bool> perguntaram(n, false), responderam(n, false);
	int nPerguntaramC, nResponderamC;
	nPerguntaramC = nResponderamC = 0;
	vector<bool> perguntaramC(n, false), responderamC(n, false);

	int estatisticas[n][n];
	int anulados = 0;
	int consequencias = 0, perguntas = 0;
	memset(estatisticas, 0, sizeof(estatisticas));
	
	bool consequencia;
	int nP, nC;
	nP = nC = 0;
	consequencia = false;
	while (1)
	{
		clrscr();
		int pergunta, resposta;
		bool novo;

		if ( consequencia )
		{
			do
			{
				novo = true;
				pergunta = rand() % n;

				if ( perguntaramC[pergunta] )
					novo = false;
			} while ( !novo );

			if ( ++nPerguntaramC >= n )
			{
				for ( int i = 0 ; i < n ; i++ )
					perguntaramC[i] = false;
				nPerguntaramC = 1;
			}

			perguntaramC[pergunta] = true;

			do
			{
				novo = true;
				resposta = rand() % n;
				if ( resposta == pergunta )
				{
					if ( nResponderamC + 1 >= n )
					{
						for ( int i = 0 ; i < n ; i++ )
							responderamC[i] = false;
						nResponderamC = 0;
					}
					novo = false;
				}
				if ( responderamC[resposta] )
					novo = false;
			} while ( !novo );

			if ( ++nResponderamC >= n )
			{
				for ( int i = 0 ; i < n ; i++ )
					responderamC[i] = false;
				nResponderamC = 1;
			}

			responderamC[resposta] = true;
		cout << "Agora, uma consequencia" << endl;

		cout << "De " << nomes[pergunta] << endl;
		cout << "Para " << nomes[resposta] << endl;

		estatisticas[pergunta][resposta]++;

		gotoxy(0,20);
		cout << "Para cancelar o último sorteio, digite u" << endl;
		cout << "Para mudar o ratio, digite r" << endl;
		cout << "Para sair, digite a qualquer momento \"Fim\"" << endl;

		getline(cin, temp);
		if ( !strcasecmp(temp.c_str(), "fim") )
			break;
		if ( !strcasecmp(temp.c_str(), "r") )
		{
			clrscr();
			cout << "Certo, me diga a nova relação entre consequencias e perguntas. Ex: 1 2 --> 1 consequência, 2 perguntas, 1 consequencia, 2 perguntas.." << endl;
			cout << "A nova relação valerá a partir do próximo sorteio" << endl;

			getline(cin, temp);
			stringstream(temp) >> ratioC >> ratioP;
		}
		if ( !strcasecmp(temp.c_str(), "u") )
		{
			nPerguntaramC--;
			nResponderamC--;
			responderamC[resposta] = false;
			perguntaramC[pergunta] = false;
			estatisticas[pergunta][resposta]--;
			anulados++;
			continue;
		}
		}
		else
		{
			do
			{
				novo = true;
				pergunta = rand() % n;

				if ( perguntaram[pergunta] )
					novo = false;
			} while ( !novo );

			if ( ++nPerguntaram >= n )
			{
				for ( int i = 0 ; i < n ; i++ )
					perguntaram[i] = false;
				nPerguntaram = 1;
			}

			perguntaram[pergunta] = true;

			do
			{
				novo = true;
				resposta = rand() % n;
				if ( resposta == pergunta )
				{
					if ( nResponderam + 1 >= n )
					{
						for ( int i = 0 ; i < n ; i++ )
							responderam[i] = false;
						nResponderam = 0;
					}
					novo = false;
				}
				if ( responderam[resposta] )
					novo = false;
			} while ( !novo );

			if ( ++nResponderam >= n )
			{
				for ( int i = 0 ; i < n ; i++ )
					responderam[i] = false;
				nResponderam = 1;
			}

			responderam[resposta] = true;
		cout << "Agora, uma pergunta" << endl;

		cout << "De " << nomes[pergunta] << endl;
		cout << "Para " << nomes[resposta] << endl;

		estatisticas[pergunta][resposta]++;

		gotoxy(0,20);
		cout << "Para cancelar o último sorteio, digite u" << endl;
		cout << "Para mudar o ratio, digite r" << endl;
		cout << "Para sair, digite a qualquer momento \"Fim\"" << endl;

		getline(cin, temp);
		if ( !strcasecmp(temp.c_str(), "fim") )
			break;
		if ( !strcasecmp(temp.c_str(), "r") )
		{
			clrscr();
			cout << "Certo, me diga a nova relação entre consequencias e perguntas. Ex: 1 2 --> 1 consequência, 2 perguntas, 1 consequencia, 2 perguntas.." << endl;
			cout << "A nova relação valerá a partir do próximo sorteio" << endl;

			getline(cin, temp);
			stringstream(temp) >> ratioC >> ratioP;
		}
		if ( !strcasecmp(temp.c_str(), "u") )
		{
			nPerguntaram--;
			nResponderam--;
			responderam[resposta] = false;
			perguntaram[pergunta] = false;
			estatisticas[pergunta][resposta]--;
			anulados++;
			continue;
		}
		}


		if ( consequencia )
		{
			nC++;
			consequencias++;
		}
		else
		{
			nP++;
			perguntas++;
		}

		if ( nP >= ratioP )
		{
			nP = 0;
			consequencia = true;
		}
		else if ( nC >= ratioC )
		{
			nC = 0;
			consequencia = false;
		}
	}

	if ( consequencia )
		consequencias++;
	else
		perguntas++;

	clrscr();
	cout << "Estatísticas do bringer" << endl;
	cout << "---------------------------------------" << endl;
	cout << "Pergunta  X  Responde" << endl;
	for ( int i = 0 ; i < n ; i++ )
		for ( int j = 0 ; j < n ; j++ )
		{
			if ( i != j )
				cout << nomes[i] << " X " << nomes[j] << ": " << estatisticas[i][j] << endl;
		}
	cout << "Anulados: " << anulados << endl;
	cout << "Perguntas: " << perguntas << endl;
	cout << "Consequências: " << consequencias << endl;
				
	return 0;
}
