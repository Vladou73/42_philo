

- Des philosop0s sont assis autour d’une table ronde au
centre de laquelle se trouve un grand plat de spaghetti

- chaque philo peut faire 3 actions : manger, de penser ou de dormir.
- les actions ne peuvent pas être simultanées

- il y a autant de fourchettes que de philo

- Pour manger
	- il faut 2 fourchettes (1 à gauche, 1 à droite)
	- 1 fourchette en cours d'utilisation par 1 philo ne peut pas être utilisée par 1 autre

- Quand un philo finit de manger
	- il n'utilise plus les fourchettes
	- il s'endort

- Quand un philo finit de dormir il pense

- Chaque philosophe doit être représenté par un thread
- Afin d’empêcher les philosophes de dupliquer les fourchettes, vous devez protéger
leur état en mémoire avec un mutex pour chacune d’entre elle.

- La simulation s'arrête et on fail si un philo meurt de fin

## Contraintes arguments du programme
- 4 args obligatoires, 1 arg optionnel
◦ number_of_philosophers : # philosophes = # fourchettes. MINIMUM 1 philo
- si il n'y a qu'un philo => il n'y a qu'une fourchette, c'est impossible de manger
◦ time_to_die (en millisecondes) : Si un philosophe n’a pas commencé à manger
time_to_die millisecondes après le début de son précédent repas ou depuis le
début de la simulation, il meurt.
◦ time_to_eat (en millisecondes) : Le temps qu’un philosophe prend à manger.
Pendant ce temps, un philosophe doit garder ses deux fourchettes.
◦ time_to_sleep (en millisecondes) : Le temps qu’un philosophe passe à dormir.
◦ number_of_times_each_philosopher_must_eat (argument optionnel) : Si tous
les philosophes ont mangé au moins number_of_times_each_philosopher_must_eat
fois, la simulation prend fin. Si cet argument n’est pas spécifié, alors la simu-
lation prend fin à la mort d’un philosophe.

## Objet du jeu global
- number_of_philosophers
- time_to_die
- time_to_eat
- time_to_sleep
- number_of_times_each_philosopher_must_eat
- Tableau contenant tous les objets philos

## Objet philosophe
- number : Chaque philosophe se voit assigner un numéro entre 1 et number_of_philosophers.
• Le philosophe numéro 1 est assis à côté du philosophe numéro number_of_philosophers.
Les autres suivent cette logique : philosophe numéro N est assis entre philosophe
numéro N - 1 et philosophe numéro N + 1

## logs
- il faut afficher tout changement d'état d'un philo, formatté comme suit :
	◦ Quand un philo commence à manger ? "timestamp_in_ms X has taken a fork"
	◦ timestamp_in_ms X is eating
	◦ timestamp_in_ms X is sleeping
	◦ timestamp_in_ms X is thinking
	◦ timestamp_in_ms X died
Remplacez timestamp_in_ms par le timestamp actuel en millisecondes
et X par le numéro du philosophe.
- ne pas mélanger les différents messages entre eux => faire 1 msg par philo => printf
- il ne doit pas y avoir plus de 10 ms entre la mort d’un philosophe et l’affichage du
message annonçant sa mort.


## Tips
- Ne pas faire de tests avec le terminal de vscode
- Faire passer les tests
	- https://github.com/lienardale/alientest_philosopher

## foncytions autorisées
memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock


## Questions

- c'est quoi une data race
- Pour quitter proprement le programme quand un philo est mort :
	- Dans ton thread tu lock ce mutex, tu stock la valeur de la variable, tu unlock et la tu fais ton if pour exit proprement ou non et comme ca t as bien unlock le mutex
	- le sujet est clair, 0 datarace c est bien tout l objectif du sujet ;)

