cas 5 800 200 0: die alors que ca devrait pas
check arguments : atol ne suffit pas, rajouter check array has only digits pour tous les arguments ==>ok
cas 4 500 200 2147483647: tant qu un philo esten train de sleep, le thread ne se termine pas ==> reglé
cas 4 200 200 99999999999999: devrait renvoyer une erreur ?
cas avec beaucoup de philos (130, 140, 150) il y en a qui meurent alors que peutetre ca ne devrait pas arriver?