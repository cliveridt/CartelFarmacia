/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>
/*End of auto generated code by Atmel studio */



unsigned char modo=0;
unsigned char enturno=0;
unsigned int tiempo=0;

/*Control remoto
	A=D2
	B=D0
	C=D3
	D=D1
*/


//Salidas
const int cruz1 = 5;	// Cruz interna (OC0B)
const int cruz2 = 6;	// Cruz externa (OC0A)
const int circ	= 3;	// Circunferencia externa (OC2B)
const int turno = 11;	// Mensaje "de turno" (OC2A)

//Entradas
const int D0 = 14;	//DataIn0	(A0)
const int D1 = 15;	//DataIn1	(A1)
const int D2 = 16;	//DataIn2	(A2)
const int D3 = 17;	//DataIn3	(A3)



ISR (PCINT1_vect) // Interrupciones por cambio en las entradas del control remoto
{
	delay(500);		//Antirrebote
	if(digitalRead(D0)==1){	//D0 cambia el modo al siguiente
		modo++;
		if(modo>3){modo=0;}
		while(digitalRead(D0));	//Espera a que se suelte el boton
		PCIFR=0;				//Limpia la bandera para no volver a entrar en la interrupcion
	}
	else if(digitalRead(D2)==1){	//D2 cambia el modo hacia atras
		modo--;
		if (modo==255){modo=3;}
		while(digitalRead(D2));	//Espera a que se suelte el boton
		PCIFR=0;				//Limpia la bandera para no volver a entrar en la interrupcion
	}
	else if(digitalRead(D1)==1){	//D1 enciende el mensaje "En turno"
		digitalWrite(turno,HIGH);
		while(digitalRead(D1));	//Espera a que se suelte el boton
		PCIFR=0;				//Limpia la bandera para no volver a entrar en la interrupcion
	}
	else if(digitalRead(D3)==1){	//D3 apaga el mensaje "En turno"
		digitalWrite(turno,LOW);
		while(digitalRead(D3));	//Espera a que se suelte el boton
		PCIFR=0;				//Limpia la bandera para no volver a entrar en la interrupcion
	}
	
}


void setup() {
	//GPIO
	pinMode(cruz1,OUTPUT);
	pinMode(cruz2,OUTPUT);
	pinMode(circ,OUTPUT);
	pinMode(turno,OUTPUT);
	
	pinMode(D0,INPUT);
	pinMode(D1,INPUT);
	pinMode(D2,INPUT);
	pinMode(D3,INPUT);
	
	//Interrupciones
	PCIFR = 0;	//Baja todas las banderas de interrupcion
	PCICR = 0x02;	//Habilita las interrupciones por cambio desde A0 a A5
	PCMSK1 = 0x0F;	//Habilita las interrupciones de A0:A4
	
	
	
	digitalWrite(cruz1,LOW);
	digitalWrite(cruz2,LOW);
	digitalWrite(circ,LOW);
	digitalWrite(turno,LOW);
}

void loop() {
	switch(modo){
		case 0:
			digitalWrite(circ,HIGH);
			digitalWrite(cruz1,HIGH);
			digitalWrite(cruz2,HIGH);
		break;
		
		case 1:
			digitalWrite(cruz1,HIGH);
			delay(500);
			digitalWrite(cruz2,HIGH);
			delay(500);
			digitalWrite(circ,HIGH);
			delay(500);
		
			digitalWrite(cruz1,LOW);
			delay(500);
			digitalWrite(cruz2,LOW);
			delay(500);
			digitalWrite(circ,LOW);
			delay(500);
			break;
		
		case 2:
			digitalWrite(cruz1,HIGH);
			delay(200);
			digitalWrite(cruz2,HIGH);
			delay(200);
			digitalWrite(circ,HIGH);
			delay(200);
		
			digitalWrite(cruz1,LOW);
			delay(200);
			digitalWrite(cruz2,LOW);
			delay(200);
			digitalWrite(circ,LOW);
			delay(200);
			break;
		
		case 3:
			digitalWrite(circ,HIGH);
			digitalWrite(cruz1,HIGH);
			digitalWrite(cruz2,HIGH);
			delay(500);
			
			digitalWrite(cruz1,LOW);
			digitalWrite(cruz2,LOW);
			delay(500);
			break;
		
		default:
		break;
	}

}
