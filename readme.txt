Per l'avvio dell'agent utilizzare lo script bin/start.sh

Utilizzo: 
./start.sh <white|black> [PORT]

Millgates � composto da un agent c++ che comunica al server di gioco utilizzando come intermediario middleware.jar
L'argomento PORT � opzionale e stabilisce la porta su cui middleware e agent c++ devono comunicare. 
Di default viene utilizzata la porta 25568, ma nel caso in cui altre applicazioni utilizzino gi� tale porta � possibile
utilizzarne una diversa.