# EmptyFile
EmptyFile est un petit programme qui va ajouter un "Fichier vide" au répertoire Modèles du répertoire personnel

![](https://raw.githubusercontent.com/P4p3RcLip/EmptyFile/master/screenshot.png?token=ALXESUAQRHMYUMQJPWJZPC25CKMVQ)

#### Dépendances pour compilation :
- debhelper 
- autotools-dev 
- libglib2.0-dev
- build-essential

#### Commandes de compilation :
Le système d'exploitation doit être un Debian 9 ou suppérieur, Ubuntu 18.04 ou suppérieur ou tout dérivé de la même famille.

##### Pour obtenir un paquets Debian :

- `tar zcvf ../empty-file_1.0.orig.tar.gz ./`
- `dpkg-buildpackage -us -uc`

##### Ou pour une installation sur un autre système :
- `./configure`
- `make`
- `sudo make install`
