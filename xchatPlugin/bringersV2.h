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

#endif /* _BRINGERS_DLL_H_ */
