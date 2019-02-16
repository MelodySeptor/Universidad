.586
.MODEL FLAT, C


; Funcions definides en C
printChar_C PROTO C, value:SDWORD
printInt_C PROTO C, value:SDWORD
clearscreen_C PROTO C
clearArea_C PROTO C, value:SDWORD, value1: SDWORD
printMenu_C PROTO C
gotoxy_C PROTO C, value:SDWORD, value1: SDWORD
getch_C PROTO C
printBoard_C PROTO C, value: DWORD
initialPosition_C PROTO C


TECLA_S EQU 115   ;ASCII letra s es el 115


.data          
teclaSalir DB 0




.code   
   
;;Macros que guardan y recuperan de la pila los registros de proposito general de la arquitectura de 32 bits de Intel    
Push_all macro
	
	push eax
   	push ebx
    push ecx
    push edx
    push esi
    push edi
endm


Pop_all macro

	pop edi
   	pop esi
   	pop edx
   	pop ecx
   	pop ebx
   	pop eax
endm
   
   
public C posCurScreenP1, getMoveP1, moveCursorP1, movContinuoP1, openP1, openContinuousP1
                         

extern C opc: SDWORD, row:SDWORD, col: BYTE, carac: BYTE, carac2: BYTE, sea: BYTE, taulell: BYTE, sunk: SDWORD, indexMat: SDWORD, tocat: SDWORD
extern C rowCur: SDWORD, colCur: BYTE, rowScreen: SDWORD, colScreen: SDWORD, RowScreenIni: SDWORD, ColScreenIni: SDWORD
extern C rowIni: SDWORD, colIni: BYTE, indexMatIni: SDWORD


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Situar el cursor en una fila i una columna de la pantalla
; en funció de la fila i columna indicats per les variables colScreen i rowScreen
; cridant a la funció gotoxy_C.
;
; Variables utilitzades: 
; Cap
; 
; Paràmetres d'entrada : 
; Cap
;    
; Paràmetres de sortida: 
; Cap
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
gotoxy:
   push ebp
   mov  ebp, esp
    Push_all
   

   ; Quan cridem la funció gotoxy_C(int row_num, int col_num) des d'assemblador 
   ; els paràmetres s'han de passar per la pila
      
   mov eax,[colScreen]
   push eax
   mov eax,[rowScreen]
   push eax
   call gotoxy_C
   pop eax
   pop eax 
   
    Pop_all

   mov esp, ebp
   pop ebp
   ret




;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Mostrar un caràcter, guardat a la variable carac
; en la pantalla en la posició on està  el cursor,  
; cridant a la funció printChar_C.
; 
; Variables utilitzades: 
; carac : variable on està emmagatzemat el caracter a treure per pantalla
; 
; Paràmetres d'entrada : 
; Cap
;    
; Paràmetres de sortida: 
; Cap
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
printch:
   push ebp
   mov  ebp, esp
   ;guardem l'estat dels registres del processador perqué
   ;les funcions de C no mantenen l'estat dels registres.
   
   
   Push_all
   

   ; Quan cridem la funció printch_C(char c) des d'assemblador, 
   ; el paràmetre (carac) s'ha de passar per la pila.
 
   xor eax,eax
   mov  al, [carac]
   push eax 
   call printChar_C
 
   pop eax
   Pop_all

   mov esp, ebp
   pop ebp
   ret
   

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Llegir un caràcter de teclat   
; cridant a la funció getch_C
; i deixar-lo a la variable carac2.
;
; Variables utilitzades: 
; carac2 : Variable on s'emmagatzema el caracter llegit
;; 
; Paràmetres d'entrada : 
; Cap
;    
; Paràmetres de sortida: 
; El caracter llegit s'emmagatzema a la variable carac
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
getch:
   push ebp
   mov  ebp, esp
    
   ;push eax
   Push_all

   call getch_C
   
   mov [carac2],al
   
   ;pop eax
   Pop_all

   mov esp, ebp
   pop ebp
   ret




;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Posicionar el cursor a la pantalla, dins el tauler, en funció de
; les variables (row) fila (int) i (col) columna (char), a partir dels
; valors de les constants RowScreenIni i ColScreenIni.
; Primer cal restar 1 a row (fila) per a que quedi entre 0 i 7 
; i convertir el char de la columna (A..H) a un número entre 0 i 7.
; Per calcular la posició del cursor a pantalla (rowScreen) i 
; (colScreen) utilitzar aquestes fórmules:
; rowScreen=rowScreenIni+(row*2)
; colScreen=colScreenIni+(col*4)
; Per a posicionar el cursor cridar a la subrutina gotoxy.
;
; Variables utilitzades:	
; row       : fila per a accedir a la matriu sea
; col       : columna per a accedir a la matriu sea
; rowScreen : fila on volem posicionar el cursor a la pantalla.
; colScreen : columna on volem posicionar el cursor a la pantalla.
;
; Paràmetres d'entrada : 
; Cap
;
; Paràmetres de sortida: 
; Cap
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
posCurScreenP1:
    push ebp
	mov  ebp, esp

	;ROW
	mov  eax, [row]
	sub	 eax, 1
	imul eax, 2
	add  eax, [rowScreenIni]
	mov  [rowScreen], eax

	;COL
	xor  eax, eax
	mov  al, [col]
	sub  eax, 65
	imul eax, 4
	add  eax, [colScreenIni]
	mov  [colScreen], eax
	
	;FIN
    call gotoxy
	mov  esp, ebp
	pop  ebp
	ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Llegir un caràcter de teclat   
; cridant a la subrutina getch
; Verificar que solament es pot introduir valors entre 'i' i 'l', o la tecla espai
; i deixar-lo a la variable carac2.
; 
; Variables utilitzades: 
; carac2 : Variable on s'emmagatzema el caracter llegit
; op: Variable que indica en quina opció del menú principal estem
; 
; Paràmetres d'entrada : 
; Cap
;    
; Paràmetres de sortida: 
; El caracter llegit s'emmagatzema a la variable carac2
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
getMoveP1:
   push ebp
   mov  ebp, esp
   Push_all

   ;Comprueba todos los inputs
   call getch
   cmp al, ' '
   jne fuera
   cmp al, 'i'
   jl fuera
   cmp al, 'l'
   jg fuera
   mov [carac2], al

fuera:   
   mov esp, ebp
   pop ebp
   ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Actualitzar les variables (rowCur) i (colCur) en funció de 
; la tecla premuda que tenim a la variable (carac2)
; (i: amunt, j:esquerra, k:avall, l:dreta).
; Comprovar que no sortim del tauler, (rowCur) i (colCur) només poden 
; prendre els valors [1..8] i [0..7]. Si al fer el moviment es surt 
; del tauler, no fer el moviment.
; No posicionar el cursor a la pantalla, es fa a posCurScreenP1.
; 
; Variables utilitzades: 
; carac2 : caràcter llegit de teclat
;          'i': amunt, 'j':esquerra, 'k':avall, 'l':dreta
; rowCur : fila del cursor a la matriu sea.
; colCur : columna del cursor a la matriu sea.
;
; Paràmetres d'entrada : 
; Cap
;
; Paràmetres de sortida: 
; Cap
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
moveCursorP1:
   push ebp
   mov  ebp, esp 

   cmp [carac2], 'i'
   je i
   cmp [carac2], 'j'
   je j
   cmp [carac2], 'k'
   je k
   cmp [carac2], 'l'
   je l
   jmp fin

; j i l son char 1byte
; i i k son int 4bytes
i:
   mov eax, [rowCur]
   sub eax, 1
   cmp eax, 1
   jl fin
   mov [rowCur], eax
   jmp fin
j:
   mov bl, [colCur]
   sub bl, 1
   cmp bl, 'A'
   jl fin
   mov [colCur], bl
   jmp fin
k:
   mov eax, [rowCur]
   add eax, 1
   cmp eax, 8
   jg fin
   mov [rowCur], eax
   jmp fin
l:
   mov bl, [colCur]
   add bl, 1
   cmp bl, 'H'
   jg fin
   mov [colCur], bl
   jmp fin

fin:
   mov esp, ebp
   pop ebp
   ret


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Subrutina que implementa el moviment continuo. 
;
; Variables utilitzades: 
;		carac2   : variable on s’emmagatzema el caràcter llegit
;		rowCur   : Fila del cursor a la matriu sea
;		colCur   : Columna del cursor a la matriu sea
;		row      : Fila per a accedir a la matriu sea
;		col      : Columna per a accedir a la matriu sea
; 
; Paràmetres d'entrada : 
; Cap
;
; Paràmetres de sortida: 
; Cap
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
movContinuoP1:
	push ebp
	mov  ebp, esp

	call getMoveP1
	mov  bl, [carac2]

bucle:	
	cmp  bl, 's'
	je  final
	cmp  bl, ' '
	je   final
	call moveCursorP1
	mov  eax, [rowCur]
	mov  [row], eax
	mov  bl, [colCur]
	mov  [col], bl
	call posCurScreenP1
	call getMoveP1
	mov  bl, [carac2]
	jmp  bucle

final:
	mov esp, ebp
	pop ebp
	ret



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Calcular l'índex per a accedir a les matrius en assemblador.
; sea[row][col] en C, és [sea+indexMat] en assemblador.
; on indexMat = row*8 + col (col convertir a número).
;
; Variables utilitzades:	
; row       : fila per a accedir a la matriu sea
; col       : columna per a accedir a la matriu sea
; indexMat	: índex per a accedir a la matriu sea
;
; Paràmetres d'entrada : 
; Cap
;
; Paràmetres de sortida: 
; Cap
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
calcIndexP1:
	push ebp
	mov  ebp, esp
	
	mov  eax, [row]
	imul eax, 8
	xor  ecx, ecx
	mov  cl, [col]
	sub  ecx, 65
	add  eax, ecx
	sub  eax, 8
	mov  [indexMat], eax

	mov esp, ebp
	pop ebp
	ret



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Obrim una casella de la matriu sea
; En primer lloc calcular la posició de la matriu corresponent a la
; posició que ocupa el cursor a la pantalla, cridant a la 
; subrutina calcIndexP1 i mostrar 'T' si hi ha un barco o 'O' si és aigua
; cridant a la subrutina printch. L'índex per a accedir
; a la matriu (sea) el calcularem cridant a la subrutina calcIndexP1.
; No es pot obrir una casella que ja tenim oberta.
;
; Variables utilitzades:	
; row       : fila per a accedir a la matriu sea
; rowCur	: fila actual del cursor a la matriu
; col       : columna per a accedir a la matriu sea
; colCur	: columna actual del cursor a la matriu
; indexMat	: Índex per a accedir a la matriu sea
; tocat		: indica si em tocat un vaixell
; sea		: Matriu 8x8 on tenim les posicions dels borcos. 
; carac2		: caràcter per a escriure a pantalla.
; taulell   : Matriu en la que anem indicant els valors de les nostres tirades 
;
; Paràmetres d'entrada : 
; Cap
;
; Paràmetres de sortida: 
; Cap
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
openP1:
	push ebp
	mov  ebp, esp

	call calcIndexP1
	xor  ecx, ecx
	mov  edx, [indexMat]
	xor  eax, eax
	mov  al, [taulell + edx]
	cmp  al, 'T'
	je  fueraOtro
	cmp al, 'O'
	je  fueraOtro
	mov  cl, [carac2]
	cmp  cl, ' '
	jne  fueraOtro
	mov  al, [sea + edx]
	cmp  al, 1
	jne noBarco
	mov  cl , 'T'
	mov  [carac], cl
	jmp pintarTodo

noBarco:
	mov  cl, 'O'
	mov  [carac], cl

pintarTodo:
	mov  [taulell+edx], cl
	call sunk_boat
	call printch

 fueraOtro:
	mov esp, ebp
	pop ebp
	ret


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Subrutina que implementa l’obertura continua de caselles. S’ha d’utiliitzar
; la tecla espai per a obrir una casella i la 's' per a sortir. 
;
; Variables utilitzades: 
; carac2   : Caràcter introduït per l’usuari
; rowCur   : Fila del cursor a la matriu sea
; colCur   : Columna del cursor a la matriu sea
; row      : Fila per a accedir a la matriu sea
; col      : Columna per a accedir a la matriz sea
;
; Paràmetres d'entrada : 
; Cap
;
; Paràmetres de sortida: 
; Cap
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
openContinuousP1:
	push ebp
	mov  ebp, esp

	call openP1
	xor  edx, edx
	mov  dl, [carac2]
bucleOpenCont:
	cmp  dl, 's'
	je fueraFinal
	call movContinuoP1
	call openP1
	mov  dl, [carac2]
	jmp bucleOpenCont

fueraFinal:
	mov esp, ebp
	pop ebp
	ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Subrutina que comprova si un vaixell que hem tocat està enfonsat
; i en cas afirmatiu marca totes les caselles del vaixell amb una H 
;
; Variables utilitzades: 
;	carac		: Caràcter a imprimir per pantalla
;	rowCur		: Fila del cursor a la matriu sea
;	colCur		: Columna del cursor a la matriu sea
;	row			: Fila per a accedir a la matriu sea
;	col			: Columna per a accedir a la matriz sea
;	sea			: Matriu en la que tenim emmagatzemats el mapa i els bracos
;	indexMat	: Variable que indica la posició de la matriu sea a la que
;				  volem accedir
;	sunk		: Variable que indica si un barco ha estat enfonsat (1) o no (0)
;
; Paràmetres d'entrada : 
; Cap
;
; Paràmetres de sortida: 
; Cap
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
sunk_boat:
	push ebp
	mov  ebp, esp

	;mov  eax, [indexMat]
	;mov  cl, [taulell + eax]
	;cmp  cl, 'T'
	;jne fuerasunk
	;mov  al, 'H'
	;mov  [carac], al


	mov esp, ebp
	pop ebp
	ret



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Subrutina que marca com aigua totes les caselles que envolten un 
; vaixell enfonsat 
;
; Variables utilitzades: 
;		carac    : Caràcter a imprimir per pantalla
;		rowCur   : Fila del cursor a la matriu sea
;		colCur   : Columna del cursor a la matriu sea
;		row      : Fila per a accedir a la matriu sea
;		col      : Columna per a accedir a la matriu sea
;		rowIni	 : Fila on hem fet la tirada
;		colIni	 : Columna on hem fet la tirada
;		sea		 : Matriu en la que tenim emmagatzemats el mapa i els bracos
;		indexMat : Variable que indica la posició on està emmagatzemada
;	               la cel·la de la matriu sea a la que volem accedir
;		indexMatIni: Variable que indica la posició on està emmagatzemada
;	                 la cel·la de la matriu sea a la que hem fet la tirada
;
; Paràmetres d'entrada : 
; Cap
;
; Paràmetres de sortida: 
; Cap
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
border:
	push ebp
	mov  ebp, esp






	mov esp, ebp
	pop ebp
	ret

END
