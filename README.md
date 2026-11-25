Configuration du timer 1 :
Pour obtenir un cycle de 100ms, il faut configurer le timer 1. On peut y modifier le presceler et le nombre de pas. Il faut faire attantion car le timer fonctionne en 16bit, Ce qui veut dire que le nombre de pas ne dois pas depasser la valeur 65535. Pour evitez ce problème, j'ai mits la valeur maximum du presceler (256). Il reste à definir le nombre de pas avec ce calcule :

Nombre de pas = tcycle * fmicro / presceler = 100ms * 80MHz / 256 = 31250

Mesure temps initialisation :
<img width="1280" height="824" alt="temps init" src="https://github.com/user-attachments/assets/04f0a541-e283-406a-870d-c26f11fd0270" />
Après que le bouton de reset de la carte aie été activé, le programme passe en état APP_STATE_SERVICE_TASKS. Ce mode dure 3s et ensuite le programme principale se mets en route avec le chennillard. Le temps mesuré est de 3s donc le programme fonctionne correctement.

Mesure temps chennillard :
<img width="1280" height="824" alt="chenillard" src="https://github.com/user-attachments/assets/fc3838f3-54ae-44b9-9a93-f4f063e324ef" />
Le chenillard fonctionne correctement car les LED D6 à D13 s'allume l'un apres l'autre. Le temps est egalement respecter car chaque 201ms, une LED s'allume et l'autre s'eteinds. Il y a 1ms en trop car il y a le temps d'executions du programme.
