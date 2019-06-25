#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libintl.h>
#include <locale.h>

#define _(STRING) gettext(STRING)

char *getSysLang()
{
	char *lang;
	lang = getenv("LANG");
	return lang;
}

char *getXdgUserDirsConfigPath()
{
	//Variables setup
	//Définition des variables
	char home[100], *xdg_user_dirs_config_path;

	strcpy(home,getenv("HOME"));
	xdg_user_dirs_config_path = strcat(home,"/.config/");
	return xdg_user_dirs_config_path;

}

#define MAX_LINE_LEN 256
char *getTemplatePath()
{
	//Variables setup
	//Définition des variables
	FILE *file;
	int template_dir_len;
	char home[100], xdg_user_dirs_config_patch[100], *config_file_patch, line[MAX_LINE_LEN + 1],
	*token, template_dir_cache[100], *template_path;

	//Save the "HOME" value and open the "user-dirs.dirs" file
	//Enregistrement de la valeur "HOME" et ouverture du fichier "user-dirs.dirs"
	strcpy(home,getenv("HOME"));
	strcpy(xdg_user_dirs_config_patch,getXdgUserDirsConfigPath());
	config_file_patch = strcat(xdg_user_dirs_config_patch,"/user-dirs.dirs");
	file = fopen( config_file_patch, "r" ) ;

	//Analysis of open file
	//Analyse du ficher ouvert
	while( fgets( line, MAX_LINE_LEN, file ) != NULL)
	{

		token = strtok (line,"=");
		// Loop only if the first line does not start with #
		//Boucle uniquement si la première ligne ne commence pas par #
		while (token != NULL && token[0] != '#' )
		{
			//Comparison between two variables
			//Comparaison entre deux variables
			if(strcmp(token, "XDG_TEMPLATES_DIR") == 0)
			{
				token = strtok (NULL, "=");
				//Copy the value of the token inside another variable
				//Copie de la valeur du token dans une autre variable
				strcpy(template_dir_cache, token);
				//Fetching of variable
				//Retraitement de la variable
				template_path = template_dir_cache;
				template_dir_len = strlen(template_path);
				template_path[template_dir_len-2] = '\0';
				template_path = template_path+6;
				template_path = strcat(template_path, "/");			}
			else
			{
				token = strtok (NULL, "=");
			}
		}

	}
	fclose(file);

	strcpy(template_path,strcat(home,template_path));
	return (char*) template_path;
}

char *getTemplateLang()
{
	//Variables setup
	//Définition des variables
	FILE *file = NULL;
	char template_path[100], line[1024], *lang;

	//Copy the location of the configuration file
	//Copie l'emplacement de l'emplacement du ficher de configuration
	strcpy(template_path,strcat(getXdgUserDirsConfigPath(),"user-models.locale"));
	file = fopen(template_path,"r");

	//Test if the file could be opened
	//Test si le fichier a pu être ouvert
	if(file == NULL)
	{
		return (char*) "error";
	}
	else
	{
		fscanf(file,"%[^\n]", line);
		lang = strcat(line,"");
		return (char*) lang;
	}
}

void setTemplateLang()
{
	//Variables setup
	//Définition des variables
	FILE *file = NULL;
	char template_path[100];

	//Copy the location of the configuration file
	//Copie l'emplacement de l'emplacement du ficher de configuration
	strcpy(template_path,strcat(getXdgUserDirsConfigPath(),"user-models.locale"));
	file = fopen(template_path,"w");
	fprintf(file, "%s", getSysLang());
	fclose(file);

}

void *createEmptyTemplate(char empty_file_name[100])
{
	//Variables setup
	//Définition des variables
	FILE *file = NULL;
	char empty_file_path[100];

	strcpy(empty_file_path,strcat(getTemplatePath(),empty_file_name));
	file = fopen(empty_file_path,"w");
	fclose(file);
}

void delEmptyTemplate(char empty_file_name[100])
{
	//Variables setup
	//Définition des variables
	char empty_file_path[100];

	strcpy(empty_file_path,strcat(getTemplatePath(),empty_file_name));
	remove(empty_file_path);
}

int main() {

	//Localization config
	//Configuration de la localisation
	setlocale (LC_ALL, "");
	bindtextdomain(GETTEXT_PACKAGE, PROGRAMNAME_LOCALEDIR);
	bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
	textdomain(GETTEXT_PACKAGE);

	//Difference between the system language variable and that recorded by this program
	//Différence entre la variable de langue du système et celle enregistré
	if(strcmp(getSysLang(), getTemplateLang()) != 0)
	{
		setlocale(LC_ALL, getTemplateLang());
		delEmptyTemplate(_("Empty file"));
		setlocale (LC_ALL, "");
		createEmptyTemplate(_("Empty file"));
		setTemplateLang();
	}
}

