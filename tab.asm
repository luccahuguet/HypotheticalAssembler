SECAO TEXT
INPUT                        OLD_DATA                           









LOAD OLD_DATA                    
L1: DIV 				DOIS
STORE  NEW_DATA
MULT DOIS
L3:
STORE TMP_DATA
LOAD OLD_DATA
L4:                 


SUB TMP_DATA
STORE TMP_DATA
OUTPUT TMP_DATA
COPY NEW_DATA,OLD_DATA            
LOAD OLD_DATA
JMPP L1
STOP                 
SECAO DATA          
DOIS: CONST 2
OLD_DATA: SPACE               
NEW_DATA: SPACE
TMP_DATA: SPACE