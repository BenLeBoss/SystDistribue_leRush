Lancement :

	-./client.out : après le lancement de la commande donner un numéro de port (différent de ceux déjà pris, et de celui donné au premier client)
	-./serveur.out : après le lancement de la commande donner le nombre de clients que le serveur doit s'attendre à reçevoir (1, 2, etc ...)


Etat du projet : 

Normalement, le projet fonctionne,  c'est-à-dire que le client se connecte en UDP au multicast auquel est abonné le serveur. Le serveur récupère à ce moment-là
l'adresse et le port du client qui lui permettent d'envoyer le tableau de valeurs. Le client le reçoit, calcule la factorielle de chaque valeurs et renvoie un tableau au serveur
qui les affiche.Néanmoins lorsqu'on essaye avec plusieurs serveur le 1er client reçoit bien ce qu'il doit recevoir mais les suivans recoivent le tableau entierement.Lorsque le serveur affiche les résultats il affiche en double les résultat avec les résultat du  1er client   qui possede des fausse sur les nombre qu'il n'as pas reçu plus ce du clients 2.


Fonctionnement : 

Client : 	Le client demande tout d'abord un numéro de port à l'utilisateur qui servira à renseigner sa socket locale TCP, car un serveur ne peut pas communiquer avec plusieurs clients si ils ont la même adresse ip ce 	qui est le cas quand on implémente ces clients sur un seul ordinateur (un seul reçevra les données).
	Une socket UDP est créée, elle envoie un message contenant le numéro de port demandé à l'utilisateur à l'adresse du multicast (qui sera récupéré par le serveur)
	Une socket TCP est ensuite déclarée (avec le port en question), et attend de reçevoir une connexion qu'elle accepte. Un "pont" est alors crée entre le client et le serveur.
	Il reçoit le tableau de données, calcule les factorielles des valeurs contenus dans le tableau et les renvoie au serveur.

Serveur:	Le serveur demande tout d'abord à l'utilisateur le nombre de clients qui vont se connecter et enregistre cette valeur. 
	Il déclare ensuite une socket UDP qu'il lie au groupe multicast auquel il s'abonne pour reçevoir (écouter) les messages.
	Quand le client se connecte, le serveur récupère le message sur le multicast et stocke l'adresse et le port (dans l'objet du mp envoyé).
	Puis il déclare une socket TCP, boucle sur le nombre de clients attendus (question du début) et envoie les parties du tableau grâce aux adresses et port.
	Pour finir, il attend la réponse des clients puis affiche les résultats.

